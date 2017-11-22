#!/bin/bash

# Drop any existing relevant tables in CS144 database IF EXISTS.
mysql CS144 < drop.sql

# Create all the relevant tables in CS144 database.
mysql CS144 < create.sql

# Compile and run the parser the generate the appropriate load files
ant clean
ant 
ant run-all
# ant run

# Duplicate elimination
# sort -u Categories.dat > Categories.dat.tmp
# sort -u Users.dat > Users.dat.tmp
# sort -u Items.dat > Items.dat.tmp
# sort -u Bids.dat > Bids.dat.tmp

sort Categories.dat | uniq > Categories.dat.tmp
sort Users.dat | uniq > Users.dat.tmp
sort Items.dat | uniq > Items.dat.tmp
sort Bids.dat | uniq > Bids.dat.tmp


# Load the data into MySQL.
mysql CS144 < load.sql

# Run queries
# mysql CS144 < queries.sql

# Remove all temporary files
rm ./*.dat*