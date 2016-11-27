#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "planetinfo.h"
#include "utilities.h"
#include "evolution.h"

using namespace std; 

template <class Input, class T>
Input findName(typename vector<Input>::iterator first,typename vector<Input>::iterator last, const T& val)
{
  Input objectInVector;
  while (first!=last) {
    Input dummy=*first;
    if (dummy.name()==val) {
      objectInVector=*first;
      return objectInVector;
    }
    ++first;
  }
  objectInVector=*last;
  return objectInVector;
}

void evolveSystem(double, vector<Planet>&,int);
double ax(Planet, Planet);
double ay(Planet, Planet);

const int noOfObjects=10;
int noOfEffObjects;

ofstream myOutput1;
ofstream myOutput2;
ofstream myOutput3;
ofstream myOutput4;
ofstream myOutput5;
ofstream myOutput6;
ofstream myOutput7;
ofstream myOutput8;
ofstream myOutput9;
ofstream myOutput10;

////////////////////////////////////////////

int main() {

  cout << "\n" << "####################" <<endl; 
  string filename="input.txt";
  
  /*  //Prompt the user for input file so you can pick which case to do:
  string filename;
  cout << "Full name of file to read: \n";
  cin >> filename;*/
  
  // Prompt the user for total time and timestep:
  cout << "\nTotal time to evolve the system over? [days]" << endl;
  int totTimeDays;
  cin >> totTimeDays;
  //convert to sec:
  int tTot=totTimeDays*24*60*60;
  
  cout << "\nTime step? [days]" << endl;
  int timestepDays;
  cin >> timestepDays;
  //convert to sec:                                                                                                
  int dt=timestepDays*24*60*60;

  ifstream myInput;

  // Open input and output files for read/write:
  myInput.open( filename.c_str() );

  checkExtant(myInput);

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

  // Which bodies are we gonna model?
  
  //vector<ofstream> outputs(noOfObjects); // SEE QUESTION BELOW

  /*ofstream myOutput1;
  ofstream myOutput2;
  ofstream myOutput3;
  ofstream myOutput4;
  ofstream myOutput5;
  ofstream myOutput6;
  ofstream myOutput7;
  ofstream myOutput8;
  ofstream myOutput9;
  ofstream myOutput10;*/ 

  int whichModel=0;
  vector<Planet> system(noOfObjects);
  // Get (valid) input:
  while ( whichModel<1 || whichModel>2) {
    cout << "\nModel (1) just Earth, Moon and Sun or (2) the whole system? [1/2]" << endl;
    cin >> whichModel;
    if (whichModel==1) {
      cout << "Modelling only Earth, Moon and Sun." << endl;
      noOfEffObjects=3;

      // initialise system with only the three:
      system.resize(noOfEffObjects);
      //outputs.resize(noOfEffObjects);
      Planet earth=findName<Planet, string>(data.begin(),data.end(),"Earth");
      Planet sun=findName<Planet, string>(data.begin(),data.end(),"Sun");
      Planet moon=findName<Planet, string>(data.begin(),data.end(),"Moon");
      system[0]=earth;
      system[1]=moon;
      system[2]=sun;
      
      myOutput1.open(earth.outFilename());
      myOutput2.open(moon.outFilename());
      myOutput3.open(sun.outFilename());
      
    }
    else if (whichModel==2) {
      cout << "Modelling only Earth, Moon and Sun." << endl;
      noOfEffObjects=noOfObjects;
      //outputs.resize(noOfEffObjects);

      // System is the whole data set
      system.resize(noOfEffObjects);
      system=data;

      myOutput1.open(system[0].outFilename());
      myOutput2.open(system[1].outFilename());
      myOutput3.open(system[2].outFilename());
      myOutput4.open(system[3].outFilename());
      myOutput5.open(system[4].outFilename());
      myOutput6.open(system[5].outFilename());
      myOutput7.open(system[6].outFilename());
      myOutput8.open(system[7].outFilename());
      myOutput9.open(system[8].outFilename());
      myOutput10.open(system[9].outFilename());
      // ew

    }
    else {
      cout << "Please enter either 1 or 2 to choose.";
    }
  }

  /* for (int i=0; i<noOfEffObjects; i++){
    string dummy=system[i].outFilename();
    
    outputs[i].open(dummy.c_str());

    dummy="";
    dummy.clear();
    }*/
  // QUESTION: I played aroung with using a loop to define and open ofstreams efficiently
  // and not closing them each time, but could not find a nice way to write to a specific one.
  // Things I tried: pointers etc, fout, various string defn

  //do the time evolution:  
  int step=0;
  for (int t=0;t<=tTot;t+=dt) { // +1 due to definition of print in evol, fix maybe
    step++;
    evolveSystem(dt,system,step);
  }
  
  cout << "Done" << endl;

  /* Testing findName
  Planet palebluedot=findName<Planet, string>(data.begin(),data.end(),"Earth");
  cout << palebluedot.name() << endl; */

 
}

///////////////////////////////////////

void evolveSystem(double dt, vector<Planet> &data, int step) {
  vector<Planet> current=data;
  vector<Planet> next=current;

  cout << "Running " << step << "step of evo" << endl;

  for (int currentPlanet=0; currentPlanet<=noOfEffObjects-1; currentPlanet++) {

    // instatiate the total accelerations on currentPlanet;                                                                                                                              
    double axTot=0;
    double ayTot=0;

    // This sums all the other planet's accelerations on the current (calls accel functions from Planet class)                                                                           
    for (int j=currentPlanet+1; (j-currentPlanet)<=(noOfEffObjects-1); j++) {
      axTot+=ax(current[j%noOfEffObjects],current[currentPlanet]);
      ayTot+=ay(current[j%noOfEffObjects],current[currentPlanet]);
    }
    
    // pull current x,y,vx,vy;                                                                                                                                                           
    double currentX=current[currentPlanet].x();
    double currentY=current[currentPlanet].y();
    double currentVx=current[currentPlanet].vx();
    double currentVy=current[currentPlanet].vy();
    
    // time-evolving coords and vs of current planet:                                                                                                                                    
    double nextX= currentX + currentVx * dt + 1/2 * axTot * dt * dt;
    double nextY= currentY + currentVy * dt + 1/2 * ayTot * dt * dt;
    double nextVx= currentVx + axTot * dt;
    double nextVy= currentVy + ayTot * dt;
    
    // update vector entry with these:                                                                                                                                                   
    next[currentPlanet].setAllVars(nextX, nextY, nextVx, nextVy);
    
    ostringstream str;
    str << step << "    " << ((step-1)*dt)/(24*60*60) <<"    " << scientific << next[currentPlanet].x() <<
      "    " << next[currentPlanet].y();

    if (currentPlanet==0) writeToFile(str.str(), myOutput1);
    if (currentPlanet==1) writeToFile(str.str(), myOutput2); 
    if (currentPlanet==2) writeToFile(str.str(), myOutput3);
    if (currentPlanet==3) writeToFile(str.str(), myOutput4);
    if (currentPlanet==4) writeToFile(str.str(), myOutput5);
    if (currentPlanet==5) writeToFile(str.str(), myOutput6);
    if (currentPlanet==6) writeToFile(str.str(), myOutput7);
    if (currentPlanet==7) writeToFile(str.str(), myOutput8);
    if (currentPlanet==8) writeToFile(str.str(), myOutput9);
    if (currentPlanet==9) writeToFile(str.str(), myOutput10);

    str.str("");
  }
  // now update the original input vector with the new vector                                                                                                                            
  data=next;

}


double ax(Planet fromPlanet, Planet onPlanet) {
  const double G=6.674e-11;
  
  double radius=sqrt((onPlanet.x()-fromPlanet.x()) * (onPlanet.x()-fromPlanet.x()) +
		     (onPlanet.y()-fromPlanet.y()) * (onPlanet.y()-fromPlanet.y()));
  double xdir=(onPlanet.x()-fromPlanet.x());
  double accel=-G * fromPlanet.mass()*xdir/(radius*radius*radius);
  
  return accel;
}

double ay(Planet fromPlanet, Planet onPlanet) {
  const double G=6.674e-11;

  double radius=sqrt((onPlanet.x()-fromPlanet.x()) * (onPlanet.x()-fromPlanet.x()) +
                     (onPlanet.y()-fromPlanet.y()) * (onPlanet.y()-fromPlanet.y()));
  double ydir=(onPlanet.y()-fromPlanet.y());
  double accel=-G * fromPlanet.mass()*ydir/(radius*radius*radius);

  return accel;
}
