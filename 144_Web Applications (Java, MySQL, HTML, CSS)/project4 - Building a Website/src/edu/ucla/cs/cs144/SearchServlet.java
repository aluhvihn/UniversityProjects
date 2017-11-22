package edu.ucla.cs.cs144;

import java.io.IOException;
import javax.servlet.Servlet;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class SearchServlet extends HttpServlet implements Servlet {

  public SearchServlet() {}

  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
    // your codes here
    String query = request.getParameter("q");
    int numResultsToSkip = 0;
    int numResultsToReturn = 20;
    SearchResult[] result = null;
    try {
      numResultsToSkip = Integer.parseInt(request.getParameter("numResultsToSkip"));
      numResultsToReturn = Integer.parseInt(request.getParameter("numResultsToReturn"));
      if (query != null && query != "") {
        result = AuctionSearchClient.basicSearch(query, numResultsToSkip, numResultsToReturn + 1);
      }
    } catch (Exception e) {
      e.printStackTrace();
    }

    request.setAttribute("query", query);
    request.setAttribute("numResultsToSkip", numResultsToSkip);
    request.setAttribute("numResultsToReturn", numResultsToReturn);
    
    request.setAttribute("result", result);
    request.setAttribute("prevExists", result != null && numResultsToReturn != 0 && numResultsToSkip-numResultsToReturn >= 0);
    request.setAttribute("nextExists", result != null && numResultsToReturn != 0 && result.length == numResultsToReturn + 1);
    request.setAttribute("startingSkip", 0);
    request.setAttribute("startingReturn", 20);
    request.getRequestDispatcher("/search.jsp").forward(request, response);
  }
}