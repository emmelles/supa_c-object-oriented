#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
#include "utilities.h"

// These are a bunch of bits of code that can be useful at any point.

//=============== COUNTCOLS =================//

// Counts the columns in the file (well really first line of file
// but who uses varying number of cols)
int countCols(ifstream &filename) {
  int cols=0;
  int n;
  string line; // you can probably tell I code in FORTRAN
 
  getline (filename, line);
  istringstream iss(line);

  // the internet helped
  do
    {
      string sub;
      iss >> sub;
      if (sub.length())
        ++cols;
    }
  while(iss);

  cout << cols << " columns in file... \n";
  return cols;
}

//=============== COUNTROWS =================//

int countRows(ifstream &mystream) {
  int rows=0;
  int n;
 
  rows=count(istreambuf_iterator<char>(mystream), 
  istreambuf_iterator<char>(), '\n');
  cout << rows << " rows in file. \n";
  return rows;
}

//=============== DATAISINTEGER =================//

// Looks for dots in your numbers, makes assumptions accordingly.
bool dataIsInteger(ifstream &mystream) {
  string DUMMY;
  
  mystream >> DUMMY;
  if (DUMMY.find(".") == string::npos) {
    cout << "Data is integers... \n";
    return true;
  }
  else {
    cout << "Data is floating point numbers... \n";
    return false;
    }
}

//=============== BACKTOBEGINNING =================//

// Calling this backToSquareOne next time.
void backToBeginning(ifstream &mystream) {
  mystream.clear();
  mystream.seekg(0, mystream.beg);    
}

//=============== CHECKEXTANT =================//

void checkExtant(ifstream &mystream) {
  if ( myInput.fail() ) {
    cout << "File does not exist. \n";
    exit(1); 
  }
  if (!myInput.is_open() ) {
    cout << "File failed to open. \n";
    exit(1);
  }
}
