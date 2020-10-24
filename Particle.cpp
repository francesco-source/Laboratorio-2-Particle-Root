#pragma once

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
		 int getMax_Num_ParticleType() const;
		int get_Num_ParticleType() const ;
		int get_index() const;
		auto getCharge() const;
		double getMass() const;
		auto getName() const;
		auto get_p_x() const;
		auto get_p_y() const ;
		auto get_p_z() const;
		auto getWidth() const;
		static void AddParticleType(const char*,int , double,double=0);
		void setter(int i);
		void setter(const char*);
		void set_p(int ,int ,int);
		static void print_array();
		void print_particle() const;
		double Energy_of_Particle() const;
		double Mass_invariant(Particle& p)const;
		double momentum_module() const;
	private:
		int static FindParticle(const char* name);
	    static const int fMaxNumParticleType=10;
		static int fNParticleType;
		static PartycleType* fParticleType[fMaxNumParticleType];
		int fIParticle;
		double fPx=0;
		double fPy=0;
		double fPz=0;
	};
