package edu.ucla.cs.cs144;

public class AuctionSearchTest {
   public static void main(String[] args1)
   {
      AuctionSearch as = new AuctionSearch();

      String message = "Test message";
      String reply = as.echo(message);
      System.out.println("Reply: " + reply);

      String query = "superman";
      SearchResult[] basicResults = as.basicSearch(query, 0, 20);
      System.out.println("Basic Search Query: " + query);
      System.out.println("Received " + basicResults.length + " results");
      for(SearchResult result : basicResults) {
         System.out.println(result.getItemId() + ": " + result.getName());
      }

      SearchRegion region =
            new SearchRegion(33.774, -118.63, 34.201, -117.38); 
      SearchResult[] spatialResults = as.spatialSearch("camera", region, 0, 20);
      System.out.println("Spatial Search");
      System.out.println("Received " + spatialResults.length + " results");
      for(SearchResult result : spatialResults) {
         System.out.println(result.getItemId() + ": " + result.getName());
      }

      String itemId = "1497595357";
      String item = as.getXMLDataForItemId(itemId);
      System.out.println("XML data for ItemId: " + itemId);
      System.out.println(item);

      // Add your own test here
      query = "superman";
      basicResults = as.basicSearch(query, 0, 100000);
      System.out.println("Basic Search Query: " + query);
      System.out.println("Received " + basicResults.length + " results");
      // for(SearchResult result : basicResults) {
      //    System.out.println(result.getItemId() + ": " + result.getName());
      // }
      query = "kitchenware";
      basicResults = as.basicSearch(query, 0, 100000);
      System.out.println("Basic Search Query: " + query);
      System.out.println("Received " + basicResults.length + " results");
      // for(SearchResult result : basicResults) {
      //    System.out.println(result.getItemId() + ": " + result.getName());
      // }
      query = "star trek";
      basicResults = as.basicSearch(query, 0, 100000);
      System.out.println("Basic Search Query: " + query);
      System.out.println("Received " + basicResults.length + " results");
      
      query = "star trek";
      basicResults = as.basicSearch(query, 0, -1);
      System.out.println("Basic Search Query: " + query);
      System.out.println("Received " + basicResults.length + " results");      

      itemId = "1045304791";
      item = as.getXMLDataForItemId(itemId);
      System.out.println("XML data for ItemId: " + itemId);
      System.out.println(item);

      itemId = "1045767117";
      item = as.getXMLDataForItemId(itemId);
      System.out.println("XML data for ItemId: " + itemId);
      System.out.println(item);
   }
}
