#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
//#include "planetinfo.h"

using namespace std;

void checkExtant(ifstream&);

struct PlanetInfo {
  string name;
  double mass;
  double dist;
};

bool sortByName(const PlanetInfo &lhs, const PlanetInfo &rhs) { return lhs.name < rhs.name; }
bool sortByMass(const PlanetInfo &lhs, const PlanetInfo &rhs) { return lhs.mass > rhs.mass; }
bool sortByDistance(const PlanetInfo &lhs, const PlanetInfo &rhs) { return lhs.dist > rhs.dist; }

void writeToFile(string, ofstream&);


////////////////////////////////////////////

main() {

  //Prompt the user for input file so you can pick which case to do:
  string filename;

  cout << "" <<endl;
  cout << "####################" <<endl;
  cout << "Full name of file to read: \n";
  cin >> filename;
  
  // create the name of the output file for later:
  string outhandle="output";
  string outname=outhandle+"_name_ordered.txt";
  string outmass=outhandle+"_mass_ordered.txt";
  string outdistance=outhandle+"_distance_ordered.txt";
  
  ifstream myInput;
  //ofstream myOutput;

  // Open input and output files for read/write:
  myInput.open( filename.c_str() );
  // myOutput.open( outfile.c_str() );

  checkExtant(myInput);

  const int numberOfPlanets=8;

  //typedef vector<PlanetInfo> planetVector;
  //planetVector data(numberOfPlanets);

  vector<PlanetInfo> data(numberOfPlanets);
  
  //  for (int i=0; i<numberOfPlanets; ++i) {
  for (int i = 0; i <= numberOfPlanets-1; i++) {
    myInput >> data[i].name >> data[i].mass >> data[i].dist;
    cout << "Reading data about " << data[i].name << "...\n";
  }

  myInput.close();

  // Sorting by name:

  ofstream myOutput1;
  myOutput1.open( outname.c_str() );

  sort(data.begin(), data.end(), sortByName);

  for (int i=0; i<numberOfPlanets; ++i) {
    ostringstream str;
    str << data[i].name;
    writeToFile(str.str(),myOutput1);
  }

  cout<< "\n";
  cout<< "Printed in alphabetical order into file " << outmass << ".\n";
  cout<< "\n";
  cout<< "\n";
  myOutput1.close();

  /////////////////////////////
  // Sorting by mass:

  ofstream myOutput2;
  myOutput2.open( outmass.c_str() );

  sort(data.begin(), data.end(), sortByMass);

  cout<< "The planet with the largest mass is " << data[0].name << ", \n";
  cout<< "while the planet with the smallest is " << data[numberOfPlanets-1].name << ".\n";
  cout<< "\n"; 

  for (int i=0; i<numberOfPlanets; ++i) {
    ostringstream str;
    str << data[i].name << " " << scientific << data[i].mass;
    writeToFile(str.str(),myOutput2);
  }

  cout<< "Printed in order of mass into file " << outmass << ".\n";
  cout<< "\n";
  cout<< "\n";
  myOutput2.close();

  /////////////////////////////
  // Sorting by distance:
  ofstream myOutput3;
  myOutput3.open( outdistance.c_str() );

  sort(data.begin(), data.end(), sortByDistance);

  cout<< "The planet furthest from Sol is " << data[0].name << ", \n";
  cout<< "while the planet closest is " << data[numberOfPlanets-1].name << ".\n";
  cout<< "\n";

  for (int i=0; i<numberOfPlanets; ++i) {
    ostringstream str;
    str << data[i].name << " " << left << setprecision(3) << fixed << data[i].dist;
    writeToFile(str.str(),myOutput3);
  }  

  cout<< "Printed in order of distance into file " << outdistance << ".\n"; 
  myOutput3.close();
  cout<< "\n";
  cout<< "\n";

  /////////////////////////////
  // Weighted average distance to the Sun of all the planets, \frac{\Sum mi*di}{\Sum mi}
  double sumMD=0;
  double sumM=0;
  for (int i=0; i<numberOfPlanets; ++i) {
    sumMD += data[i].mass * data[i].dist;
    sumM += data[i].mass;
      }

  double weighteddist=sumMD/sumM;
  
  cout << "The weighted average distance to the Sun of all planets is " << weighteddist << ".\n";
  cout<< "\n";
 
  /// END
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
