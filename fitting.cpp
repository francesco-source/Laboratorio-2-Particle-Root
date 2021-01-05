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
#include "TMultiGraph.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TStyle.h"

void fit() {
  /////////////////////////////////////////////////////////////////////
  //////////////////Cosmetica//////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(1111);
  ///////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  TFile *file = new TFile("Particles.root");

  TH1F *particles = (TH1F *)file->Get("Particles");
  TH1F *theta = (TH1F *)file->Get("theta");
  TH1F *phi = (TH1F *)file->Get("phi");
  TH1F *impulse = (TH1F *)file->Get("Impulse");
  TH1F *trasvP = (TH1F *)file->Get("TraverseP");
  TH1F *energy = (TH1F *)file->Get("Energy");
  TH1F *massInvariant = (TH1F *)file->Get("MassInvariant");
  TH1F *massID = (TH1F *)file->Get("massID");
  TH1F *massIC = (TH1F *)file->Get("massIC");
  TH1F *massIPKD = (TH1F *)file->Get("mass_p_k_d");
  TH1F *massIPKC = (TH1F *)file->Get("mass_p_k_c");
  TH1F *massIDECAY = (TH1F *)file->Get("mass_inv_decad");

  TH1F *sub1 = new TH1F("sottrazione_1", "k*3-4", 80, 0, 2);
  TH1F *sub2 = new TH1F("sottrazione_2", "sottrazione 2", 80, 0, 2);
  TH1F *sub1a = new TH1F("sottrazione_1", "sottrazione 1", 80, 0, 2);
  TH1F *sub2a = new TH1F("sottrazione_2", "Sottrazione 2", 80, 0, 2);

  ///////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////

  sub1->Add(massIPKD, massIPKC, 1, -1);
  sub1a->Sumw2();
  sub1a->Add(massIPKD, massIPKC, 1, -1);

  sub2->Add(massID, massIC, 1, -1);
  sub2a->Sumw2();
  sub2a->Add(massID, massIC, 1, -1);

  ////////////////////////////////////////////////////////////////////
  ////////////// FITTING /////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////

  theta->Fit("pol0");
  phi->Fit("pol0");
  impulse->Fit("expo");
  massIDECAY->Fit("gaus", "", "", 0, 2);
  sub1a->Fit("gaus", "Q", "", 0.6, 1.2);
  sub2a->Fit("gaus", "Q", "", 0, 2);
  TF1 *fit1_gaus = sub1a->GetFunction("gaus");
  TF1 *fit2_gaus = sub2a->GetFunction("gaus");

  ////////////////////////////////////////////////////////////////////////
  /////////////Writing on File////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

  TFile *file2 = new TFile("Final_file.root", "RECREATE");

  theta->Write();
  phi->Write();
  impulse->Write();
  massIDECAY->Write();
  sub1->Write();
  sub2->Write();
  file2->Close();

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  ///////////////Printing on canvas/////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////

  TCanvas *firstFit = new TCanvas("Fit1", "Fit1");

  firstFit->Divide(2, 2);

  firstFit->cd(1);
  gPad->SetGrid();
  gPad->SetFillColor(42);
  gPad->SetFrameFillColor(44);
  particles->SetFillColor(kBlue - 2);
  particles->SetTitle("Abbondanza di particelle");
  particles->GetXaxis()->SetTitle("Particelle");
  particles->GetYaxis()->SetTitle("Numero di particelle");
  gPad->SetGrid();
  gPad->SetFrameFillColor(19);
  particles->Draw();

  firstFit->cd(2);
  gPad->SetGrid();
  gPad->SetFillColor(42);
  gPad->SetFrameFillColor(44);
  theta->SetTitle("Distribuzione di Theta");
  theta->GetXaxis()->SetTitle("Angolo(rad)");
  theta->GetYaxis()->SetTitle("Occorrenze");
  gPad->SetGrid();
  gPad->SetFrameFillColor(19);
  theta->Draw();

  firstFit->cd(3);
  gPad->SetGrid();
  gPad->SetFillColor(42);
  gPad->SetFrameFillColor(44);
  phi->SetTitle("Distribuzione di phi");
  phi->GetXaxis()->SetTitle("Angolo(rad)");
  phi->GetYaxis()->SetTitle("Occorrenze");
  gPad->SetGrid();
  gPad->SetFrameFillColor(19);
  phi->SetLineWidth(1);
  phi->SetLineColor(kBlue);
  phi->SetMarkerColor(kRed);
  phi->SetLineWidth(1);
  phi->Draw();

  firstFit->cd(4);
  gPad->SetGrid();
  gPad->SetFillColor(42);
  gPad->SetFrameFillColor(44);
  impulse->SetTitle("Distribuzione dell' Impulso");
  impulse->GetXaxis()->SetTitle("Modulo di P");
  impulse->GetYaxis()->SetTitle("Occorrenze");
  impulse->SetFillColor(kRed + 1);
  impulse->SetLineColor(kRed + 2);
  impulse->SetLineWidth(2);
  gPad->SetGrid();
  gPad->SetFrameFillColor(19);
  impulse->Draw();

  TCanvas *secondFit = new TCanvas("Fit2", "Fit2");
  secondFit->Divide(1, 3);
  secondFit->cd(1);
  gPad->SetGrid();
  gPad->SetFillColor(42);
  gPad->SetFrameFillColor(44);
  massIDECAY->SetTitle("K* teoriche");
  massIDECAY->GetXaxis()->SetTitle("Massa invariante");
  massIDECAY->GetYaxis()->SetTitle("Occorrenze");
  massIDECAY->SetFillColor(kGray + 1);
  massIDECAY->SetLineWidth(2);
  massIDECAY->Draw("Same");

  secondFit->cd(2);
  sub1->SetTitle("Prima sottrazione");
  sub1->GetXaxis()->SetTitle("Massa Invariante");
  sub1->GetYaxis()->SetTitle("Occorrenze");
  gPad->SetGrid();
  gPad->SetFillColor(42);
  gPad->SetFrameFillColor(44);
  sub1->Chisquare(fit1_gaus);
  sub1a->SetEntries(sub1a->Integral());
  sub1->SetLineColor(kBlack);
  sub1->SetFillColor(40);
  sub1->SetLineWidth(1);
  sub1a->Draw();
  sub1->Draw("Same");
  fit1_gaus->SetLineColor(kRed + 1);
  fit1_gaus->Draw("Same");

  secondFit->cd(3);
  sub2->SetTitle("Seconda sottrazione");
  sub2->SetLineColor(2);
  sub2a->SetEntries(sub2->Integral());
  sub2->GetXaxis()->SetTitle("Massa Invariante");
  sub2->GetYaxis()->SetTitle("Occorrenze");
  gPad->SetGrid();
  gPad->SetFillColor(42);
  gPad->SetFrameFillColor(44);
  sub2->SetFillColor(40);
  sub2->SetLineWidth(2);
  sub2a->Draw();
  sub1->Draw("Same");
  fit2_gaus->SetLineColor(2);
  fit2_gaus->SetLineWidth(2);
  fit2_gaus->Draw("Same");

  firstFit->Print("Fit_of_Particles.pdf");
  secondFit->Print("Second_fit.pdf");
