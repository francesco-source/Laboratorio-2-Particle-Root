#pragma once
#include<iostream>

class PartycleType {
public:
	PartycleType();
	PartycleType(int charge=0,double mass=0,const char* name=0);
	virtual void print() const;
	const char* getName() const  ;
	double getMass() const;
	int  getCharge() const ;
	virtual double getWidth()const;
	
private:
	 const char *fName;
	 const double fMass;
	 const int fCharge;
};
