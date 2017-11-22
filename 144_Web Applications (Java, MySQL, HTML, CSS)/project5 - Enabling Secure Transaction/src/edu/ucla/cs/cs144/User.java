package edu.ucla.cs.cs144;

public class User {
  private String userID;
  private String rating;
  private Location location;
  private String country;
  
  public User(String userID, String rating, Location location, String country) {
    this.userID = userID;
    this.rating = rating;
    this.location = location;
    this.country = country;
  }
  
  public String getUserID() {
    return this.userID;
  }
  
  public String getRating() {
    return this.rating;
  }
  
  public Location getLocation() {
    return this.location;
  }
  
  public String getCountry() {
    return this.country;
  }
}