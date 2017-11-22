package edu.ucla.cs.cs144;

import java.io.IOException;
import javax.servlet.Servlet;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.text.SimpleDateFormat;
import java.util.Date;

public class ConfirmPurchaseServlet extends HttpServlet implements Servlet {
  
  public ConfirmPurchaseServlet() {}

  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
    HttpSession session = request.getSession(true);
    Item item = (Item) session.getAttribute("itemBuying");
    String ccNum = request.getParameter("ccNum");
    SimpleDateFormat dateFormat = new SimpleDateFormat("MMM-dd-yy kk:mm:ss");
    Date date = new Date();
    request.setAttribute("itemID", item.getItemID());
    request.setAttribute("name", item.getName());
    request.setAttribute("price", item.getBuyPrice());
    request.setAttribute("ccNum", ccNum);
    request.setAttribute("time", dateFormat.format(date));
    request.setAttribute("homeURL", "http:"+request.getServerName()+":1448"+request.getContextPath()+"/search");
    request.getRequestDispatcher("/confirm.jsp").forward(request, response);
  }
  
  protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
    doGet(request, response);
  }
}