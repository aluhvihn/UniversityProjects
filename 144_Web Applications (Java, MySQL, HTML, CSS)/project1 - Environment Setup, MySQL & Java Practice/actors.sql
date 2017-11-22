CREATE TABLE Actors(	
  Name VARCHAR(40) NOT NULL,     	-- Name
  Movie VARCHAR(80) NOT NULL,     -- Movie
  Year INT NOT NULL,              -- Date of birth
  Role VARCHAR(40) NOT NULL
);

-- Import Actor Data
LOAD DATA LOCAL INFILE '~/data/actors.csv' INTO TABLE Actors
    FIELDS
        TERMINATED BY ','
        OPTIONALLY ENCLOSED BY '"'
    LINES
        TERMINATED BY '\n';

-- Give me the names of all the actors in the movie 'Die Another Day'.
SELECT Name FROM Actors WHERE Movie='Die Another Day';

-- Drop the table at the end
DROP TABLE Actors;