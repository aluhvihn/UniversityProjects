import time
import logging
import sys
import json
import datetime
import re

from twisted.internet import reactor, protocol
from twisted.protocols.basic import LineReceiver
from twisted.python import log
from twisted.web.client import getPage
from twisted.application import service, internet

GOOGLE_API_KEY = "AIzaSyCGOezzGtT73XE1xc6POSWhVlxG-XXjxGE"
GOOGLE_API_PREFIX = "https://maps.googleapis.com/maps/api/place/nearbysearch/json?"

Ports = {
  "Alford" : 5000,
  "Bolden" : 5001,
  "Hamilton" : 5002,
  "Parker" : 5003,
  "Welsh" : 5004
}

Neighbors = {
  "Alford" : ["Parker", "Welsh"],
  "Bolden" : ["Parker", "Welsh"],
  "Hamilton" : ["Parker"],
  "Parker" : ["Alford", "Bolden", "Hamilton"],
  "Welsh" : ["Alford", "Bolden"]
}

class ProxyServerProtocol(LineReceiver):
  def __init__(self, factory):
    self.factory = factory

  def connectionMade(self):
    self.factory.numConnections += 1
    logging.info("Connection established. Total: {0}".format(self.factory.numConnections))

  def lineReceived(self, line):
    logging.info("Line received: {0}".format(line))
    param = line.split()

    if len(param) < 1:
      logging.error("Invalid number of parameters.")
      self.transport.write("? {0}\n".format(line))
    elif (param[0] == "IAMAT"):
      self.procIAMAT(line)
    elif (param[0] == "WHATSAT"):
      self.procWHATSAT(line)
    elif (param[0] == "AT"):
      self.procAT(line)
    else:
      logging.error("Invalid line.")
      self.transport.write("? {0}\n".format(line))
    return

  def procIAMAT(self, line):
    param = line.split()
    if len(param) != 4:
      logging.error("IAMAT - invalid command: {0}".format(line))
      self.transport.write("? {0}\n".format(line))
      return
    command, clientID, clientPos, clientTime = param
    
    try:
      timeDiff =  time.time() - float(clientTime)
    except Exception, e:
      logging.error("IAMAT - invalid command: {0}".format(line))
      self.transport.write("? {0}\n".format(line))
      return

    if timeDiff >= 0:
      response = "AT {0} +{1} {2}".format(self.factory.serverName,
        timeDiff, ' '.join(param[1:]))
    else:
      response = "AT {0} {1} {2}".format(self.factory.serverName,
        timeDiff, ' '.join(param[1:]))

    if clientID in self.factory.clients:
      if (clientTime <= self.factory.clients[clientID]["time"]):
        logging.info("Outdated AT info from client: {0}".format(clientID))
      else:
        logging.info("Update from client: {0}".format(clientID))
    else:
      logging.info("New client: {0}".format(clientID))
    self.factory.clients[clientID] = {"response":response, "time":clientTime}

    logging.info("Response to IAMAT: {0}".format(response))
    self.transport.write("{0}\n".format(response))

    logging.info("Sending location update to neighbors")
    self.propagateLoc(response)

  def procWHATSAT(self, line):
    param = line.split()
    if len(param) != 4:
      logging.error("WHATSAT - invalid command: {0}".format(line))
      self.transport.write("? {0}\n".format(line))
      return
    command, clientID, radius, upperLim = param
    radius = int(radius)
    upperLim = int(upperLim)
    if radius > 50 or upperLim > 20:
      logging.error("WHATSAT: range or item limit exceeded.")
      self.transport.write("? {0}\n".format(line))
      return
    if not (clientID in self.factory.clients):
      self.commandFailed(line, "WHATSAT: client not found.")
      return

    AT_response = self.factory.clients[clientID]["response"]
    logging.info("AT response: {0}".format(AT_response))
    commandAT, server, timeDiff, clientID2, clientPos, clientTime = AT_response.split()

    clientPos = re.sub(r'[-]', ' -', clientPos)
    clientPos = re.sub(r'[+]', ' +', clientPos).split()
    queryPos = clientPos[0] + "," + clientPos[1]

    requestURL = "{0}location={1}&radius={2}&sensor=false&key={3}".format(
      GOOGLE_API_PREFIX, queryPos, radius, GOOGLE_API_KEY)
    logging.info("API request: {0}".format(requestURL))
    API_response = getPage(requestURL)
    API_response.addCallback(callback = lambda x:(self.processRequest(x, clientID, upperLim)))

  def procAT(self, line):
    param = line.split()
    if len(param) != 6:
      logging.error("AT - invalid command: {0}".format(line))
      self.transport.write("? {0}\n".format(line))
      return

    commandAT, server, timeDiff, clientID, clientPos, clientTime = param

    # Check time stamp to stop flooding
    if (clientID in self.factory.clients) and (clientTime <= self.factory.clients[clientID]["time"]):
      logging.info("Duplicate AT info from {0}".format(server))
      return

    if clientID in self.factory.clients:
      logging.info("AT - Location update for client: {0}".format(clientID))
    else:
      logging.info("AT - Location update for new client: {0}".format(clientID))

    self.factory.clients[clientID] = { "response":("{0} {1} {2} {3} {4} {5}".format(
      commandAT, server, timeDiff, clientID, clientPos, clientTime)), 
      "time":clientTime }
    logging.info("Added or updated {0} : {1}".format(clientID, self.factory.clients[clientID]["response"]))

    self.propagateLoc(self.factory.clients[clientID]["response"])
    return

  def processRequest(self, response, clientID, upperLim):
    responseObj = json.loads(response)
    results = responseObj["results"]
    responseObj["results"] = results[0:int(upperLim)]
    logging.info("API Response: {0}".format(json.dumps(responseObj, indent=4)))
    msg = self.factory.clients[clientID]["response"]
    full_response = "{0}\n{1}\n\n".format(msg, json.dumps(responseObj, indent=4))
    self.transport.write(full_response)

  def propagateLoc(self, message):
    for neighbor in Neighbors[self.factory.serverName]:
      reactor.connectTCP('localhost', Ports[neighbor], ProxyClient(message))
      logging.info("Location update sent from {0} to {1}".format(self.factory.serverName, neighbor))
    return

  def connectionLost(self, reason):
    self.factory.numConnections = self.factory.numConnections - 1
    logging.info("Connection lost. Remaining clients: {0}".format(self.factory.numConnections))

class ProxyServer(protocol.ServerFactory):
  def __init__(self, serverName):
    self.serverName = serverName
    self.serverPort = Ports[self.serverName]
    self.numConnections = 0
    self.clients = {}
    filename = self.serverName + "_" + re.sub(r'[:T]', '_', datetime.datetime.utcnow().isoformat().split('.')[0]) + ".log"
    logging.basicConfig(filename = filename, level=logging.DEBUG, filemode = 'a', format='%(asctime)s %(message)s')
    logging.info('{0}:{1} server started'.format(self.serverName, self.serverPort))

  def buildProtocol(self, addr):
    return ProxyServerProtocol(self)

  def stopFactory(self):
    logging.info("{0} server shutdown".format(self.serverName))

class ProxyClientProtocol(LineReceiver):
  def __init__ (self, factory):
    self.factory = factory

  def connectionMade(self):
    self.sendLine(self.factory.message)
    self.transport.loseConnection()

class ProxyClient(protocol.ClientFactory):
  def __init__(self, message):
    self.message = message

  def buildProtocol(self, addr):
    return ProxyClientProtocol(self)

def main():
  if len(sys.argv) != 2:
    print "Usage: python chatserver.py [Server name]\n\tServer names are Alford, Bolden, Hamilton, Parker and Welsh."
    exit()
  factory = ProxyServer(sys.argv[1])

  reactor.listenTCP(Ports[sys.argv[1]], factory)
  reactor.run()

if __name__ == '__main__':
    main()