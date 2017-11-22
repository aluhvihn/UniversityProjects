package edu.ucla.cs.cs144;

import java.io.IOException;
import java.util.HashSet;
import java.util.LinkedList;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import org.apache.lucene.document.Document;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.search.ScoreDoc;

import edu.ucla.cs.cs144.DbManager;
import edu.ucla.cs.cs144.XMLConverter;

public class AuctionSearch implements IAuctionSearch {
   /* 
    * You will probably have to use JDBC to access MySQL data
    * Lucene IndexSearcher class to lookup Lucene index.
    * Read the corresponding tutorial to learn about how to use these.
    *
    * You may create helper functions or classes to simplify writing these
    * methods. Make sure that your helper functions are not public,
    * so that they are not exposed to outside of this class.
    *
    * Any new classes that you create should be part of
    * edu.ucla.cs.cs144 package and their source files should be
    * placed at src/edu/ucla/cs/cs144.
    *
    */

    public SearchResult[] basicSearch(String query, int numResultsToSkip, 
         int numResultsToReturn) {
        // LinkedList<SearchResult> results = new LinkedList<SearchResult>();
        SearchResult[] results = null;
        if (numResultsToReturn <= 0) {
            return new SearchResult[0];
        }
        try {
            SearchEngine se = new SearchEngine();
            TopDocs topDocs = se.performSearch(query, (numResultsToSkip + numResultsToReturn) );
            ScoreDoc[] hits = topDocs.scoreDocs;
            int resultRange = 0;
         
            //Check if requested skip amount is greater than number of hits
            if (hits.length < numResultsToSkip) {
                return new SearchResult[0];
            }

            if (topDocs.totalHits < (numResultsToReturn + numResultsToSkip) ) {
                results = new SearchResult[topDocs.totalHits - numResultsToSkip];
                resultRange = topDocs.totalHits;
            }
            else {
                results = new SearchResult[numResultsToReturn];
                resultRange = numResultsToReturn + numResultsToSkip;
            }

            //Add each search result to the array
            for (int i=numResultsToSkip; i < resultRange; i++) {
                Document doc = se.getDocument(hits[i].doc);
                // results.add(new SearchResult(doc.get("ItemID"), doc.get("Name")));
                results[i - numResultsToSkip] = new SearchResult(doc.get("ItemID"), doc.get("Name"));
            }
            // return results.toArray(new SearchResult[results.size()]);
            return results;
        } catch (IOException | ParseException ex) {
            ex.printStackTrace();
            System.exit(2);
            return null;
        }
    }

    public SearchResult[] spatialSearch(String query, SearchRegion region,
         int numResultsToSkip, int numResultsToReturn) {
        if (numResultsToReturn <= 0) {
            return new SearchResult[0];
        }
        //Get spatial index search results
        HashSet <String> spatResults = new HashSet <String>();
        try {
            Connection conn = DbManager.getConnection(true);

            Statement stmt = conn.createStatement();
            double lx = region.getLx(), ly = region.getLy(), rx = region.getRx(), ry = region.getRy();

            String spatial_query = String.format("SELECT * FROM ItemLocation "
                + "WHERE MBRContains(GeomFromText('Polygon((%f %f, %f %f, %f %f, %f %f, %f %f))'), coord)", 
                region.getLx(), region.getLy(), region.getLx(), region.getRy(), region.getRx(), region.getRy(),
                region.getRx(), region.getLy(), region.getLx(), region.getLy());

            
            ResultSet rs = stmt.executeQuery(spatial_query);

            while (rs.next()) {
                spatResults.add(rs.getString("ItemID"));
            }
            conn.close();
        } catch (SQLException ex) {
            ex.printStackTrace();
            System.exit(2);
        }

        // Perform basic search on the results
        LinkedList<SearchResult> results = new LinkedList<SearchResult>();
        try {
            SearchEngine se = new SearchEngine();
            TopDocs topDocs = se.performSearch(query, Integer.MAX_VALUE );
            ScoreDoc[] hits = topDocs.scoreDocs;

            if (hits.length < numResultsToSkip) {
                return new SearchResult[0];
            }

            // int skipped = 0, currentResults = 0;
            for (int i=0, skipped=0, currentResults=0; i < hits.length; i++) {
                Document doc = se.getDocument(hits[i].doc);
                //Only take intersection of the two results
                if (spatResults.contains(doc.get("ItemID"))) {
                    if (skipped < numResultsToSkip) {
                        skipped++;
                    } else if (currentResults < numResultsToReturn){
                        results.add(new SearchResult(doc.get("ItemID"), doc.get("Name")));
                        currentResults++;
                    } else {
                        break;
                    }
                }
            }
            return results.toArray(new SearchResult[results.size()]);
        } catch (IOException | ParseException ex) {
            ex.printStackTrace();
            System.exit(2);
            return null;
        }
    }

    public String getXMLDataForItemId(String ItemID) {
        XMLConverter converter = new XMLConverter(ItemID);
        return converter.getXML();
    }

    public String echo(String message) {
        return message;
    }
}
