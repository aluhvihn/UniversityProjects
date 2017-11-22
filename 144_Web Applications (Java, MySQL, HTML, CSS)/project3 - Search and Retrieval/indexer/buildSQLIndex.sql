CREATE TABLE IF NOT EXISTS ItemLocation (
  ItemID CHAR(100) PRIMARY KEY,     
  Latitude VARCHAR(64) NOT NULL,     
  Longitude VARCHAR(64) NOT NULL,     
FOREIGN KEY (ItemID) REFERENCES Items(ItemID) 
) ENGINE=MyISAM;

INSERT INTO ItemLocation (ItemID, Latitude, Longitude)     
  SELECT ItemID, Latitude, Longitude
  FROM Items
  WHERE Latitude IS NOT NULL AND Longitude IS NOT NULL;

ALTER TABLE ItemLocation ADD COLUMN coord POINT;
UPDATE ItemLocation SET coord=POINT(Latitude, Longitude);
ALTER TABLE ItemLocation MODIFY coord POINT NOT NULL;
CREATE SPATIAL INDEX spatial_index ON ItemLocation(coord);
