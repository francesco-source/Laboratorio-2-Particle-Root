#include "ResonanceType.hpp"

double ResonanceType::GetWidth() const
{
    return fWidth;
}

void ResonanceType::print() const {
    PartycleType::print();
    std::cout << "| Resonance width:"
        << fWidth << "\n";
}

ResonanceType::ResonanceType(const char* name)
    : fWidth{ 0 }, PartycleType(0, 0, name){};
ResonanceType::ResonanceType(double width, int coulomb,
    double mass,
    const char* name)
    : fWidth{ width }, PartycleType(coulomb, mass, name){};
