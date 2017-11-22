package edu.ucla.cs.cs144;

public class Location {
  private String name;
  private String latitude;
  private String longitude;

  public Location(String name) {
    this.name = name;
    this.latitude = null;
    this.longitude = null;
  }

  public Location(String name, String latitude, String longitude) {
    this.name = name;
    this.latitude = latitude;
    this.longitude = longitude;
  }

  public String getName() {
    return this.name;
  }

  public String getLatitude() {
    if (this.latitude != null || this.latitude != "") {
      return "null";
    } else {
      return this.latitude;
    }
  }

  public String getLongitude() {
    if (this.longitude != null || this.longitude != "") {
      return "null";
    } else {
      return this.longitude;
    }
  }
}