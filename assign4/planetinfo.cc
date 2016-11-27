#include <string>
#include <cmath>
#include <algorithm>
#include "planetinfo.h"

using namespace std;

template <class InputIterator, class Input, class T>
InputIterator findName(InputIterator first,InputIterator last, const T& val)
{
  while (first!=last) {
    Input dummy=*first;
    if (dummy.name()==val) return first;
    ++first;
  }
  return last;
}


Planet::Planet() {
  m_name=" ";
  m_mass=0;
  m_x=0;
  m_y=0;
  m_vx=0;
  m_vy=0;
}

Planet::Planet(string name, double mass, double x,
	       double y, double vx, double vy) {
  m_name=name;
  m_mass=mass;
  m_x=x;
  m_y=y;
  m_vx=vx;
  m_vy=vy;
}

// build accelerations due to Planet:
double Planet::ax() {
  double r=sqrt(m_x*m_x+m_y*m_y);
  double accel=-G*m_mass*m_x/(r*r*r);
  return accel;
}

double Planet::ay() {
  double r=m_x*m_x+m_y*m_y;
  double accel=-G*m_mass*m_y/(r*r*r);
  return accel;
}

string Planet:: outFilename() {
  string dummy="output_"+m_name+".txt";
  return dummy;
}

string Planet::name() {return m_name;}
double Planet::mass() {return m_mass;}
double Planet::x() {return m_x;}
double Planet::y() {return m_y;}
double Planet::vx() {return m_vx;}
double Planet::vy() {return m_vy;}

void Planet::setName(string name) {m_name=name;}
void Planet::setMass(double mass) {m_mass=mass;}
void Planet::setX(double x) {m_x=x;}
void Planet::setY(double y) {m_y=y;}
void Planet::setVx(double vx) {m_vx=vx;}
void Planet::setVy(double vy) {m_vy=vy;}
void Planet::setCoords(double x, double y) {m_x=x; m_y=y;}
void Planet::setVs(double x, double y) {m_x=x; m_y=y;}
void Planet::setAllVars(double x, double y, double vx, double vy) {
  m_x=x;
  m_y=y;
  m_vx=vx;
  m_vy=vy;
}

/*SolarSystem:: SolarSystem()
{
  Planet m_Sun;
  Planet m_Earth;
  Planet m_Moon;

}

SolarSystem:: SolarSystem(vector<Planet> data)
{
  vector<Planet>::iterator whereSun = findName<vector<Planet>::iterator,Planet,string>(data.begin(), data.end(), "Sun");
  Planet m_Sun=*whereSun;

  vector<Planet>::iterator whereEarth = findName<vector<Planet>::iterator,Planet,string>(data.begin(), data.end(), "Earth");
  Planet m_Earth=*whereEarth;

  vector<Planet>::iterator whereMoon = findName<vector<Planet>::iterator,Planet,string>(data.begin(), data.end(), "Moon");
  Planet m_Moon=*whereMoon;
}

Planet SolarSystem::Earth() {return m_Earth;}
Planet SolarSystem::Sun() {return m_Sun;}
Planet SolarSystem::Moon() {return m_Moon;}

void SolarSystem::setPlanets( vector<Planet> data) {
  vector<Planet>::iterator whereSun = findName<vector<Planet>::iterator,Planet,string>(data.begin(), data.end(), "Sun");
  Planet m_Sun=*whereSun;

  vector<Planet>::iterator whereEarth = findName<vector<Planet>::iterator,Planet,string>(data.begin(), data.end(), "Earth");
  Planet m_Earth=*whereEarth;

  vector<Planet>::iterator whereMoon = findName<vector<Planet>::iterator,Planet,string>(data.begin(), data.end(), "Moon");
  Planet m_Moon=*whereMoon;
  }*/
