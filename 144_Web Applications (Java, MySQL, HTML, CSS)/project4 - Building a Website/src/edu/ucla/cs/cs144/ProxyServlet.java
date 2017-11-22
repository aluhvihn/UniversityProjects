package edu.ucla.cs.cs144;

import java.io.IOException;
import java.net.HttpURLConnection;
import javax.servlet.Servlet;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.net.URL;
import java.net.URI;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;

public class ProxyServlet extends HttpServlet implements Servlet {

  public ProxyServlet() {}
  
  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
    // your codes here
    String query = request.getParameter("q");
    String url_string = "";
    try{
      URI uri = new URI("http", "google.com", "/complete/search", "output=toolbar&q=" + query, null);
      url_string = uri.toASCIIString();
    } catch(Exception e){}
    
    URL url = new URL(url_string);
    HttpURLConnection con = (HttpURLConnection) url.openConnection();
    con.setRequestProperty("User-Agent", "Mozilla/5.0");
    int responseCode = con.getResponseCode();
    System.out.println("\nSending GET request to " + url_string);
    System.out.println("Response Code: " + responseCode);
 
    String inputLine;
    StringBuffer result = new StringBuffer();
    BufferedReader buffer = new BufferedReader(new InputStreamReader(con.getInputStream()));
    while ((inputLine = buffer.readLine()) != null) {
      result.append(inputLine);
    }
    response.setContentType("text/xml");
    response.getWriter().write(result.toString());
    
    System.out.println(result.toString());
    buffer.close();
  }
}
