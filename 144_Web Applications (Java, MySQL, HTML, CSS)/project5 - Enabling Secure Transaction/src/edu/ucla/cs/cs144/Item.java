package edu.ucla.cs.cs144;

public class Item {
  private String itemID;
  private String name;
  private String[] categories;
  private String currently;
  private String buy_price;
  private String first_bid;
  private String number_of_bids;
  private Bid[] bids;
  private Location location;
  private String country;
  private String started;
  private String ends;
  private User seller;
  private String description;

  public Item(String itemID) {
    this.itemID = itemID;
  }

  public void setName(String name) {
    this.name = name;
  }

  public void setCategories(String[] categories) {
    this.categories = categories;
  }

  public void setCurrently(String currently) {
    this.currently = currently;
  }

  public void setBuyPrice(String buy_price) {
    this.buy_price = buy_price;
  }

  public void setFirstBid(String first_bid) {
    this.first_bid = first_bid;
  }

  public void setNumberOfBids(String number_of_bids) {
    this.number_of_bids = number_of_bids;
  }

  public void setBids(Bid[] bids) {
    this.bids = bids;
  }

  public void setLocation(Location location) {
    this.location = location;
  }

  public void setCountry(String country) {
    this.country = country;
  }

  public void setStarted(String started) {
    this.started = started;
  }

  public void setEnds(String ends) {
    this.ends = ends;
  }

  public void setSeller(User seller) { 
    this.seller = seller;
  }

  public void setDescription(String description) {
    this.description = description;
  }

  public String getItemID() {
    return this.itemID;
  }

  public String getName() {
    return this.name;
  }

  public String[] getCategories() {
    return this.categories;
  }

  public String getCurrently() {
    return this.currently;
  }

  public String getBuyPrice() {
    return this.buy_price;
  }

  public String getFirstBid() {
    return this.first_bid;
  }

  public String getNumberOfBids() {
    return this.number_of_bids;
  }

  public Bid[] getBids() {
    return this.bids;
  }

  public Location getLocation() {
    return this.location;
  }

  public String getCountry() {
    return this.country;
  }

  private String escapeSpecialString(String string) {
    String result = "";
    for (int i = 0; i < string.length(); i++) {
      result += escapeSpecialChar(string.charAt(i));
    }
    return result;
  }

  private String escapeSpecialChar(char c) {
    switch (c) {
    case '\\':
      return "\\\\";
    case '\'':
      return "\\\'";
    case '\"':
      return "\\\"";
    default:
      return "" + c;
    }
  }

  public String getAddress() {
    return escapeSpecialString(this.location.getName() + " " + this.country);
  }

  public String getStarted() {
    return this.started;
  }

  public String getEnds() {
    return this.ends;
  }

  public User getSeller() { 
    return this.seller;
  }

  public String getDescription() {
    return this.description;
  }
}