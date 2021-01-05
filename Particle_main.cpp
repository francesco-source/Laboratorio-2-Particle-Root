
#include "Particle.hpp"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TLegend.h"
#include "TMath.h"
#include "TMatrixD.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TStyle.h"

void macro() {
    gROOT->LoadMacro("ParticleType.cpp+");
    gROOT->LoadMacro("ResonanceType.cpp+");
    gROOT->LoadMacro("Particle.cpp+");
    gRandom->SetSeed();
    int n_gen = 100000;
    int num_particle = 120;
    TFile* file =
        new TFile("Particles.root", "RECREATE");
    TH1F* h1 = 
        new TH1F("Particles", "Particles", 7, 0, 7);
    TH1F* h2 = 
        new TH1F("theta", "Theta", 200, 0, TMath::Pi());
    TH1F* h3 = 
        new TH1F("phi", "phi", 200, 0, TMath::Pi() * 2);
    TH1F* pp = 
        new TH1F("Impulse", "Impulse", 200, 0, 5);
    TH1F* trasvp =
        new TH1F("TraversP", "Traverse Impulse", 100, 0, 5);
    TH1F* energy =
        new TH1F("Energy", "Energy of particle", 100, 0, 5);
    TH1F* massInvariant = 
        new TH1F("MassInvariant", "Mass invariant", 80, 0, 2);
    TH1F* massID =
        new TH1F("massID", "Mass invariant discord", 80, 0, 2);
    TH1F* massIC =
        new TH1F("massIC", "Mass invariant concorde", 80, 0, 2);
    TH1F* mass_p_k_d =
        new TH1F("mass_p_k_d", "Mass discord pion katon", 80, 0, 2);
    TH1F* mass_p_k_c =
        new TH1F("mass_p_k_c", "Mass concord pion katon", 80, 0, 2);
    TH1F* mass_inv_decad =
        new TH1F("mass_inv_decad", "Mass decadimenti", 80, 0, 2);

    Particle::AddParticleType("pioni+", 1, 0.13957);    // 0
    Particle::AddParticleType("pioni", -1, 0.13957);    // 1
    Particle::AddParticleType("kaoni+", 1, 0.49367);    // 2
    Particle::AddParticleType("kaoni", -1, 0.49367);    // 3
    Particle::AddParticleType("protoni+", 1, 0.93827);  // 4
    Particle::AddParticleType("protoni", -1, 0.93827);  // 5
    Particle::AddParticleType("k*", 0, 0.89166, 0.050); // 6

    Particle Part[num_particle];
    for (int i = 0; i < n_gen; ++i) {
        int counter = 0;
        for (int j = 0; j < 100; ++j) {

            double theta = gRandom->Rndm() * TMath::Pi();
            double phi = gRandom->Rndm() * 2 * TMath::Pi();
            double p = gRandom->Exp(1);
            pp->Fill(p);
            double pz = p * cos(theta);
            double px = p * sin(theta) * cos(phi);
            double py = p * sin(theta) * sin(phi);
            trasvp->Fill(sqrt(px * px + py * py));
            h2->Fill(theta);
            h3->Fill(phi);
            Part[j].SetP(px, py, pz);
            double num_generate = gRandom->Rndm();
            if (num_generate < 0.4) {
                Part[j].setter(0);
            }
            else if (num_generate < 0.8) {
                Part[j].setter(1);
            }
            else if (num_generate < 0.85) {
                Part[j].setter(2);
            }
            else if (num_generate < 0.9) {
                Part[j].setter(3);
            }
            else if (num_generate < 0.945) {
                Part[j].setter(4);
            }
            else if (num_generate < 0.99) {
                Part[j].setter(5);
            }
            else {
                Part[j].setter(6);
                if (num_generate < 0.995) {
                    Part[100 + counter].setter(0);
                    Part[100 + counter + 1].setter(3);
                    Part[j].Decay2body(Part[100 + counter],
                        Part[100 + counter + 1]);
                    mass_inv_decad->Fill(
                        Part[100 + counter].Mass_invariant(Part[100 + 
                            counter + 1]));
                }
                else {
                    Part[100 + counter].setter(1);
                    Part[100 + counter + 1].setter(2);
                    Part[j].Decay2body(Part[100 + counter], Part[100
                        + counter + 1]);
                    mass_inv_decad->Fill(
                        Part[100 + counter].Mass_invariant(Part[100 
                            + counter + 1]));
                }
                counter = counter + 2;
            }
            energy->Fill(Part[j].GetEnergy());
            if (Part[j].Get_index() >= 0) {
                h1->Fill(Part[j].Get_index());
            }
        }
        for (int k = 0; k < 100 + counter; ++k) {
         for (int j = k + 1; j < 100 + counter; ++j) {
           massInvariant->Fill(Part[k].Mass_invariant(Part[j]));
            if (Part[k].GetCharge() * Part[j].GetCharge() == -1) {
               massID->Fill(Part[k].Mass_invariant(Part[j]));
               }
            if (Part[k].GetCharge() * Part[j].GetCharge() == 1) {
               massIC->Fill(Part[k].Mass_invariant(Part[j]));
               }
            if ((Part[k].Get_index() == 0 && Part[j].Get_index() == 3)||
               (Part[k].Get_index() == 1 && Part[j].Get_index() == 2)||
               (Part[k].Get_index() == 3 && Part[j].Get_index() == 0)||
               (Part[k].Get_index() == 2 && Part[j].Get_index() == 1)){
               mass_p_k_d->Fill(Part[k].Mass_invariant(Part[j]));
                }
            if ((Part[k].Get_index() == 1 && Part[j].Get_index() == 3) ||
                (Part[k].Get_index() == 0 && Part[j].Get_index() == 2) ||
                (Part[k].Get_index() == 3 && Part[j].Get_index() == 1) ||
                (Part[k].Get_index() == 2 && Part[j].Get_index() == 0)) {
                mass_p_k_c->Fill(Part[k].Mass_invariant(Part[j]));
                }
            }
        }
    }
    std::cout << "num of pigreco +" << h1->GetBinContent(1) << "+/-"
        << h1->GetBinError(1) << "\n";
    std::cout << "num of pigreco -" << h1->GetBinContent(2) << "+/-"
        << h1->GetBinError(2) << "\n";
    std::cout << "num of K +" << h1->GetBinContent(3) << "+/-"
        << h1->GetBinError(3) << "\n";
    std::cout << "num of K -" << h1->GetBinContent(4) << "+/-"
        << h1->GetBinError(4) << "\n";
    std::cout << "num of P +" << h1->GetBinContent(5) << "+/-"
        << h1->GetBinError(5) << "\n";
    std::cout << "num of P-" << h1->GetBinContent(6) << "+/-"
        << h1->GetBinError(6) << "\n";
    std::cout << "num of k*" << h1->GetBinContent(7) << "+/-"
        << h1->GetBinError(7) << "\n";

    h1->Write();
    h2->Write();
    h3->Write();
    pp->Write();
    trasvp->Write();
    energy->Write();
    massInvariant->Write();
    massID->Write();
    massIC->Write();
    mass_p_k_d->Write();
    mass_p_k_c->Write();
    mass_inv_decad->Write();
    file->Close();
}
