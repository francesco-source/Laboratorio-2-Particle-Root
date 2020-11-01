#include"Particle.hpp"
#include "TMath.h"
#include "TStyle.h"
#include "TH1F.h"
#include"TH2F.h"
#include "TH3F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TMatrixD.h"
#include "TFitResult.h"
#include "TROOT.h"
#include"TRandom.h"

int main()
{
	gRandom->SetSeed();
	int  n_gen=1e4;
	int num_particle=130;
TFile *file= new TFile("Particles.root","RECREATE");
TH1F * h1=new TH1F("hParticlesTypes", "test histogram", 7,0,7);
TH2F * h2= new TH2F("Angoli azimutali","",10,0,TMath::Pi(),10,0,2*TMath::Pi());
TH1F *pp =new TH1F("Impulse","P",1000,0,10e9);
TH1F *trasvp= new TH1F("Traverse impulse","",1000,0,10e9);
TH1F *energy=new TH1F("Energy of particle","Energy of particle",100,0,10e9);//viene malissimo
TH1F *massInvariant =new TH1F("MassInvariant","Mass invariant",1000,0,10e9);	
TH1F *massID =new TH1F ("massID","Mass invariant discord",1000,0,10e9);
TH1F * massIC= new TH1F("massIC", "Mass invariant concorde",1000,0,10e9);
TH1F *mass_p_k_d =new TH1F("mass_p_k_d","Mass discord pion katon",1000,0,10e9);
TH1F *mass_p_k_c =new TH1F("mass_p_k_c","Mass concord pion katon",1000,0,10e9);


	Particle::AddParticleType("pioni+",1,0.13957);//0
	Particle::AddParticleType("pioni",-1,0.13957);//1
	Particle::AddParticleType("kaoni+",1,0.49367);//2
	Particle::AddParticleType("kaoni",-1,0.49367);//3
	Particle::AddParticleType("protoni+",1,0.93827);//4
	Particle::AddParticleType("protoni",-1,0.93827);//5
	Particle::AddParticleType("K*",0,0.89166,0.050);//6
	//Particle::print_array();
	
	Particle Part[num_particle];
	for(int i =0;i<n_gen;++i){		
		int counter=0;
		for(int j=0;j<100+counter;++j){
			
			double theta=gRandom->Rndm()*TMath::Pi();
			double phi=gRandom->Rndm()*2*TMath::Pi();
			double p=gRandom->Exp(1e9);
			pp->Fill(p);
			double pz=p*cos(theta);
			double px=p*sin(theta)*cos(phi);
			double py=p*sin(theta)*sin(phi);
			trasvp->Fill(sqrt(px*px+py*py));			
			h2->Fill(theta,phi);
			Part[j].SetP(px,py,pz);
			double num_generate=gRandom->Rndm();
			double persentage=gRandom->Rndm();
		     
			if(num_generate<0.8){
				if(persentage<=0.5){
					Part[j].setter(0);
				}
				else{
					Part[j].setter(1);
				}
			}
			else if(num_generate>=0.8 && num_generate<0.9){
				if(persentage<=0.5){
					Part[j].setter(2);
				}
				else{
					Part[j].setter(3);
				}
			}
			else if(num_generate>=0.9 && num_generate<0.99){
				if(persentage<=0.5){
					Part[j].setter(4);
				}
				else{
					Part[j].setter(5);
				}
				
			}
			else if( num_generate<=1){
					Part[j].setter(6);
					if(persentage<=0.5){
					
					Part[100+counter].setter(0);
					Part[100+counter+1].setter(3);
					Part[j].Decay2body(Part[100+counter],Part[100+counter+1]);
					}
					else{
						Part[100+counter].setter(2);
						Part[100+counter+1].setter(1);
						Part[j].Decay2body(Part[100+counter],Part[100+counter+1]);
					}
					counter++;
					counter++;
			}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
							//Fill dell'energia
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////				
			if(Part[j].Get_index()>=0){
				h1->Fill(Part[j].Get_index());		//Fill particelle generate		
			}			
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		
		}
		for(int j=0;j<100;++j){
			energy->Fill(Part[j].GetEnergy());
		}
	  for(int k=0;k<100+counter;++k){
		  for(int j=k+1;j<100+counter;++j){
			massInvariant->Fill(Part[k].Mass_invariant(Part[j]));
			if(Part[k].GetCharge()!=Part[j].GetCharge()){
				massID->Fill(Part[k].Mass_invariant(Part[j]));
			}
			 if(Part[k].GetCharge()==Part[j].GetCharge()){
				massIC->Fill(Part[k].Mass_invariant(Part[j]));
			}
			 if((Part[k].Get_index()==0 && Part[j].Get_index()==3) ||(Part[k].Get_index()==1 && Part[j].Get_index()==2) ||
			  (Part[k].Get_index()==3 && Part[j].Get_index()==0) ||(Part[k].Get_index()==2 && Part[j].Get_index()==1)) {
				 mass_p_k_d->Fill(Part[k].Mass_invariant(Part[j]));
			 }
			 if((Part[k].Get_index()==1 && Part[j].Get_index()==3) ||(Part[k].Get_index()==0 && Part[j].Get_index()==2) ||
			 (Part[k].Get_index()==3 && Part[j].Get_index()==1) ||(Part[k].Get_index()==2 && Part[j].Get_index()==0) ) {
				 mass_p_k_c->Fill(Part[k].Mass_invariant(Part[j]));
			 }
		  }
	  }
	  }
	
	h1->Draw();
	h1->Write();
	h2->Draw();
	pp->Draw();
	trasvp->Draw();
	energy->Draw();
	massInvariant->Draw();
	massID->Draw();
	massIC->Draw();
	mass_p_k_d->Draw();
	mass_p_k_c->Draw();
	file->Write();
	file->Close();
}
