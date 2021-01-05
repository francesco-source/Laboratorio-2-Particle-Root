#include "ParticleType.hpp"

const char* PartycleType::GetName() const
return fName; }

double PartycleType::GetMass() const
{
	return fMass;
}

int PartycleType::GetCharge() const
{
	return fCharge;
}

void PartycleType::print() const {
	std::cout << "this are the propieties"
		"of the Partycle\n";
	std::cout << "| Name: " << fName << "\n";
	std::cout << "| Charge: " << fCharge << "\n";
	std::cout << "| Mass: " << fMass << "\n";
}

double PartycleType::GetWidth() const
{
	return 0;
}

PartycleType::PartycleType() :
	fCharge{ 0 }, fMass{ 0 }, fName{ "0" } {}

PartycleType::PartycleType(int charge, double mass, const char* name)
	: fCharge{ charge }, fMass{ mass }, fName{ name } {}
