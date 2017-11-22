package edu.ucla.cs.cs144;

import java.io.IOException;
import javax.servlet.Servlet;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class ItemServlet extends HttpServlet implements Servlet {

  public ItemServlet() {}

  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
    // your codes here
    Item item = null;
    HttpSession session = request.getSession(true);

    String xml = AuctionSearchClient.getXMLDataForItemId(request.getParameter("id"));
    if (xml != "" && xml != null) {
      item = ParseXML.parseXML(xml);
      if (session != null && item.getBuyPrice() != null && item.getBuyPrice() != "") {
        session.setAttribute("itemBuying", item);
      }
    }
    request.setAttribute("item", item);
    request.getRequestDispatcher("/item.jsp").forward(request, response);
  }
}