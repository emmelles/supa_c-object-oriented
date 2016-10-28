#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath> // this is a *bunch* of headers...better way?

using namespace std;

int countCols(ifstream&);
int countRows(ifstream&);
bool dataIsInteger(ifstream&);
void backToBeginning(ifstream&);

/* template <class type> void printVect(ifstream &filename,int dim) {
  type x;
  type y;
  type z;
  if (dim==2) {
    filename >> x >> y;
    cout << "Components of " << dim << "D vector are " << x << " and " << y << endl;
  }
  else if (dim==3) {
    filename >> x >> y >> z;
    cout << "Components of " << dim << "D vector are " << x << ", " << y <<
      " and " << z << endl;   
  }
  } */ // WHY DOESN'T THIS WORK?

template <class type> type absVal(type x, type y, type z=0) {
  return sqrt(x*x+y*y+z*z); // this isn't overloaded but makes more sense to me...
}

template <class type> void writeToFile(type A, type B, type C, ofstream &outstream) {
  string str="  ";
  outstream << A << str <<  B << str << setprecision(2) << C << endl; 
}

template <class type> void writeToFile(type A, type B, type C, type D, ofstream &outstream) {
  string str="  ";
  outstream << A  << str << B  << str << C  << str << setprecision(2) << D << endl;
}

template <class type> void writeToFile(type A, ofstream &outstream) {
  outstream << A << endl;
}

//======================== MAIN ==========================//

main() {

  //Prompt the user for input file so you can pick which case to do:
  string filename;
  
  cout << "File to read? \n";
  cin >> filename ; // Pass this as ./main<<nameoffile.txt
  //filename="input3D_int.txt";
  cout << "Looking for " << filename << endl;
  cout << "How many lines of the file do you want to read? \n";

  int usernumber;
  cin >> usernumber;
  if (usernumber>0) {
    cout << "Extracting "<< usernumber << " lines." <<endl;
  }
  else {  
    cout << "Please enter a number that makes sense next time. \n";
    exit (1);
  }
  
  // create the name of the output file for later:
  string outfile;
  string dummy1;
  dummy1=filename;
  string dummy2="out";
  outfile=dummy2+dummy1.erase(0,2);
  
  ifstream myInput;
  ofstream myOutput;

  // Open input and output files for read/write:
  myInput.open( filename.c_str() );
  myOutput.open( outfile.c_str() );
  
  // Check extant
  if ( myInput.fail() ) {
    cout << "File does not exist. \n";
    exit(1); 
  }
  else if (!myInput.is_open() ) {
    cout << "File failed to open. \n";
    exit(1);
  }
  else {
    
    // Reading whole file
    int lin=0;

    // this counts the columns of first line only for brevity, so we're assuming const number
    int cols=countCols(myInput);
    backToBeginning(myInput);
    int rows=countRows(myInput);
    backToBeginning(myInput);
    bool isInteger=dataIsInteger(myInput);
    backToBeginning(myInput);
    
    //string currentLine;
    //for (int i=1; i<=rows; i++)
    while ( !myInput.eof() )  {
      
      float x;
      float y;
      float z=0;
      unsigned int xi;
      unsigned int yi;
      unsigned int zi=0;

      // This runs appropriately for any data type and size.
      // Running for integers:
      if ( isInteger ) {
	if (cols==2) {
	  myInput >> xi >> yi;
	  if ( !myInput.eof() ) {
	    cout << "Components of " << cols << "D vector are " << xi << " and " << yi << endl;
	    cout << "Absolute value: " << absVal(xi,yi) << endl;
	    writeToFile(xi, yi, absVal(xi,yi), myOutput);
	    lin++;
	  }
	}
	else if (cols==3) {
	  myInput >> xi >> yi >> zi;
	  if ( !myInput.eof() ) {
	    cout << "Components of " << cols << "D vector are " << xi << ", " << yi <<
	      " and " << zi << endl;
	    cout << "Absolute value: " << absVal(xi,yi,zi) << endl;
	    writeToFile(xi, yi, zi, absVal(xi,yi, zi), myOutput);
	    lin++;
	  } 
	}
      } 
      
      // Running for non-integers:
      else {
	if (cols==2) {
	  myInput >> x >> y;
	  if ( !myInput.eof() ) {
	    cout << "Components of " << cols << "D vector are " << x << " and " << y << endl;
	    cout << "Absolute value: " << absVal<float>(x,y) << endl;

	    ostringstream str;
	    str << left << setprecision(1) << fixed << x << "  " << y << "  "
	        << absVal<float>(x,y,z) ;

	    writeToFile(str.str(),myOutput);
	    
	    lin++;
	    if (lin >= usernumber) break;
	  }
	}
       	else if (cols==3) {
	  myInput >> x >> y >> z;
	  if ( !myInput.eof() ) {
	    cout << "Components of " << cols << "D vector are " << x << ", " << y <<
	      " and " << z << endl;
	    cout << "Absolute value: " << absVal<float>(x,y,z) << endl;
	    
	    ostringstream str;
	    str << left << setprecision(1) << fixed << x << "  " << y << "  " << z << "  "
	        << absVal<float>(x,y,z) ;
	    
	    writeToFile(str.str(),myOutput);
	    
	    lin++;
	    if (lin >= usernumber) break;
	  }
	}
      } // esle
      
    } // for loop closed
    cout << lin << " lines read. \n";
    
  } // if loop close
    
  myInput.close();
  myOutput.close();
  
} // main close

//===========================================================//

int countCols(ifstream &filename) {
  int cols=0;
  int n;
  string line; // you can probably tell I code in FORTRAN
 
  getline (filename, line);
  istringstream iss(line);

  // the internet helped
  do
    {
      string sub;
      iss >> sub;
      if (sub.length())
        ++cols;
    }
  while(iss);

  cout << cols << " columns in file. \n";
  return cols;
  
}

int countRows(ifstream &mystream) {
  int rows=0;
  int n;
 
  rows=count(istreambuf_iterator<char>(mystream), 
	     istreambuf_iterator<char>(), '\n');
  cout << rows << " rows in file. \n";
  return rows;
}

bool dataIsInteger(ifstream &mystream) {
  string DUMMY;
  
  mystream >> DUMMY;
  if (DUMMY.find(".") == string::npos) {
    cout << "Data is integers (assumed from first entry) \n";
    return true;
  }
  else {
    cout << "Data is floats (assumed from first entry) \n";
    return false;
    }
    
}

/* char sigFig(float f, int d)
{
  float dummy;
  for ( int i=1;i<=d; i++) {
    dummy=dummy*10;
    }
  cout <<  f <<

    
  round(f*10)
    
    char buf[16];
    sprintf(buf, "%.*g", d, f);
    return buf;
    } */

void backToBeginning(ifstream &mystream) {
  mystream.clear();
  mystream.seekg(0, mystream.beg);    
}


