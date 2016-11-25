#ifndef PLANETINFO_H
#define PLANETINFO_H

#include <string>

using namespace std;

class PlanetInfo {

 public:

  PlanetInfo();
  PlanetInfo(string name, double mass, double dist);
  // getters
  string name();
  double mass();
  double dist();
  // setters
  void setName(string name);
  void setMass(double mass);
  void setDistance(double dist);

 private:
  
  string m_name;
  double m_mass;
  double m_dist;
};

#endif
