#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "planetinfo.h"

using namespace std;

void checkExtant(ifstream&);
void writeToFile(string, ofstream&);

/*
template <class InputIterator, class Input, class T>
InputIterator findName(InputIterator first,InputIterator last, const T& val)
{
  while (first!=last) {
    Input dummy=*first;
    if (dummy.name()==val) return first;
    ++first;
  }
  return last;
  }*/


////////////////////////////////////////////

int main() {

  string filename="input.txt";
  
  /*  //Prompt the user for input file so you can pick which case to do:
  string filename;
  cout << "\n" << "####################" <<endl;
  cout << "Full name of file to read: \n";
  cin >> filename;*/
  
  
  
  ifstream myInput;
  //ofstream myOutput;

  // Open input and output files for read/write:
  myInput.open( filename.c_str() );

  checkExtant(myInput);

  const int noOfObjects=10;
  vector<Planet> data(noOfObjects);
  
  for (int i = 0; i <= noOfObjects-1; i++) {
    string dummy_name;
    double dummy_mass;
    double dummy_x;
    double dummy_y;
    double dummy_vx;
    double dummy_vy;
    
    myInput >> dummy_name >> dummy_mass >> dummy_x >> dummy_y >>
      dummy_vx >> dummy_vy;
    data[i].setName(dummy_name);
    data[i].setMass(dummy_mass);
    data[i].setAllVars(dummy_x, dummy_y, dummy_vx, dummy_vy);
    cout << "Reading data about " << data[i].name() << "...\n";
  }

  myInput.close();
  
  SolarSystem dummy=SolarSystem(data);
  Planet palebluedot=dummy.Sun();
  
  cout << palebluedot.name() << endl;
}

////////////////////////////////////////////

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

// string:
void writeToFile(string A, ofstream &outstream) {
  outstream << A << endl;
}
