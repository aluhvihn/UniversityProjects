/* CS144
 *
 * Parser skeleton for processing item-???.xml files. Must be compiled in
 * JDK 1.5 or above.
 *
 * Instructions:
 *
 * This program processes all files passed on the command line (to parse
 * an entire diectory, type "java MyParser myFiles/*.xml" at the shell).
 *
 * At the point noted below, an individual XML file has been parsed into a
 * DOM Document node. You should fill in code to process the node. Java's
 * interface for the Document Object Model (DOM) is in package
 * org.w3c.dom. The documentation is available online at
 *
 * http://java.sun.com/j2se/1.5.0/docs/api/index.html
 *
 * A tutorial of Java's XML Parsing can be found at:
 *
 * http://java.sun.com/webservices/jaxp/
 *
 * Some auxiliary methods have been written for you. You may find them
 * useful.
 */

package edu.ucla.cs.cs144;

import java.io.*;
import java.text.*;
import java.util.*;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.FactoryConfigurationError;
import javax.xml.parsers.ParserConfigurationException;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import org.w3c.dom.Text;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;
import org.xml.sax.ErrorHandler;


class MyParser {
    
    static final String columnSeparator = "|*|";
    static DocumentBuilder builder;
    
    static final String[] typeName = {
	"none",
	"Element",
	"Attr",
	"Text",
	"CDATA",
	"EntityRef",
	"Entity",
	"ProcInstr",
	"Comment",
	"Document",
	"DocType",
	"DocFragment",
	"Notation",
    };
    
    static class MyErrorHandler implements ErrorHandler {
        
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
            System.out.println("There should be no errors " +
                               "in the supplied XML files.");
            System.exit(3);
        }
        
    }
    
    /* Non-recursive (NR) version of Node.getElementsByTagName(...)
     */
    static Element[] getElementsByTagNameNR(Element e, String tagName) {
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
    static Element getElementByTagNameNR(Element e, String tagName) {
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
    static String getElementText(Element e) {
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
    static String getElementTextByTagNameNR(Element e, String tagName) {
        Element elem = getElementByTagNameNR(e, tagName);
        if (elem != null)
            return getElementText(elem);
        else
            return "";
    }
    
    /* Returns the amount (in XXXXX.xx format) denoted by a money-string
     * like $3,453.23. Returns the input if the input is an empty string.
     */
    static String strip(String money) {
        if (money.equals(""))
            return money;
        else {
            double am = 0.0;
            NumberFormat nf = NumberFormat.getCurrencyInstance(Locale.US);
            try { am = nf.parse(money).doubleValue(); }
            catch (ParseException e) {
                System.out.println("This method should work for all " +
                                   "money values you find in our data.");
                System.exit(20);
            }
            nf.setGroupingUsed(false);
            return nf.format(am).substring(1);
        }
    }
    
    /* Process one items-???.xml file.
     */
    static void processFile(File xmlFile) {
        Document doc = null;
        try {
            doc = builder.parse(xmlFile);
        }
        catch (IOException e) {
            e.printStackTrace();
            System.exit(3);
        }
        catch (SAXException e) {
            System.out.println("Parsing error on file " + xmlFile);
            System.out.println("  (not supposed to happen with supplied XML files)");
            e.printStackTrace();
            System.exit(3);
        }
        
        /* At this point 'doc' contains a DOM representation of an 'Items' XML
         * file. Use doc.getDocumentElement() to get the root Element. */
        System.out.println("Successfully parsed - " + xmlFile);
        
        /* Fill in code here (you will probably need to write auxiliary
            methods). */
        // Create array for all the auctions from Item elements in doc
        // Element[] auctions = getElementsByTagNameNR(doc.getDocumentElement(), "Item");
        
        // for (int i=0; i<auctions.length; i++) {
        //     // recursiveDescent(auctions[i], 0);
        //     parseCurrentItem(auctions[i]);
        // }
        parseItems(doc);
    }
    
    static String convertDate(String dateString) {
        SimpleDateFormat oldFormat = new SimpleDateFormat("MMM-dd-yy HH:mm:ss");
        SimpleDateFormat sqlTimestamp = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        try {
            // Create Date object from 'date' String of old format
            Date date = oldFormat.parse(dateString);
            // Return String created with the sqlTimestamp
            return sqlTimestamp.format(date);
        } catch (ParseException pe) {
            System.out.println("ERROR: Cannot parse \"" + dateString + "\"");
            return "";
        }
    }

    // public static void parseCurrentItem(Element currentItem) {
    public static void parseItems(Document document) {
        // Create array for all the auctions from Item elements in doc
        Element[] auctions = getElementsByTagNameNR(document.getDocumentElement(), "Item");

        try {
            // Create writer (buffered, for performance) for item load file
            BufferedWriter itemFile = new BufferedWriter(new FileWriter("Items.dat", true));

            for (int i=0; i<auctions.length; i++) {
                // Parse item fields from attributes and elements
                String itemID = auctions[i].getAttribute("ItemID");
                String name = getElementTextByTagNameNR(auctions[i], "Name");
                String currentPrice = strip(getElementTextByTagNameNR(auctions[i], "Currently"));
                String buyPrice = strip(getElementTextByTagNameNR(auctions[i], "Buy_Price"));
                String firstBid = strip(getElementTextByTagNameNR(auctions[i], "First_Bid"));
                String numBids = getElementTextByTagNameNR(auctions[i], "Number_of_Bids");

                Element loc_element = getElementByTagNameNR(auctions[i], "Location");
                String latitude = loc_element.getAttribute("Latitude");
                String longitude = loc_element.getAttribute("Longitude");
                String location = getElementTextByTagNameNR(auctions[i], "Location");
                String country = getElementTextByTagNameNR(auctions[i], "Country");

                String dateStarted = convertDate(getElementTextByTagNameNR(auctions[i], "Started"));
                String dateEnds = convertDate(getElementTextByTagNameNR(auctions[i], "Ends"));
                String description = getElementTextByTagNameNR(auctions[i], "Description");

                // Truncate 'description' field at 4000 characters
                if (description.length() > 4000) {
                    description = description.substring(0, 4000);
                }
                // Seller ID is an attribute of Element Seller
                Element seller = getElementByTagNameNR(auctions[i], "Seller");
                String sellerID = seller.getAttribute("UserID");
                String item = itemID + ",`" + name + "`," + currentPrice + "," + buyPrice + ","
                            + firstBid + "," + numBids + ",`" + latitude + "`,`" + longitude + "`,`" 
                            + location + "`,`" + country + "`,`" + dateStarted + "`,`" + dateEnds + "`,`" + sellerID
                            + "`,`" + description + "`";
                itemFile.append(item);
                itemFile.newLine();

                parseCategory(auctions[i]);
                parseUserAndBid(auctions[i]);
                // parseUser(auctions[i]);
                // parseBid(auctions[i]);
            }

            itemFile.close();
        } catch (IOException e) {
            System.out.println("File error");
            System.exit(3);
        }

        // parseCategory(currentItem);
        // parseUser(currentItem);
        // parseBid(currentItem);
    }
    
    public static void parseCategory(Element currentItem) {
        try {
            BufferedWriter categoryFile = new BufferedWriter(new FileWriter("Categories.dat", true));

            String itemID = currentItem.getAttribute("ItemID");
            // Create array for all the categories from for this Item
            Element[] categories = getElementsByTagNameNR(currentItem, "Category");

            for (int i=0; i<categories.length; i++) {
                String categoryName = getElementText(categories[i]);
                String category = "`" + categoryName + "`," + itemID;
                categoryFile.append(category);
                categoryFile.newLine();
            }
            categoryFile.close();
        } catch (IOException e) {
            System.out.println("File error");
            System.exit(3);
        }
    }

    public static void parseUserAndBid(Element currentItem) {
        try {
            BufferedWriter userFile = new BufferedWriter(new FileWriter("Users.dat", true));
            BufferedWriter bidFile = new BufferedWriter(new FileWriter("Bids.dat", true));
            
            String itemID = currentItem.getAttribute("ItemID");

            // Get first user info from seller of currentItem
            Element user = getElementByTagNameNR(currentItem, "Seller");
            String userID = user.getAttribute("UserID");
            String userRating = user.getAttribute("Rating");
            String location = getElementTextByTagNameNR(currentItem, "Location");
            String country = getElementTextByTagNameNR(currentItem, "Country");

            userFile.append("`" + userID + "`," + userRating + ",`" + location + "`,`" + country + "`");
            userFile.newLine();
            
            // Create array for all the bids on this Item
            Element bidsElement = getElementByTagNameNR(currentItem, "Bids");
            Element[] bids = getElementsByTagNameNR(bidsElement, "Bid");

            for (int i=0; i<bids.length; i++) {
                user = getElementByTagNameNR(bids[i], "Bidder");
                userID = user.getAttribute("UserID");
                userRating = user.getAttribute("Rating");
                location = getElementTextByTagNameNR(user, "Location");
                country = getElementTextByTagNameNR(user, "Country");
                
                userFile.append("`" + userID + "`," + userRating + ",`" + location + "`,`" + country + "`");
                userFile.newLine();

                String time = convertDate(getElementTextByTagNameNR(bids[i], "Time"));
                String amount = strip(getElementTextByTagNameNR(bids[i], "Amount"));

                bidFile.append("`" + userID + "`,`" + time + "`," + itemID + "," + amount);
                bidFile.newLine();
            }
            userFile.close();

            bidFile.close();
        } catch (IOException e) {
            System.out.println("File error");
            System.exit(3);
        }
    }

    // public static void parseUser(Element currentItem) {
    //     try {
    //         BufferedWriter userFile = new BufferedWriter(new FileWriter("Users.dat", true));
            
    //         // Get first user info from seller of currentItem
    //         Element user = getElementByTagNameNR(currentItem, "Seller");
    //         String userID = user.getAttribute("UserID");
    //         String userRating = user.getAttribute("Rating");
    //         String location = getElementTextByTagNameNR(currentItem, "Location");
    //         String country = getElementTextByTagNameNR(currentItem, "Country");

    //         userFile.append("`" + userID + "`," + userRating + ",`" + location + "`,`" + country + "`");
    //         userFile.newLine();
            
    //         // Create array for all the bids on this Item
    //         Element bidsElement = getElementByTagNameNR(currentItem, "Bids");
    //         Element[] bids = getElementsByTagNameNR(bidsElement, "Bid");

    //         for (int i=0; i<bids.length; i++) {
    //             user = getElementByTagNameNR(bids[i], "Bidder");
    //             userID = user.getAttribute("UserID");
    //             userRating = user.getAttribute("Rating");
    //             location = getElementTextByTagNameNR(user, "Location");
    //             country = getElementTextByTagNameNR(user, "Country");
    //             userFile.append("`" + userID + "`," + userRating + ",`" + location + "`,`" + country + "`");
    //             userFile.newLine();
    //         }
    //         userFile.close();
    //     } catch (IOException e) {
    //         System.out.println("File error");
    //         System.exit(3);
    //     }
    // }

    // public static void parseBid(Element currentItem) {
    //     try {
    //         BufferedWriter bidFile = new BufferedWriter(new FileWriter("Bids.dat", true));
            
    //         String itemID = currentItem.getAttribute("ItemID");
    //         // Create array for all the bids on this Item
    //         Element bidsElement = getElementByTagNameNR(currentItem, "Bids");
    //         Element[] bids = getElementsByTagNameNR(bidsElement, "Bid");

    //         for (int i=0; i<bids.length; i++) {
    //             Element bidder = getElementByTagNameNR(bids[i], "Bidder");
    //             String userID = bidder.getAttribute("UserID");
    //             String time = convertDate(getElementTextByTagNameNR(bids[i], "Time"));
    //             String amount = strip(getElementTextByTagNameNR(bids[i], "Amount"));
    //             bidFile.append("`" + userID + "`,`" + time + "`," + itemID + "," + amount);
    //             bidFile.newLine();
    //         }
    //         bidFile.close();
    //     } catch (IOException e) {
    //         System.out.println("File error");
    //         System.exit(3);
    //     }
    // }

    public static void main (String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java MyParser [file] [file] ...");
            System.exit(1);
        }
        
        /* Initialize parser. */
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            factory.setValidating(false);
            factory.setIgnoringElementContentWhitespace(true);      
            builder = factory.newDocumentBuilder();
            builder.setErrorHandler(new MyErrorHandler());
        }
        catch (FactoryConfigurationError e) {
            System.out.println("unable to get a document builder factory");
            System.exit(2);
        } 
        catch (ParserConfigurationException e) {
            System.out.println("parser was unable to be configured");
            System.exit(2);
        }
        
        /* Process all files listed on command line. */
        for (int i = 0; i < args.length; i++) {
            File currentFile = new File(args[i]);
            processFile(currentFile);
        }
    }
}
