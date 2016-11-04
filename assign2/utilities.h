#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>

int countCols(ifstream);
int countRows(ifstream);
bool dataIsInteger(ifstream);
void backToBeginning(ifstream);
void checkExtant(ifstream);

#endif
