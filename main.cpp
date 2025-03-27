#include <iostream> 
#include <cmath>
using namespace std:

class field{
private:
	double *value;
public:

field(){
	F = new double[3];
	F[0] = 0.0;
	F[1] =	0.0;
	F[2] = 0.0;
	}

field(double x,double y,double z){
	F = new double[3];
	F[0] = x;
	F[1] = y;
	F[2] = z;
	}

~field(){
	delete[]F;
}


double getX() const {return F[0];}
double getY() const {return F[1];}
double getZ() const {return F[2];} 

void setX(double x) {F[0] = x;}
void setY(double y) {F[1] = y;}
void setZ(double z) {F[2] = z;}

void printMagnitude(){
	cout << "Field Components:" << field[0] << "," << field[1] << "," << field[2] << endl;
	}

};
class Electric :public field{

private:
	double *E;

public:

Electric() :field() {}

Electric(double x,double y,double z) :field(x,y,z) {}

}
class Magnetic :public field{
private:
	double *M;

public:

Magnetic() :field() {}

Magnetic(double x, double y, double z) {}

};



int main(){

Electric field;
Electric field(0,1e5,1e3);

Magnetic field;
Magnetic field(0,1e5,1e3);
}
