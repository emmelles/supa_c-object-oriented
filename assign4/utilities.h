#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

void checkExtant(ifstream&);
void writeToFile(string, ofstream&);

#endif
