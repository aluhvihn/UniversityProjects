/**
 * Copyright (C) 2008 by The Regents of the University of California
 * Redistribution of this file is permitted under the terms of the GNU
 * Public License (GPL).
 *
 * @author Junghoo "John" Cho <cho AT cs.ucla.edu>
 * @date 3/24/2008
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Bruinbase.h"
#include "SqlEngine.h"
#include "BTreeIndex.h"     // added for part d

using namespace std;

// external functions and variables for load file and sql command parsing
extern FILE* sqlin;
int sqlparse(void);


RC SqlEngine::run(FILE* commandline)
{
  fprintf(stdout, "Bruinbase> ");
  
  // set the command line input and start parsing user input
  sqlin = commandline;
  sqlparse();  // sqlparse() is defined in SqlParser.tab.c generated from
               // SqlParser.y by bison (bison is GNU equivalent of yacc)
  
  return 0;
}

bool useIndex(RC index_exists, const vector<SelCond>& cond) {
  // if (index_exists == RC_FILE_OPEN_FAILED)
  if (index_exists && cond.size()) {
    return false;
  }
  for (int i = 0; i < cond.size(); i++) {
    if (cond[i].attr == 2) {              // attr == 2 means value, not key - No index for value
      return false;
    }
    if (cond[i].comp == SelCond::NE) {    // if doing a not equals comparison, we have to check all of the tuples - index not used
      return false;
    }
    else {
      return true;                        // other comparisons (equality or range) can all use index
    }
  }
  return false;
}

/*
The select() function is called when the user issues the SELECT command.
The attribute in the SELECT clause is passed as the first input parameter attr 
(attr=1 means "key" attribute, attr=2 means "value" attribute, attr=3 means "*", and attr=4 means "COUNT(*)"). 
The table name in the FROM clause is passed as the second input parameter table.
The conditions listed in the WHERE clause are passed as the input parameter conds
*/
RC SqlEngine::select(int attr, const string& table, const vector<SelCond>& cond)
{
  RecordFile rf;   // RecordFile containing the table
  RecordId   rid;  // record cursor for table scanning
  
  RC     rc;
  int    key;
  string value;
  int    count;
  int    diff;

  IndexCursor indexCursor;
  BTreeIndex BTree;

  // look at the table file and open it
  if ((rc = rf.open(table + ".tbl", 'r')) < 0) {
    fprintf(stderr, "Error: table %s does not exist\n", table.c_str());
    return rc;
  }

  // start at the beginning
  rid.pid = rid.sid = 0;
  count = 0;
  // Not using index; default (original) method
  if (BTree.open(table+".idx", 'r')) {
    while (rid < rf.endRid()) {
      // read the tuple
      if ((rc = rf.read(rid, key, value)) < 0) {
        fprintf(stderr, "Error: while reading a tuple from table %s\n", table.c_str());
        goto exit_select;
      }

      // check the conditions on the tuple
      for (unsigned i = 0; i < cond.size(); i++) {
        // compute the difference between the tuple value and the condition value
        switch (cond[i].attr) {
          case 1:
            diff = key - atoi(cond[i].value);
            break;
          case 2:
            diff = strcmp(value.c_str(), cond[i].value);
            break;
        }

        // skip the tuple if any condition is not met
        switch (cond[i].comp) {
          case SelCond::EQ:
            if (diff != 0) goto next_tuple;
            break;
          case SelCond::NE:
            if (diff == 0) goto next_tuple;
            break;
          case SelCond::GT:
            if (diff <= 0) goto next_tuple;
            break;
          case SelCond::LT:
            if (diff >= 0) goto next_tuple;
            break;
          case SelCond::GE:
            if (diff < 0) goto next_tuple;
            break;
          case SelCond::LE:
            if (diff > 0) goto next_tuple;
            break;
        }
      }

      count++;

      // print the tuple 
      switch (attr) {
        case 1:  // SELECT key
          fprintf(stdout, "%d\n", key);
          break;
        case 2:  // SELECT value
          fprintf(stdout, "%s\n", value.c_str());
          break;
        case 3:  // SELECT *
          fprintf(stdout, "%d '%s'\n", key, value.c_str());
          break;
      }

      // move to the next tuple
      next_tuple:
        ++rid;
    }
  }
  // Using an index
  else {
    int searchKey, cond_value, cond_attr, upper_bound;
    searchKey = cond_value = cond_attr = upper_bound = -1;
    SelCond::Comparator cond_comp = SelCond::NOT_SET;
    bool read_tree = false; // May still have to read "values" of index for searches looking for a value

    for(unsigned i = 0; i < cond.size(); i++){
      cond_value = atoi(cond[i].value);
      cond_attr = cond[i].attr;
      cond_comp = cond[i].comp;
            
      if(cond_attr != 1){
        read_tree = true;
        continue;
      }
    
      if(cond_comp == SelCond::EQ){
        searchKey = cond_value;
        break;
      }

      // Ranges: (key >= searchKey), (key > searchKey)
      if(cond_comp == SelCond::GE) {
        if(searchKey < cond_value || searchKey == -1) searchKey = cond_value;
      }
      if(cond_comp == SelCond::GT){
        if(searchKey < cond_value + 1 || searchKey == -1) searchKey = cond_value;
      }

      // Ranges: (key <= searchKey), (key < searchKey)
      if(cond_comp == SelCond::LE) {
        if(upper_bound > cond_value || upper_bound == -1) upper_bound = cond_value;
      }
      if(cond_comp == SelCond::LT){
        if(upper_bound > cond_value + 1 || upper_bound == -1) upper_bound = cond_value;
      }
    }
     
    //Get an index cursor to point to the location of our lowerbound
    if(cond_comp == SelCond::NOT_SET || searchKey == -1){ // if cond_comp is NOT_SET, that means there were no conditions, so we would return all of that column
      indexCursor.eid = 0;
      indexCursor.pid = 1; // Furthest left leaf is pid = 1 due to our implementation (0 is tree data (height and rootpid), root is variable)
    }
    else
      BTree.locate(searchKey, indexCursor);
      // Scan through leaf nodes starting at our searchKey
      while(BTree.readForward(indexCursor, key, rid) == 0 && (searchKey <= upper_bound || upper_bound == -1) )
      {
        if (read_tree && attr != 4 && ((rc = rf.read(rid, key, value)) < 0)) {
          goto exit_select;
        }
        // See if tuple passes all our conditions
        for (unsigned i = 0; i < cond.size(); i++) 
        {
          if(attr == 4 && cond[i].attr !=1)
            continue;
            
          cond_comp = cond[i].comp;
          
          switch (cond[i].attr) {
            case 1:
              diff = key - atoi(cond[i].value);
              break;
            case 2:
              diff = strcmp(value.c_str(), cond[i].value);
              break;
          }

          // skip the tuple if any condition is not met
          switch (cond[i].comp) {
            case SelCond::EQ:
              if (diff != 0) goto index_next_tuple;
              break;
            case SelCond::NE:
              if (diff == 0) goto index_next_tuple;
              break;
            case SelCond::GT:
              if (diff <= 0) goto index_next_tuple;
              break;
            case SelCond::LT:
              if (diff >= 0) goto index_next_tuple;
              break;
            case SelCond::GE:
              if (diff < 0) goto index_next_tuple;
              break;
            case SelCond::LE:
              if (diff > 0) goto index_next_tuple;
              break;
          }
        }
        count++;

        // fprintf the tuple, need value to print
        if(!read_tree){
          if (attr != 4 && ((rc = rf.read(rid, key, value)) < 0)) {
            fprintf(stderr, "Error: cannot read tuple from table %s\n", table.c_str());
            goto exit_select;
          }
        }
        // print the tuple 
        switch (attr) {
          case 1:  // SELECT key
            fprintf(stdout, "%d\n", key);
            break;
          case 2:  // SELECT value
            fprintf(stdout, "%s\n", value.c_str());
            break;
          case 3:  // SELECT *
            fprintf(stdout, "%d '%s'\n", key, value.c_str());
            break;
        }
        
        index_next_tuple:
          continue;
    }
  }

  if (attr == 4) fprintf(stdout, "%d\n", count);
  rc = 0;

  // close the table file and return
  exit_select:
    BTree.close();
    rf.close();
    return rc;
}

/*
 when the user issues the command "LOAD movie FROM 'movieData.del'",
 you should create a RecordFile named movie.tbl (in the current working directory) and store all tuples in the file.
 If the file already exists, the LOAD command should append all records in the load file to the end of the table.
 Roughly, your implementation of the load function should open the input loadfile and the RecordFile,
 parse each line of the loadfile to read a tuple (possibly using SqlEngine::parseLoadLine()) and insert the tuple to the RecordFile.
 */
RC SqlEngine::load(const string& table, const string& loadfile, bool index)
{

  RecordFile rf;   // RecordFile containing the table
  RecordId   rid;  // record cursor for table scanning

  RC     rc;
  int    key;     
  string value;
  int    count;
  int    diff;
  string line;

  // With index
  if (index) {
  // Open/create the table file
    if ((rc = rf.open(table + ".tbl", 'w')) < 0) {
      fprintf(stderr, "Error: Unable to create table %s\n", table.c_str());
      return rc;
    }

    // Open loadfile
    ifstream input_data;
    input_data.open(loadfile.c_str());
    // Error check
    if (!input_data.is_open()) {
      fprintf(stderr, "Error: Unable to open %s to read data\n", loadfile.c_str());
      return RC_INVALID_ATTRIBUTE;
    }
    
    BTreeIndex BTree;
    BTree.open(table+".idx", 'w');

    // read from lines input_data until end of file
    while (input_data.good() && getline(input_data, line)) {
      // Get the key and value from the line
      if (parseLoadLine(line, key, value) < 0) {
        fprintf(stderr, "Error: Unable to parse data from file\n");
        return RC_INVALID_ATTRIBUTE;
      }
      // Append key and value to RecordFile rc
      if (rf.append(key, value, rid) < 0) {
        fprintf(stderr, "Error: Unable to append data to RecordFile\n");
        return RC_FILE_WRITE_FAILED;
      }
      BTree.insert(key, rid);
    }
  }
  // Without index
  else {
    // Open/create the table file
    if ((rc = rf.open(table + ".tbl", 'w')) < 0) {
      fprintf(stderr, "Error: Unable to create table %s\n", table.c_str());
      return rc;
    }

    // Open loadfile
    ifstream input_data;
    input_data.open(loadfile.c_str());
    // Error check
    if (!input_data.is_open()) {
      fprintf(stderr, "Error: Unable to open %s to read data\n", loadfile.c_str());
      return RC_INVALID_ATTRIBUTE;
    }

    // read from lines input_data until end of file
    while (input_data.good() && getline(input_data, line)) {
      // Get the key and value from the line
      if (parseLoadLine(line, key, value) < 0) {
        fprintf(stderr, "Error: Unable to parse data from file\n");
        return RC_INVALID_ATTRIBUTE;
      }
      // Append key and value to RecordFile rc
      if (rf.append(key, value, rid) < 0) {
        fprintf(stderr, "Error: Unable to append data to RecordFile\n");
        return RC_FILE_WRITE_FAILED;
      }
    }
  }
  
  return 0;
}

RC SqlEngine::parseLoadLine(const string& line, int& key, string& value)
{
  const char *s;
  char        c;
  string::size_type loc;
  
  // ignore beginning white spaces
  c = *(s = line.c_str());
  while (c == ' ' || c == '\t') { c = *++s; }
  
  // get the integer key value
  key = atoi(s);
  
  // look for comma
  s = strchr(s, ',');
  if (s == NULL) { return RC_INVALID_FILE_FORMAT; }
  
  // ignore white spaces
  do { c = *++s; } while (c == ' ' || c == '\t');
  
  // if there is nothing left, set the value to empty string
  if (c == 0) { 
    value.erase();
    return 0;
  }
  
  // is the value field delimited by ' or "?
  if (c == '\'' || c == '"') {
    s++;
  } else {
    c = '\n';
  }
  
  // get the value string
  value.assign(s);
  loc = value.find(c, 0);
  if (loc != string::npos) { value.erase(loc); }
  
  return 0;
}
