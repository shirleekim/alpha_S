#define recoMass_cxx
#include "recoMass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void recoMass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L recoMass.C
//      root> recoMass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   Double_t theta_min = M_PI/2.-0.55;
   Double_t theta_max = M_PI/2.+0.55;

   double r_cone = 0.5;

      Double_t sumE1, sumpx1, sumpy1,sumpz1;
      Double_t sumE2, sumpx2, sumpy2,sumpz2;
      Double_t sumE3, sumpx3, sumpy3,sumpz3;
      Double_t recoMass1, recoMass2, recoMass3;

   TFile *f = new TFile("reconstructedMass.root","RECREATE");
  // TTree *tree=new TTree("events","events");

   TH1D* hist_recoMass1 = new TH1D("hist_reco_mass_without_thetacut", "Reconstructed Mass without theta cut; Reconstructed Mass; Counts",100,0.,100.);
   TH1D* hist_recoMass2 = new TH1D("hist_reco_mass_thetacut", "Reconstructed Z Mass; Reconstructed Mass (GeV); Counts", 100,0.,100.);
   TH1D* hist_recoMass3 = new TH1D("hist_reco_mass_thetacut_Ecut", "Reconstructed Z Mass ; Reconstructed Mass (GeV); Counts", 100,0.,100.);

   TText *conesize = new TText(0.15, 0.9, Form("R=%.1f",r_cone));
   conesize->SetNDC(); // text position defined within [0,1]
   conesize->SetTextSize(0.05);


   TText *theta_range = new TText(0.15, 0.75, Form("#theta in range [%.1f, %.1f]",theta_min,theta_max));
   theta_range->SetNDC(); // text position defined within [0,1]
   theta_range->SetTextSize(0.03);
   theta_range->SetTextColor(kRed);

   TText *without_theta = new TText(0.15, 0.8, "#theta in range [0, #PI]");
   without_theta->SetNDC(); // text position defined within [0,1]
   without_theta->SetTextSize(0.03);
   without_theta->SetTextColor(kBlue);

   TText *Ecut = new TText(0.15, 0.7, Form("#theta in range [%.1f, %.1f] and E > 10 GeV",theta_min, theta_max));
   Ecut->SetNDC(); // text position defined within [0,1]
   Ecut->SetTextSize(0.03);
   Ecut->SetTextColor(kGreen+4);

   TLatex latex_thetacut;
   latex_thetacut.SetTextAlign(13);
   latex_thetacut.SetTextSize(0.045);
   //latex_thetacut.DrawLatexNDC(0.3,0.65, Form("#color[2]{#theta #in [%.1f, %.1f]}",theta_min,theta_max));

   TLatex latex_thetawithout;
   latex_thetawithout.SetTextAlign(13);
   latex_thetawithout.SetTextSize(0.045);
   //latex_thetawithout.DrawLatexNDC(0.3,0.7, "#color[4]{#theta #in [0, #Pi]}");

   TLatex latex_Ecut;
   latex_thetacut.SetTextAlign(13);
   latex_thetacut.SetTextSize(0.045);
   //latex_thetacut.DrawLatexNDC(0.3,0.6, Form("#color[6]{#theta #in [%.1f, %.1f] and and E > 10 GeV}",theta_min,theta_max));



   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;



      sumE1 = 0;
      sumpx1 = 0;
      sumpy1=0;
      sumpz1=0;
      recoMass1=0;

      sumE2 = 0;
      sumpx2 = 0;
      sumpy2=0;
      sumpz2=0;
      recoMass2=0;

      sumE3 = 0;
      sumpx3 = 0;
      sumpy3=0;
      sumpz3=0;
      recoMass3=0;

    for(int i=0; i<(*jets_antikt_pT).size(); i++)
      { //for 1 event


        sumE1 += (*jets_antikt_E)[i];
        sumpx1 += (*jets_antikt_px)[i];
        sumpy1 += (*jets_antikt_py)[i];
        sumpz1 += (*jets_antikt_pz)[i];

          if (((*jets_antikt_theta)[i]>theta_min) && ((*jets_antikt_theta)[i]<theta_max))
          {

            sumE2 += (*jets_antikt_E)[i];
            sumpx2 += (*jets_antikt_px)[i];
            sumpy2 += (*jets_antikt_py)[i];
            sumpz2 += (*jets_antikt_pz)[i];

            if ((*jets_antikt_E)[i]>10.)
            {
              sumE3 += (*jets_antikt_E)[i];
              sumpx3 += (*jets_antikt_px)[i];
              sumpy3 += (*jets_antikt_py)[i];
              sumpz3 += (*jets_antikt_pz)[i];
            }
          }
      }

      recoMass1 = sqrt(sumE1*sumE1 - (sumpx1*sumpx1 + sumpy1*sumpy1 +sumpz1*sumpz1));
      recoMass2 = sqrt(sumE2*sumE2 - (sumpx2*sumpx2 + sumpy2*sumpy2 +sumpz2*sumpz2));
      recoMass3 = sqrt(sumE3*sumE3 - (sumpx3*sumpx3 + sumpy3*sumpy3 +sumpz3*sumpz3));


/*
      for(int i=0; i<(*jets_antikt_pT).size(); i++)
      { //for 1 event


        sumE1 += (*jets_antikt_E)[i]*(*jets_antikt_E)[i];
        sumpx1 += (*jets_antikt_px)[i]*(*jets_antikt_px)[i];
        sumpy1 += (*jets_antikt_py)[i]*(*jets_antikt_py)[i];
        sumpz1 += (*jets_antikt_pz)[i]*(*jets_antikt_pz)[i];

          if (((*jets_antikt_theta)[i]>theta_min) && ((*jets_antikt_theta)[i]<theta_max))
          {

            sumE2 += (*jets_antikt_E)[i]*(*jets_antikt_E)[i];
            sumpx2 += (*jets_antikt_px)[i]*(*jets_antikt_px)[i];
            sumpy2 += (*jets_antikt_py)[i]*(*jets_antikt_py)[i];
            sumpz2 += (*jets_antikt_pz)[i]*(*jets_antikt_pz)[i];

            if ((*jets_antikt_E)[i]>10.)
            {
              sumE3 += (*jets_antikt_E)[i]*(*jets_antikt_E)[i];
              sumpx3 += (*jets_antikt_px)[i]*(*jets_antikt_px)[i];
              sumpy3 += (*jets_antikt_py)[i]*(*jets_antikt_py)[i];
              sumpz3 += (*jets_antikt_pz)[i]*(*jets_antikt_pz)[i];
            }
          }
      }

      recoMass1 = sqrt(sumE1 - (sumpx1 + sumpy1 +sumpz1));
      recoMass2 = sqrt(sumE2 - (sumpx2 + sumpy2 +sumpz2));
      recoMass3 = sqrt(sumE3 - (sumpx3 + sumpy3 +sumpz3));
*/




      hist_recoMass1->Fill(recoMass1);
      hist_recoMass2->Fill(recoMass2);
      hist_recoMass3->Fill(recoMass3);

   }

  TCanvas *c1 = new TCanvas("c1", "Invariant Mass", 1000, 650);

  gStyle->SetOptStat(0);
  c1->cd();
  hist_recoMass3->SetLineColor(kMagenta);
  hist_recoMass3->Draw();
  hist_recoMass2->SetLineColor(kRed);
  hist_recoMass2->Draw("SAME");
  hist_recoMass1->SetLineColor(kBlue);
  hist_recoMass1->Draw("SAME");
  latex_thetacut.DrawLatexNDC(0.3,0.65, Form("#color[2]{#theta #in [%.1f, %.1f]}",theta_min,theta_max)); //red
  latex_thetawithout.DrawLatexNDC(0.3,0.7, "#color[4]{#theta #in [0, #Pi]}"); //blue
  latex_thetacut.DrawLatexNDC(0.3,0.6, Form("#color[6]{#theta #in [%.1f, %.1f] and and E > 10 GeV}",theta_min,theta_max));

//  conesize->Draw();
  //theta_range->Draw();
//  without_theta->Draw();
  //Ecut->Draw();
  c1->Update();
  //c1->SaveAs("ReconstructedMass.pdf");
  c1->SaveAs("ReconstructedMass_3.png");

  f->Write();
  f->Close();

}
