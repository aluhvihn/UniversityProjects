package edu.ucla.cs.cs144;

import java.io.IOException;
import javax.servlet.Servlet;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class BuyServlet extends HttpServlet implements Servlet {
  
  public BuyServlet() {}

  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
    HttpSession session = request.getSession(true);
    Item item = (Item) session.getAttribute("itemBuying");
    request.setAttribute("itemID", item.getItemID());
    request.setAttribute("name", item.getName());
    request.setAttribute("price", item.getBuyPrice());
    request.setAttribute("confirmURL", "https:"+request.getServerName()+":8443"+request.getContextPath()+"/confirm");
    request.getRequestDispatcher("/buy.jsp").forward(request, response);
  }
}