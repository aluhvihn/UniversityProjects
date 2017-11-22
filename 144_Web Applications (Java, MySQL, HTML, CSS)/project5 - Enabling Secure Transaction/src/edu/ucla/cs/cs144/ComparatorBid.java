package edu.ucla.cs.cs144;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Comparator;
import java.util.Date;

public class ComparatorBid implements Comparator<Bid>{
  public ComparatorBid() {}

  @Override
  public int compare(Bid bid1, Bid bid2) {
    Date date1 = null, date2 = null;
    DateFormat format = new SimpleDateFormat("MMM-dd-yy kk:mm:ss");
    try {
      date1 = format.parse(bid1.getTime());
      date2 = format.parse(bid2.getTime());
    } catch (ParseException e) {
      System.exit(2);
    }
    return date1.compareTo(date2);
  }
}