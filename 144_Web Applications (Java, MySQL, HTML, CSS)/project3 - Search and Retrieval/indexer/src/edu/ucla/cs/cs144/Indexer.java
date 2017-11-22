package edu.ucla.cs.cs144;

import java.io.IOException;
import java.io.StringReader;
import java.io.File;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.StringField;
import org.apache.lucene.document.TextField;
import org.apache.lucene.analysis.TokenStream;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;

public class Indexer {

    /** Creates a new instance of Indexer */
    public Indexer() {
    }
 
    private IndexWriter indexWriter = null;

    public IndexWriter getIndexWriter(boolean create) throws IOException {
        if (indexWriter == null) {
            Directory indexDir = FSDirectory.open(new File("/var/lib/lucene/ebayindex/"));
            IndexWriterConfig config = new IndexWriterConfig(Version.LUCENE_4_10_2, new StandardAnalyzer());
            indexWriter = new IndexWriter(indexDir, config);
        }
        return indexWriter;
    }

    public void closeIndexWriter() throws IOException {
        if (indexWriter != null) {
            indexWriter.close();
        }
    }

    public void rebuildIndexes() throws Exception{

        Connection conn = null;

        // create a connection to the database to retrieve Items from MySQL
        try {
            conn = DbManager.getConnection(true);
        } catch (SQLException ex) {
            System.out.println(ex);
        }


        /*
         * Add your code here to retrieve Items using the connection
         * and add corresponding entries to your Lucene inverted indexes.
             *
             * You will have to use JDBC API to retrieve MySQL data from Java.
             * Read our tutorial on JDBC if you do not know how to use JDBC.
             *
             * You will also have to use Lucene IndexWriter and Document
             * classes to create an index and populate it with Items data.
             * Read our tutorial on Lucene as well if you don't know how.
             *
             * As part of this development, you may want to add 
             * new methods and create additional Java classes. 
             * If you create new classes, make sure that
             * the classes become part of "edu.ucla.cs.cs144" package
             * and place your class source files at src/edu/ucla/cs/cs144/.
         * 
         */
        // Search queries to get all the index attributes
        getIndexWriter(true);
        Statement getItemFields = conn.createStatement();
        ResultSet rs = getItemFields.executeQuery("SELECT ItemID, Name, Description FROM Items");
        // PreparedStatement getItemFields = conn.prepareStatement("SELECT ItemID, Name, Description FROM Items");
        PreparedStatement getItemCategories = conn.prepareStatement("SELECT Category FROM ItemCategories WHERE ItemID = ?");


        String itemID, name, description;

        // ResultSet rs = getItemFields.executeQuery();

        while (rs.next()) {
            String categories = null;
            // Fill variables with result set attributes
            itemID = rs.getString("ItemID");
            name = rs.getString("Name");
            description = rs.getString("Description");
            // Set itemID parameter of PreparedStatement getItemCategories
            getItemCategories.setString(1, itemID);
            ResultSet crs = getItemCategories.executeQuery();

            while (crs.next()) {
                if (categories == null) {
                    categories = crs.getString("Category");
                }
                else {
                    categories = ( categories + " " + crs.getString("Category") );
                }
            }
            indexItems(itemID, name, description, categories);
        }

        closeIndexWriter();

        // close the database connection
        try {
            conn.close();
        } catch (SQLException ex) {
            System.out.println(ex);
        }
    }    

    public void indexItems(String itemID, String name, String description, String categories) throws Exception {
        IndexWriter indexWriter = getIndexWriter(false);
        Document doc = new Document();
        String fullSearchableText = name + " " + categories + " " + description;
        doc.add(new StringField("ItemID", String.valueOf(itemID), Field.Store.YES));
        doc.add(new StringField("Name", name, Field.Store.YES));
        doc.add(new StringField("Category", categories, Field.Store.NO));
        doc.add(new StringField("Description", description, Field.Store.NO));
        doc.add(new TextField("content", fullSearchableText, Field.Store.NO));
        indexWriter.addDocument(doc);
    }

    public static void main(String args[]) throws Exception {
        Indexer idx = new Indexer();
        idx.rebuildIndexes();
    }   
}
