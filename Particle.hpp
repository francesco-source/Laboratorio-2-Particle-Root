#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include"ResonanceType.hpp"


	struct Impul{
		double x = 0;
		double y = 0;
		double z = 0;
	};	

	class Particle {
	public:
		Particle(const char* name, double Px, double Py, double Pz);
		Particle();
		 int GetMax_Num_ParticleType() const;
		int Get_Num_ParticleType() const ;
		int Get_index() const;
		int GetCharge() const;
		double GetMass() const;
		const char* GetName() const;
		double Get_p_x() const;
		double Get_p_y() const ;
		double Get_p_z() const;
		double GetWidth() const;
		static void AddParticleType(const char*,int , double,double=0);
		void setter(int i);
		void setter(const char*);
		void SetP(double,double,double);
		static void print_array();
		void print_particle() const;
		double GetEnergy() const;
		double Mass_invariant(Particle& p)const;
		double momentum_module() const;
		int Decay2body(Particle &dau1,Particle &dau2) const;
	private:
		int static FindParticle(const char* name);
		void Boost(double bx, double by, double bz);
	    static const int fMaxNumParticleType=10;
		static int fNParticleType;
		static PartycleType* fParticleType[fMaxNumParticleType];
		int fIParticle;
		double fPx=0;
		double fPy=0;
		double fPz=0;
		
	};

#endif
