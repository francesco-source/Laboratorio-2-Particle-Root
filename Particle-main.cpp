#include "PartycleType.hpp"
#include"ResonanceType.hpp"
#include"Particle.hpp"
int main()
{
	/*PartycleType p0(1, 1, "elettrone");
	ResonanceType p1(40,1,1000,"protone");
	PartycleType *particles[2];
	particles[0]= &p0;
	particles[1]= &p1;
	for (int i = 0; i < 2; ++i) {
		particles[i]->print();
	}

	return 0;*/


	Particle::AddParticleType("elettrone", 2, 20, 30);
	Particle::AddParticleType("positrone", -1, 30, 124.32);
	Particle::AddParticleType("antineutrone",2,20,200);
	Particle::AddParticleType("muone", 100, 20.45634344343);
	Particle::AddParticleType("neutrino", 1, 2, 5);
	Particle P("muone", 3, 5, 1);
	/*std::cout << P.getMass();
	P.setter(2);
	std::cout << P.get_index();*/
	P.print_array();







}
