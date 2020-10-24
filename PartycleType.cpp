#include"PartycleType.hpp"


 const char* PartycleType::getName() const{
	return fName;
}


double PartycleType::getMass() const {
	return fMass;
}


int PartycleType::getCharge() const {
	return fCharge;
}


void PartycleType::print() const {
	std::cout << "this are the propieties of the Partycle\n";
	std::cout << "| Name: " << fName << "\n";
	std::cout << "| Charge: " << fCharge<<"\n";
	std::cout << "| Mass: " << fMass << "\n";
}



double PartycleType::getWidth() const {
	return 0;
}

PartycleType::PartycleType(): fCharge{0}, fMass{0}, fName{"0"} {}

PartycleType::PartycleType(int charge, double mass,const char* name) : fCharge{ charge }, fMass{ mass }, fName{ name }{}
