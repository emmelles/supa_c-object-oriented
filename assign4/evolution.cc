#include <vector>
#include <fstream>
#include <sstream>
#include "evolution.h"
#include "planetinfo.h"
#include "utilities.h"

// this evolves the input data according to the EoMs (note - modifies data itself)
void evolveSystem(double dt, vector<Planet> &data, int step) {
  vector<Planet> current=data;
  vector<Planet> next=current;

  cout << "Running " << step << "step of evo" << endl;

  for (int currentPlanet=0; currentPlanet<=noOfObjects-1; currentPlanet++) {    

    // instatiate the total accelerations on currentPlanet;
    double axTot=0;
    double ayTot=0;    

    // This sums all the other planet's accelerations on the current (calls accel functions from Planet class)
    for (int j=currentPlanet+1; (j-currentPlanet)<=(noOfObjects-1); j++) {
      axTot+=current[j%noOfObjects].ax();
      ayTot+=current[j%noOfObjects].ay();
    }
    
    // pull current x,y,vx,vy;
    double currentX=current[currentPlanet].x();
    double currentY=current[currentPlanet].y();
    double currentVx=current[currentPlanet].vx();
    double currentVy=current[currentPlanet].vy();

    // time-evolving coords and vs of current planet:
    double nextX=currentX*dt+1/2*axTot*dt*dt;
    double nextY=currentY*dt+1/2*ayTot*dt*dt;
    double nextVx=currentVx+axTot*dt;
    double nextVy=currentVy+ayTot*dt;

    // update vector entry with these:
    next[currentPlanet].setAllVars(nextX, nextY, nextVx, nextVy);

    ostringstream str;
    str << step << "    " << (step-1)*dt <<"    " << scientific << current[currentPlanet].x() <<
      "    " << current[currentPlanet].y() <<endl;

    switch(currentPlanet) {
    case 0:
      writeToFile(str.str(), myOutput1);
    case 1:
      writeToFile(str.str(), myOutput2);
    case 2:
      writeToFile(str.str(), myOutput3);
    case 3:
      writeToFile(str.str(), myOutput4);
    case 4:
      writeToFile(str.str(), myOutput5);
    case 5:
      writeToFile(str.str(), myOutput6);
    case 6:
      writeToFile(str.str(), myOutput7);
    case 7:
      writeToFile(str.str(), myOutput8);
    case 8:
      writeToFile(str.str(), myOutput9);
    case 9:
      writeToFile(str.str(), myOutput10);
    }

    str.str("");
    str.clear();

  }
  
  // now update the original input vector with the new vector
  data=next;

}
