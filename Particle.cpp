#include"Particle.hpp"
#include<cmath>

int Particle::fNParticleType = 0;
PartycleType* Particle::fParticleType[fMaxNumParticleType];
Particle::Particle(const char* name, double x = 0, double y = 0, double z = 0) :fPx{ x }, fPy{ y }, fPz{ z }, fIParticle{FindParticle(name)}{}
 
Particle::Particle() : fPx{ 0 }, fPy{ 0 }, fPz{ 0 }, fIParticle{ 0 }{}


int Particle::FindParticle(const char* name)  {
	 for (int i = 0; i < fNParticleType; ++i) {		 
		 if (fParticleType[i]->getName() == name) return i;
		 	
		
	 }
	
	std::cout << "index not found\n"; 
	 return -1;
}

 int Particle::getMax_Num_ParticleType() const {
	 return fMaxNumParticleType;
 }

 int Particle::get_Num_ParticleType() const {
	 return fNParticleType;
 };

 int Particle::get_index() const {
	 return fIParticle;
 }

 auto Particle::getCharge() const  {
	 return fParticleType[fIParticle]->getCharge();
 }

 double Particle::getMass()const {
	 return fParticleType[fIParticle]->getMass();

 }

 auto Particle::getName() const {
	 return fParticleType[fIParticle]->getName();
 }

 auto Particle::get_p_x()const  {
	 return fPx;
 }

 auto Particle::get_p_y()const {
	 return fPy;
 }

 auto Particle::get_p_z() const {
	 return fPz;
 }
 //const char* name, int carica, double mass.
 void Particle::AddParticleType(const char* name,int charge, double mass,double width) {    
	 if (FindParticle(name)==-1 && fNParticleType<fMaxNumParticleType) {
		 fParticleType[fNParticleType] =new ResonanceType(width,charge,mass,name);
		 ++fNParticleType;

	 }
	 else if(FindParticle(name)>=0 && fNParticleType < fMaxNumParticleType) {
		 std::cout << "Metodo add :Particella gia' presente.\n";
	 }
	 else {

		 std::cout << "Metodo add :Limite massimo di elementi già raggiunto.\n";
	 }
 }

 void Particle::setter(int i ) {
	 if (i >= 0 && i < fNParticleType) {
		 fIParticle = i;
	 }
	 else if (i >= fNParticleType && i<fMaxNumParticleType) {
		 std::cout << "Elemento con tale indice non ancora incluso.\n";
	 }
	 else {
		 std::cout << "Indice oltre la dimensione.\n";
	 }
}

 void Particle::setter(const char* name) {
	 if (FindParticle(name) >= 0) {
		 fIParticle = FindParticle(name);
	 }
	 else if (FindParticle(name) == -1) {
		 std::cout << "Indice non presente.\n";
	 }
 }

 void Particle::print_array() {
	 for (int i = 0; i < fNParticleType; ++i) {
		 fParticleType[i]->print();
	 }
 }

 void Particle::print_particle() const {
	 std::cout << "Indice della particella : (" << fIParticle << ") .\n";
	 std::cout << " Nome della particella : " << fParticleType[fIParticle]->getName() << " .\n";
	 std::cout << "Le componenti dell' impulso di questa sono :\n";
	 std::cout << " Px= " << fPx << " kg*m/s";
	 std::cout << " Py= " << fPy << " kg*m/s";
	 std::cout << " Pz= " << fPz << " kg*m/s";
 }


 double Particle::Energy_of_Particle() const {
	 double mass_2 = pow(fParticleType[fIParticle]->getMass(), 2);
	 double momentum_2 = pow(fPx, 2) + pow(fPy, 2) + pow(fPz, 2);
	 double energy = pow(momentum_2 + mass_2, 0.5);
	 return energy;
 }
 double Particle::momentum_module() const {
	 double momentum_2 = pow(fPx, 2) + pow(fPy, 2) + pow(fPz, 2);
	 double momentum = pow(momentum_2, 0.5);
	 return momentum;
 }
 double Particle::Mass_invariant(Particle& p)const {
	 double energy = pow(Energy_of_Particle() + p.Energy_of_Particle(), 2);
	 double momentum = pow(momentum_module() + p.momentum_module(), 2);
	 double mass_invariant = pow(energy - momentum, 0.5);
	 return mass_invariant;
 }

 void Particle::set_p(int x,int y,int z) {
	 fPx = x;
	 fPy = y;
	 fPz = z;
 }

 auto Particle::getWidth() const {
	 return fParticleType[fIParticle]->getWidth();
 }
