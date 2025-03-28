#include <iostream> 
#include <cmath>
using namespace std;

class field{
protected:
	double *value;
public:

field(){
	value = new double[3];
	value[0] = 0.0;
	value[1] =	0.0;
	value[2] = 0.0;
	}

field(double x,double y,double z){
	value = new double[3];
	value[0] = x;
	value[1] = y;
	value[2] = z;
	}

field(const field &other){
	value = new double[3];
	for(int i=0; i < 3;i++){
		value[i] = other.value[i];
	}
}

~field(){
	delete[] value;
}

double operator[](int index) const {
	if(index < 0 || index >= 3)
		throw out_of_range("Index out of range");
	return value[index];
}

void printMagnitude(){
	cout << "Field Components:" << value[0] << "," << value[1] << "," << value[2] << endl;
}
};

class Electric :public field{

private:
	double calculatedEfield;

public:

Electric() :field() {}

Electric(double x,double y,double z) :field(x,y,z) {}

Electric(const Electric  &other) :field(other), calculatedEfield(other.calculatedEfield) {}

void calculateElectricfield(double r, double Q){
	const double epsilon_0 =  8.854187817e-12; 
	calculatedEfield = Q/(4*3.14159 * r * r * epsilon_0);
	}	

double getCalculatedEfield() const {return calculatedEfield;}

Electric operator+(const Electric &other) const { 
	Electric result(0,0,0); 
	for(int i=0; i < 3; ++i){
		result.value[i] = this->value[i] +  other.value[i];
	}
	result.calculatedEfield = this->calculatedEfield + other.calculatedEfield;
	return result;
}
friend ostream& operator<<(ostream &os, const Electric &ef){
	os << "Electric Field Components: (" << ef.value[0] << "," << ef.value[1] << "," << ef.value[2] << ")";
	os << ", Calculated Field: " << ef.calculatedEfield;
	return os;	
	}	 
};

class Magnetic :public field{
private:
	double calculatedMfield;
public:

Magnetic() :field() {}
Magnetic(double x, double y, double z):field(x,y,z) {}
Magnetic(const Magnetic &other):field(other), calculatedMfield(other.calculatedMfield) {}
void calculateMagneticfield(double r, double I){
	double const mu = 4 * 3.14159 * 1e-7;
	calculatedMfield = I/(2*3.14159 *r * mu);
	}
double getCalculateMfield() const {return calculatedMfield;}

Magnetic operator+(const Magnetic &other) const {
	Magnetic result(0,0,0);
	for(int i = 0; i < 3; ++i){
		result.value[i] = this->value[i] + other.value[i];
	}
	result.calculatedMfield = this->calculatedMfield + other.calculatedMfield;
	return result;
	}
friend ostream& operator<<(ostream &os, const Magnetic &mf){
	os << "Magnetic Field Components: (" << mf[0] << "," << mf[1] << "," << mf[2] << ")";
	os << ", Calculated field: " << mf.calculatedMfield;
	return os;
	}
};



int main(){


Electric efield(0,1e5,1e3);


Magnetic mfield(9e2,1e5,1e3);
cout << "Initial Electric: " << endl;
efield.printMagnitude();

cout << "Initial Magnetic: " << endl;
mfield.printMagnitude();

double Q =1e-6;
double r = .9;
efield.calculateElectricfield(r,Q);
cout << "Calclulated Electric Field at r=" << r << "meters from Q = " << Q << "C: "
	 <<efield.getCalculatedEfield() << " N/C" << endl;

double I = 3;
mfield.calculateMagneticfield(r,I);
cout<< "Calculated Magnetic Field at r = " << r << "m from I = " << I << "A:"
	<< mfield.getCalculateMfield() << " T" << endl;

Electric efield2(1e2,1e3,4e4);
Electric efieldsum = efield + efield2;
cout << "Sum of Electric Fields: " << efieldsum << " N/C" << endl;

Magnetic mfield2(2e5,3e2,1e2);
Magnetic mfieldsum = mfield + mfield2;
cout << "Sum of Magnetic Fields: " << mfieldsum << " T" << endl;
return 0;

}
