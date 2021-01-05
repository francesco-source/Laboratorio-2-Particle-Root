#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include "ParticleType.hpp"

class ResonanceType : public PartycleType {
public:
	ResonanceType(double width, int charge, 
		double mass, const char* name);
	ResonanceType(const char* name);
	double GetWidth() const override;
	void print() const override;

private:
	const double fWidth = 0;
};
