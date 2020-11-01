#include"Particle.hpp"
#include<cmath>
#include <cstdlib>

int Particle::fNParticleType = 0;
PartycleType* Particle::fParticleType[fMaxNumParticleType];


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Particle::Particle(const char* name, double x = 0, double y = 0, double z = 0) :fPx{ x }, fPy{ y }, fPz{ z }, fIParticle{FindParticle(name)}{}
 
Particle::Particle() : fPx{ 0 }, fPy{ 0 }, fPz{ 0 }, fIParticle{ -1 }{}


int Particle::FindParticle(const char* name)  {
	 for (int i = 0; i < fNParticleType; ++i) {		 
		 if (fParticleType[i]->GetName() == name) 
		 return i;		
	 }	
	 return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 int Particle::GetMax_Num_ParticleType() const {
	 return fMaxNumParticleType;
 }

 int Particle::Get_Num_ParticleType() const {
	 return fNParticleType;
 };

 int Particle::Get_index() const {
	 return fIParticle;
 }

 int Particle::GetCharge() const  {
	 return fParticleType[fIParticle]->GetCharge();
 }

 double Particle::GetMass()const {
	 return fParticleType[fIParticle]->GetMass();

 }

  const char* Particle::GetName() const {
	 return fParticleType[fIParticle]->GetName();
 }

 double Particle::Get_p_x()const  {
	 return fPx;
 }

 double Particle::Get_p_y()const {
	 return fPy;
 }

 double Particle::Get_p_z() const {
	 return fPz;
 }

  double Particle::GetWidth() const {
	 return fParticleType[fIParticle]->GetWidth();
 }
 
  void Particle::print_array() {
	 for (int i = 0; i < fNParticleType; ++i) {
		 fParticleType[i]->print();
	 }
 }

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 void Particle::AddParticleType(const char* name,int charge, double mass,double width) {    
	 if (FindParticle(name)==-1 && fNParticleType<fMaxNumParticleType ) {
		 if(width==0){
		 fParticleType[fNParticleType] =new PartycleType(charge,mass,name);}
		 else{
		 fParticleType[fNParticleType]= new ResonanceType(width,charge,mass,name);
		 }
		 ++fNParticleType;
		
	 }
	 else if(FindParticle(name)>=0 && fNParticleType < fMaxNumParticleType) {
		 std::cout << "Metodo add :Particella gia' presente.\n";
	 }
	 else {

		 std::cout << "Metodo add-find Particle:Limite massimo di elementi già raggiunto. \n";
	 }
 }


  void Particle::print_particle() const {
	 std::cout << "Indice della particella : (" << fIParticle << ") .\n";
	 std::cout << " Nome della particella : " << fParticleType[fIParticle]->GetName() << " .\n";
	 std::cout << "Le componenti dell' impulso di questa sono :\n";
	 std::cout << " Px= " << fPx << " kg*m/s";
	 std::cout << " Py= " << fPy << " kg*m/s";
	 std::cout << " Pz= " << fPz << " kg*m/s";
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

 void Particle::SetP(double x,double y,double z) {
	 fPx = x;
	 fPy = y;
	 fPz = z;
 }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



 double Particle::GetEnergy() const {
	double energy=sqrt(pow(GetMass(),2)+(fPx*fPx)+(fPy*fPy)+(fPz*fPz));
	 return energy;
 }

 double Particle::momentum_module() const {
	 return sqrt(fPx*fPx+fPy*fPy+fPz*fPz);
 }

 double Particle::Mass_invariant(Particle& p)const {
	 double energy = pow(GetEnergy() + p.GetEnergy(), 2);
	double momentum = ((fPx+p.Get_p_x())*(fPx+p.Get_p_x()))+((fPy+p.Get_p_y())*(fPy+ p.Get_p_y()))+((fPz+p.Get_p_z())*(fPz+p.Get_p_z())) ;
	 return  sqrt(energy - momentum);
 }

 





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////Funzione disponibile su virtuale   //////////////////////////////////////////////////////////////////////////////////////////

int Particle::Decay2body(Particle &dau1,Particle &dau2) const {
  if(GetMass() == 0.0){
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }
  
  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if(fIParticle > -1){ // add width effect

    // gaussian random numbers

    float x1, x2, w, y1, y2;
    
    double invnum = 1./RAND_MAX;
    do {
      x1 = 2.0 * rand()*invnum - 1.0;
      x2 = 2.0 * rand()*invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );
    
    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;
    y2 = x2 * w;

    massMot += fParticleType[fIParticle]->GetWidth() * y1;

  }

  if(massMot < massDau1 + massDau2){
    printf("Decayment cannot be preformed because mass is too low in this channel\n");
    return 2;
  }
  
  double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

  double norm = 2*M_PI/RAND_MAX;

  double phi = rand()*norm;
  double theta = rand()*norm*0.5 - M_PI/2.;
  dau1.SetP(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
  dau2.SetP(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));

  double energy = sqrt(fPx*fPx + fPy*fPy + fPz*fPz + massMot*massMot);

  double bx = fPx/energy;
  double by = fPy/energy;
  double bz = fPz/energy;

  dau1.Boost(bx,by,bz);
  dau2.Boost(bx,by,bz);

  return 0;
}
void Particle::Boost(double bx, double by, double bz)
{

  double energy = GetEnergy();

  //Boost this Lorentz vector
  double b2 = bx*bx + by*by + bz*bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx*fPx + by*fPy + bz*fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

  fPx += gamma2*bp*bx + gamma*bx*energy;
  fPy += gamma2*bp*by + gamma*by*energy;
  fPz += gamma2*bp*bz + gamma*bz*energy;
}
