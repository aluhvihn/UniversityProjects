LOAD DATA LOCAL INFILE 'Users.dat.tmp' INTO TABLE Users
  FIELDS
    TERMINATED BY ','
    OPTIONALLY ENCLOSED BY '`'
  LINES
    TERMINATED BY '\n';

LOAD DATA LOCAL INFILE 'Items.dat.tmp' INTO TABLE Items
  FIELDS
    TERMINATED BY ','
    OPTIONALLY ENCLOSED BY '`'
  LINES
    TERMINATED BY '\n';

LOAD DATA LOCAL INFILE 'Categories.dat.tmp' INTO TABLE ItemCategories
  FIELDS
    TERMINATED BY ','
    OPTIONALLY ENCLOSED BY '`'
  LINES
    TERMINATED BY '\n';

LOAD DATA LOCAL INFILE 'Bids.dat.tmp' INTO TABLE Bids
  FIELDS
    TERMINATED BY ','
    OPTIONALLY ENCLOSED BY '`'
  LINES
    TERMINATED BY '\n';

UPDATE Items SET Buy_Price = NULL WHERE Buy_Price = 0.00;
UPDATE Items SET Latitude = NULL WHERE Latitude = '';
UPDATE Items SET Longitude = NULL WHERE Longitude = '';
UPDATE Items SET Location = NULL WHERE Location = '';
UPDATE Items SET Country = NULL WHERE Country = '';
UPDATE Users SET Location = NULL WHERE Location = '';
UPDATE Users SET Country = NULL WHERE Country = '';