#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <planetinfo.h>

using namespace std;

void checkExtant(ifstream&);

main {

  //Prompt the user for input file so you can pick which case to do:
  string filename;

  cout << "" <<endl;
  cout << "####################" <<endl;
  cout << "Full name of file to read: \n";
  cin >> filename;
  
  // create the name of the output file for later:
  string outhandle="output";
  string outfile_name=outhandle+"_name_ordered.txt";
  string outfile_mass=outhandle+"_mass_ordered.txt";
  string outfile_distance=outhandle+"_distance_ordered.txt";
  
  ifstream myInput;
  //ofstream myOutput;

  const int numberOfPlanets=9;

  // Open input and output files for read/write:
  myInput.open( filename.c_str() );
  // myOutput.open( outfile.c_str() );

  checkExtant(myInput);

  typedef vector<PlanetInfo> planetVector;
  planetVector data(numberOfPlanets);

  for (i=0; i<numberOfPlanets; ++i) {
    myInput >> planetVector[i].name >> planetVector[i].mass >> planetVector[i].distance;
    cout << "Reading " << planetVector[i] <<endl;
  }

  myInput.close();
  
}

//////////////////////////////////////////////////////////////////

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
