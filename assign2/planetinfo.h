#ifndef PLANETINFO_H
#define PLANETINFO_H

class PlanetInfo {

 public:
  
  PlanetInfo(char name, double mass, double dist);
  // getters
  char name();
  double mass();
  double dist();
  // setters
  void setName(string name);
  void setMass(double mass);
  void setDistance(double dist);

 private:
  
  char m_name;
  double m_mass;
  double m_dist;
}

#endif
