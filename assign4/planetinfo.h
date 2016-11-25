#ifndef PLANETINFO_H
#define PLANETINFO_H

#include <string>
#include <vector>

using namespace std;
const double G=6.674e-11;

class Planet {

 public:

  Planet();
  Planet(string name, double mass, double x, double y,
	 double vx, double vy);
  // getters
  string name();
  double mass();
  double x();
  double y();
  double vx();
  double vy();
  // setters
  void setName(string name);
  void setMass(double mass);
  void setX(double x);
  void setY(double y);
  void setVx(double vx);
  void setVy(double vy);
  void setCoords(double x, double y);
  void setVs(double vx, double vy);
  void setAllVars(double x, double y, double vx, double vy);

  // build accelerations due to Planet:
  double ax();
  double ay();

 private:
  
  string m_name;
  double m_mass;
  double m_x;
  double m_y;
  double m_vx;
  double m_vy;
  
};

class SolarSystem {

 public:
  SolarSystem();
  SolarSystem(vector<Planet> data);

  // setter:
  void setPlanets( vector<Planet> data);
  // getters:
  Planet Earth();
  Planet Sun();
  Planet Moon();
  
 private:
  Planet m_Sun;
  Planet m_Earth;
  Planet m_Moon;
  
  };

#endif