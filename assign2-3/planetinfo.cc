#include <string>
#include "planetinfo.h"

using namespace std;

PlanetInfo::PlanetInfo() {
  m_name=" ";
  m_dist=0;
  m_mass=0;
}

PlanetInfo::PlanetInfo(string name, double mass, double dist) {
  m_name=name;
  m_dist=dist;
  m_mass=mass;
}

double PlanetInfo::mass() {return m_mass;}
double PlanetInfo::dist() {return m_dist;}
string PlanetInfo::name() {return m_name;}

void PlanetInfo::setName(string name) {m_name=name;}
void PlanetInfo::setMass(double mass) {m_mass=mass;}
void PlanetInfo::setDistance(double dist) {m_dist=dist;}

