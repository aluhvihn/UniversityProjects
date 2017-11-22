package edu.ucla.cs.cs144;

public class Bid {
  private User userID;
  private String time;
  private String amount;
  
  public Bid(User userID, String time, String amount) {
    this.userID = userID;
    this.time = time;
    this.amount = amount;
  }
  
  public User getBidder() {
    return this.userID;
  }
  
  public String getTime() {
    return this.time;
  }
  
  public String getAmount() {
    return this.amount;
  }
}