package edu.ucla.cs.cs144;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class XMLConverter {

    private static boolean isSeller = false;
    private static boolean isBidder = true;

    private Connection conn;
    private String xmlString;
    private String itemID;

    public XMLConverter(String itemID) {
        try {
            this.itemID = itemID;
            this.xmlString = "";
            this.conn = DbManager.getConnection(true);
            this.parseResult();
            this.conn.close();
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void parseResult() throws SQLException{
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM Items WHERE ItemID = " + this.itemID);
        if (rs.next()) {

            this.xmlString += "<Item ItemID=\"" + this.itemID + "\">\n";
            
            this.xmlString += "  <Name>" + specialChars(rs.getString("Name")) + "</Name>\n";
            
            this.xmlString += parseCategories();

            this.xmlString += "  <Currently>$" + rs.getString("Currently") + "</Currently>\n";
            
            String buyPrice = rs.getString("Buy_Price");
            if (buyPrice != null) {
                this.xmlString += "  <Buy_Price>$" + buyPrice + "</Buy_Price>\n";
            }
            
            this.xmlString += "  <First_Bid>$" + rs.getString("First_Bid") + "</First_Bid>\n";

            this.xmlString += "  <Number_of_Bids>" + rs.getString("Number_of_Bids") + "</Number_of_Bids>\n";

            this.xmlString += parseBids(rs.getInt("Number_of_Bids"));

            String latitude = rs.getString("Latitude");
            String longitude = rs.getString("Longitude");
            if (latitude != null && longitude != null) {
                this.xmlString += "  <Location Latitude=\"" + latitude + "\" Longitude=\"" + longitude + 
                                    "\">" + specialChars(rs.getString("Location")) + "</Location>\n"; 
            } else {
                this.xmlString += "  <Location>" + specialChars(rs.getString("location")) + "</Location>\n";
            }

            this.xmlString += "  <Country>" + specialChars(rs.getString("Country")) + "</Country>\n";
            this.xmlString += "  <Started>" + convertDate(rs.getString("Started")) + "</Started>\n";
            this.xmlString += "  <Ends>" + convertDate(rs.getString("Ends")) + "</Ends>\n";
            this.xmlString += parseUsers(rs.getString("SellerID"), isSeller, null);
            this.xmlString += "  <Description>" + specialChars(rs.getString("Description")) + "</Description>\n";
            this.xmlString += "</Items>";
        }
    }

    private String specialChars(String inputString) {
        if (inputString == null) {
            return null;
        }
        String result = "";
        for (int i = 0; i < inputString.length(); i++) {
            char c = inputString.charAt(i);
            switch (c) {
            case '<':
                result += "&lt;";
                break;
            case '>':
                result += "&gt;";
                break;
            case '\"':
                result += "&quot;";
                break;
            case '\'':
                result += "&apos;";
                break;
            case '&':
                result += "&amp;";
                break;
            default:
                result += c;
                break;
            }
        }
        return result;
    }

    private String convertDate(String date) {
        DateFormat sqlTimestamp = new SimpleDateFormat("yyyy-MM-dd kk:mm:ss");
        DateFormat xmlFormat = new SimpleDateFormat("MMM-dd-yy kk:mm:ss");
        try {
            // Create Date object from sqlTimestamp
            Date d = sqlTimestamp.parse(date);
            // Return String created with xmlFormat
            return xmlFormat.format(d);
        } catch (ParseException ex) {
            ex.printStackTrace();
            System.out.format("Error parsing date \"%s\"!\n", date);
            return "";
        }
    }

    private String parseCategories() throws SQLException {
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT Category FROM ItemCategories WHERE ItemID = \"" + this.itemID + "\"");
        String categoryString = "";
        while (rs.next()) {
            categoryString += "  <Category>" + specialChars(rs.getString("Category")) + "</Category>\n";
        }
        return categoryString;
    }

    private String parseBids(int numBids) throws SQLException {
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT UserID, Time, Amount FROM Bids WHERE ItemID = " + this.itemID);
        String bidString = "";
        if (numBids > 0) {
            bidString += "  <Bids>\n";
            PreparedStatement prepStatement = conn.prepareStatement("SELECT Rating FROM Users WHERE UserID = ?");
            while(rs.next()) {
                bidString += "    <Bid>\n";
                String userID = rs.getString("UserID");
                prepStatement.setString(1, userID);
                bidString += parseUsers(userID, isBidder, prepStatement);

                this.xmlString += "    <Time>" + convertDate(rs.getString("Time")) + "</Time>\n";

                this.xmlString += "    <Amount>$" + rs.getString("Amount") + "</Amount>\n";
                bidString += "    </Bid>\n";
            }
            bidString += "  </Bids>\n";
        } else {
            bidString += "  <Bids />\n";
        }
        return bidString;
    }

    private String parseUsers(String userID, boolean type, PreparedStatement prepStatement) throws SQLException {
        String userString = "";
        if (type == isSeller) {
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT Rating FROM Users WHERE userID = \"" + userID + "\"");
            rs.next();
            userString += "  <Seller Rating=\"" + rs.getString("Rating") + "\" UserID=\"" + userID + "\" />\n";
        } else if (type == isBidder) {
            prepStatement.setString(1, userID);
            ResultSet brs = prepStatement.executeQuery();
            brs.next();
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT Location, Country FROM Users WHERE UserID = \"" + userID + "\"");
            rs.next();
            userString += "      <Bidder Rating=\"" + brs.getString("Rating") + "\" UserID=\"" + userID + "\">\n";
            String location = specialChars(rs.getString("Location"));
            String country = specialChars(rs.getString("Country"));
            if (location != null) {
                userString += "        <Location>" + location + "</Location>\n";
            }
            if (country != null) {
                userString += "        <Country>" + country + "</Country>\n";
            }
            userString += "      </Bidder>\n";
        }
        return userString;
    }

    public String getXML() {
        return this.xmlString;
    }
}
