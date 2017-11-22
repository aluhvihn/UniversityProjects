package edu.ucla.cs.cs144;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Vector;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.FactoryConfigurationError;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.Text;
import org.xml.sax.ErrorHandler;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

public class ParseXML {
  private static DocumentBuilder builder;

  private ParseXML () {}

/*************    Functions from MyParser.java (Project 2)    *******************/

  private static class MyErrorHandler implements ErrorHandler {
    public void warning(SAXParseException exception)
        throws SAXException {
      fatalError(exception);
    }

    public void error(SAXParseException exception)
        throws SAXException {
      fatalError(exception);
    }

    public void fatalError(SAXParseException exception)
        throws SAXException {
      exception.printStackTrace();
      System.out.println("There should be no errors in the supplied XML files.");
      System.exit(3);
    }
  }

  /* Non-recursive (NR) version of Node.getElementsByTagName(...)
   */
  private static Element[] getElementsByTagNameNR(Element e, String tagName) {
    Vector< Element > elements = new Vector< Element >();
    Node child = e.getFirstChild();
    while (child != null) {
      if (child instanceof Element && child.getNodeName().equals(tagName))
      {
        elements.add( (Element)child );
      }
      child = child.getNextSibling();
    }
    Element[] result = new Element[elements.size()];
    elements.copyInto(result);
    return result;
  }

  /* Returns the first subelement of e matching the given tagName, or
   * null if one does not exist. NR means Non-Recursive.
   */
  private static Element getElementByTagNameNR(Element e, String tagName) {
    Node child = e.getFirstChild();
    while (child != null) {
      if (child instanceof Element && child.getNodeName().equals(tagName))
        return (Element) child;
      child = child.getNextSibling();
    }
    return null;
  }

  /* Returns the text associated with the given element (which must have
   * type #PCDATA) as child, or "" if it contains no text.
   */
  private static String getElementText(Element e) {
    if (e.getChildNodes().getLength() == 1) {
      Text elementText = (Text) e.getFirstChild();
      return elementText.getNodeValue();
    }
    else
      return "";
  }

  /* Returns the text (#PCDATA) associated with the first subelement X
   * of e with the given tagName. If no such X exists or X contains no
   * text, "" is returned. NR means Non-Recursive.
   */
  private static String getElementTextByTagNameNR(Element e, String tagName) {
    Element elem = getElementByTagNameNR(e, tagName);
    if (elem != null)
      return getElementText(elem);
    else
      return "";
  }

  static {
    try {
      DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
      factory.setValidating(false);
      factory.setIgnoringElementContentWhitespace(true);      
      ParseXML.builder = factory.newDocumentBuilder();
      ParseXML.builder.setErrorHandler(new MyErrorHandler());
    }
    catch (FactoryConfigurationError e) {
      System.out.println("unable to get a document builder factory");
      System.exit(2);
    } 
    catch (ParserConfigurationException e) {
      System.out.println("parser was unable to be configured");
      System.exit(2);
    }
  }

/********************************************************************************************/

  public static Item parseXML(String xml) {
    Document doc = null;
    try {
      doc = ParseXML.builder.parse(new ByteArrayInputStream(xml.getBytes()));
    }
    catch (IOException e) {
      e.printStackTrace();
      System.exit(3);
    }
    catch (SAXException e) {
      e.printStackTrace();
      System.exit(3);
    }
    Item item = new Item(doc.getDocumentElement().getAttribute("ItemID"));
    org.w3c.dom.NodeList nlist = doc.getDocumentElement().getChildNodes();
    LinkedList<String> categories = new LinkedList<String>();
    LinkedList<Bid> bids = new LinkedList<Bid>();
    for (int i=0; i<nlist.getLength(); i++) {
      Node n = nlist.item(i);
      switch (n.getNodeName()) {
        case "Name":
          item.setName(getElementText((Element) n));
          break;
        case "Category":
          categories.add(getElementText((Element) n));
          break;
        case "Currently":
          item.setCurrently(getElementText((Element) n));
          break;
        case "Buy_Price":
          item.setBuyPrice(getElementText((Element) n));
          break;
        case "First_Bid":
          item.setFirstBid(getElementText((Element) n));
          break;
        case "Number_of_Bids":
          item.setNumberOfBids(getElementText((Element) n));
          break;
        case "Bids":
          Element[] bids_list = getElementsByTagNameNR((Element) n, "Bid");
          for (int j=0; j<bids_list.length; j++) {
            Element user = getElementByTagNameNR(bids_list[j], "Bidder");
            String location = getElementTextByTagNameNR(user, "Location");
            String country = getElementTextByTagNameNR(user, "Country");
            bids.add(new Bid( new User(user.getAttribute("UserID"),
                                        user.getAttribute("Rating"),
                                        new Location("location"),
                                        country),
                              getElementTextByTagNameNR(bids_list[j], "Time"), 
                              getElementTextByTagNameNR(bids_list[j], "Amount")));
          }
          break;
        case "Location":
          item.setLocation(new Location(getElementText((Element) n), 
              ((Element) n).getAttribute("Latitude"), ((Element) n).getAttribute("Longitude")));
          break;
        case "Country":
          item.setCountry(getElementText((Element) n));
          break;
        case "Started":
          item.setStarted(getElementText((Element) n));
          break;
        case "Ends":
          item.setEnds(getElementText((Element) n));
          break;
        case "Seller":
          Element user = (Element) n;
          String location = getElementTextByTagNameNR(user, "Location");
          String country = getElementTextByTagNameNR(user, "Country");
          item.setSeller(new User(user.getAttribute("UserID"), user.getAttribute("Rating"),
                                  new Location("location"), country));
          break;
        case "Description":
          item.setDescription(getElementText((Element) n));
          break;
      }
      item.setCategories(categories.toArray(new String[categories.size()]));
      Collections.sort(bids, Collections.reverseOrder(new ComparatorBid()));
      item.setBids(bids.toArray(new Bid[bids.size()]));
    }
    return item;
  }
}