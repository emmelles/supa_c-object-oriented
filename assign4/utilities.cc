#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string> 
#include "utilities.h"

using namespace std;

void checkExtant(ifstream &mystream) {
  if ( mystream.fail() ) {
    cout << "File does not exist. \n";
    exit(1);
  }
  if (!mystream.is_open() ) {
    cout << "File failed to open. \n";
    exit(1);
  }
}

void writeToFile(string A, ofstream &outstream) {
  outstream << A << endl;
}

