#include <cmath>
#include <iostream>
#include <string>
#include <utilities.h>

using namespace std; 

main {

  //Prompt the user for input file so you can pick which case to do:
  string filename;

  cout << "" <<endl;
  cout << "####################" <<endl;
  cout << "Full name of file to read: \n";
  cin >> filename;
  
  // create the name of the output file for later:
  string outfile;
  string dummy1;
  dummy1=filename;
  string dummy2="out";
  outfile=dummy2+dummy1.erase(0,2);
  
  ifstream myInput;
  ofstream myOutput;

  // Open input and output files for read/write:
  myInput.open( filename.c_str() );
  myOutput.open( outfile.c_str() );

  checkExtant(myInput);
  
  cout << countRows
  //PlanetInfo data[len];

}

//////////////////////////////////////////////////////////////////

int countRows(ifstream &mystream) {
  int rows=0;
  int n;
 
  rows=count(istreambuf_iterator<char>(mystream), 
  istreambuf_iterator<char>(), '\n');
  cout << rows << " rows in file. \n";
  return rows;
}

// Check extant

