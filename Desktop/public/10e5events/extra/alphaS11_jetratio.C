#define alphaS11_jetratio_cxx
#include "alphaS11_jetratio.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void alphaS11_jetratio::Loop()
{
double alpha_S = 0.110;
int alphaS = alpha_S*1000;

//algorithm 0: antikt, 1:ee_genkt, 2:kt, 3:valencia, 4:cambridge
int algorithm = 0;

double r_cone = 0.5;

   ofstream write;

   write.open(Form("alphaS%d_R5jetratio_antikt.txt",alphaS));
   write << "algorithm"<< " " << "alpha_S" << " " << "R" << " " << "pTcut" << " " << "E cut" << " " << "Jet ratio" << "\n" ;

if (fChain == 0) return;

Bool_t first = true;


// corresponds to event number
Long64_t nentries = fChain->GetEntriesFast();

Int_t r = r_cone*10;

Int_t nbin = 100;
Double_t xmin = 0.;
Double_t xmax = 50.;

Int_t Ecut = 0;
Int_t pTcut= 0;
Double_t pTcuts[] = {0,5,6,7,8,9,10,11,12,13,14,15,20,25};
Double_t Ecuts[] = {0,5,6,7,8,9,10,11,12,13,14,15,20,25};

Double_t Rvalues[5] = {0.3, 0.4, 0.5, 0.6, 0.7};

Int_t size = sizeof(pTcuts)/sizeof(pTcuts[0]);


Double_t theta_min = M_PI/2.-0.55;
Double_t theta_max = M_PI/2.+0.55;

Int_t jetcountpT =0;
Int_t jetcountE=0;

//without theta cut
Double_t jetthreepT=0;
Double_t jettwopT=0;
Double_t ratiojetpT[size];

Double_t jetthreeE=0.;
Double_t jettwoE=0;
Double_t ratiojetE[size];

Double_t error_pT[size];
Double_t error_E[size];


//theta cut
Int_t jetcountpT2 =0;
Int_t jetcountE2=0;

Double_t jetthreepT2=0;
Double_t jettwopT2=0;
Double_t ratiojetpT2[size];

Double_t jetthreeE2=0.;
Double_t jettwoE2=0;
Double_t ratiojetE2[size];

Double_t error_pT2[size];
Double_t error_E2[size];





Int_t max_nb_jets =30;




//To make R size appear on the canvas
TText *conesize = new TText(0.15, 0.9, Form("R=%.1f",r_cone));
conesize->SetNDC(); // text position defined within [0,1]
conesize->SetTextSize(0.05);
conesize->SetTextColor(kGreen+2);

TText *theta_range = new TText(0.5, 0.75, Form("#theta in range [%.1f, %.1f]",theta_min,theta_max));
theta_range->SetNDC(); // text position defined within [0,1]
theta_range->SetTextSize(0.03);
theta_range->SetTextColor(kRed);

TText *without_theta = new TText(0.5, 0.8, "#theta in range [0, #PI]");
without_theta->SetNDC(); // text position defined within [0,1]
without_theta->SetTextSize(0.03);
without_theta->SetTextColor(kBlue);

////only wh




   TH2F* hist_jetratio_pT = new TH2F(Form("hist_jetratio_pTcut%d_withoutthetacut",pTcut), "Jet ratio in function of pT cut (antikt); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E = new TH2F(Form("hist_jetratio_Ecut%d_withoutthetacut",Ecut), "Jet ratio in function of E cut (antikt); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);

   TH2F* hist_jetratio_pT2 = new TH2F(Form("hist_jetratio_pTcut%d",pTcut), "Jet ratio in function of pT cut (antikt); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E2 = new TH2F(Form("hist_jetratio_Ecut%d",Ecut), "Jet ratio in function of E cut (antikt); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);



for(int i=0; i<size; i++)
{
  Ecut = Ecuts[i];
  pTcut = pTcuts[i];



 //without theta cut
    TH1D* hist_nb_jets_pTcut = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (antikt); Number of jets; Counts",60,0.,30.);
    TH1D* hist_nb_jets_Ecut = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (antikt); Number of jets; Counts", 60,0.,30.);

 /////end of without thetacut

 //theta cut histogram
    TH1D* hist_nb_jets_pTcut2 = new TH1D(Form("hist_nb_jets_pTcut%d_2",pTcut), "Number of jets (antikt); Number of jets; Counts",60,0.,30.);
    TH1D* hist_nb_jets_Ecut2 = new TH1D(Form("hist_nb_jets_Ecut%d_2",Ecut), "Number of jets (antikt); Number of jets; Counts", 60,0.,30.);

 //////end of theta cut histogram


Long64_t nbytes = 0, nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   b_jets_antikt_pT->GetEntry(jentry);
   b_jets_antikt_E->GetEntry(jentry);
   b_jets_antikt_theta->GetEntry(jentry);
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   // if (Cut(ientry) < 0) continue;


   jetcountpT=0;
   jetcountE=0;

   jetcountpT2=0;
   jetcountE2=0;


   for(int i=0; i<(*jets_antikt_pT).size(); i++)
   { //for 1 event


     if((*jets_antikt_pT)[i]>=pTcut)
     {
       jetcountpT++;

       if (((*jets_antikt_theta)[i]>theta_min) && ((*jets_antikt_theta)[i]<theta_max))
       {
         jetcountpT2++;
       }

     }


     if((*jets_antikt_E)[i]>=Ecut)
     {
       jetcountE++;

       if (((*jets_antikt_theta)[i]>theta_min) && ((*jets_antikt_theta)[i]<theta_max))
       {
         jetcountE2++;
       }

     }


   } // end of loop of 1 event


     hist_nb_jets_pTcut->Fill(jetcountpT);
     hist_nb_jets_Ecut->Fill(jetcountE);

     hist_nb_jets_pTcut2->Fill(jetcountpT2);
     hist_nb_jets_Ecut2->Fill(jetcountE2);

}//end of loop of all events



// analysis of number of jets, >=3jets / >=2jets

   jettwopT = 0;
   jetthreepT = 0;
   ratiojetpT[i] = 0.;

   jettwopT2 = 0;
   jetthreepT2 = 0;
   ratiojetpT2[i] = 0.;


   //max_nb_jets = 8;
   //if (pTcut ==0 or Ecut ==0)
   max_nb_jets = 30;

   for(int i=2; i<max_nb_jets; i++)
   {
     jettwopT += hist_nb_jets_pTcut->GetBinContent(hist_nb_jets_pTcut->FindBin((double) i));
     jettwopT2 += hist_nb_jets_pTcut2->GetBinContent(hist_nb_jets_pTcut2->FindBin((double) i));
 //    cout << "jet 2 pt : " << jettwopT;
     if(i>2)
     {
       jetthreepT += hist_nb_jets_pTcut->GetBinContent(hist_nb_jets_pTcut->FindBin((double) i));
       jetthreepT2 += hist_nb_jets_pTcut2->GetBinContent(hist_nb_jets_pTcut2->FindBin((double) i));
   //    cout << "jet 3 pt: " << jetthreepT;
     }

   }

 //  if (jetthreepT/jettwopT>0.0001)
   ratiojetpT[i] = jetthreepT/jettwopT;
   //error bar for jet ratio : binomial distribution sqrt(Np(1-p))/N
   error_pT[i] = sqrt(jettwopT * ratiojetpT[i] * (1-ratiojetpT[i])) / jettwopT ;
 //  if (jetthreepT2/jettwopT2>0.0001)
   ratiojetpT2[i] = jetthreepT2/jettwopT2;
   error_pT2[i] = sqrt(jettwopT2 * ratiojetpT2[i] * (1-ratiojetpT2[i])) / jettwopT2 ;

    jettwoE = 0;
    jetthreeE = 0;
    ratiojetE[i] = 0.;

    jettwoE2 = 0;
    jetthreeE2 = 0;
    ratiojetE2[i] = 0.;


   for(int i=2; i<max_nb_jets; i++)
   {
     jettwoE += hist_nb_jets_Ecut->GetBinContent(hist_nb_jets_Ecut->FindBin((double) i));
     jettwoE2 += hist_nb_jets_Ecut2->GetBinContent(hist_nb_jets_Ecut2->FindBin((double) i));
     if(i>2)
     {
       jetthreeE += hist_nb_jets_Ecut->GetBinContent(hist_nb_jets_Ecut->FindBin((double) i));
       jetthreeE2 += hist_nb_jets_Ecut2->GetBinContent(hist_nb_jets_Ecut2->FindBin((double) i));
     }
   }

  ratiojetE[i] = jetthreeE/jettwoE;
  error_E[i] = sqrt(jettwoE * ratiojetE[i] *(1-ratiojetE[i])) / jettwoE ;
 //if (jetthreeE2/jettwoE2>0.0001)
 ratiojetE2[i] = jetthreeE2/jettwoE2;
 error_E2[i] = sqrt(jettwoE2 * ratiojetE2[i] *(1-ratiojetE2[i])) / jettwoE2 ;



 hist_jetratio_pT2->Fill(pTcut, ratiojetpT2[i]);
 cout << "ratiojetpT2 : " << pTcut<< " " << ratiojetpT2[i] << endl;
 hist_jetratio_pT->Fill(pTcut, ratiojetpT[i]);

 hist_jetratio_E2->Fill(Ecut, ratiojetE2[i]);
     cout << "ratiojetE2 : " << Ecut<< " " << ratiojetE2[i] << endl;
 hist_jetratio_E->Fill(Ecut, ratiojetE[i]);

 // 0 : no theta cut , 1: theta cut applied!
 write << algorithm << " " << alpha_S << " " << r_cone << " " << pTcut << " " << "0" << " " << ratiojetpT[i] << " " << "0" << " " << error_pT[i] << "\n";
 write << algorithm << " " << alpha_S << " " << r_cone << " " << "0" << " " << Ecut << " " << ratiojetE[i] << " " << "0" << " " << error_E[i] << "\n";

 write << algorithm << " " << alpha_S << " " << r_cone << " " << pTcut << " " << "0" << " " << ratiojetpT2[i] << " " << "1" << " " << error_pT2[i] << "\n";
 write << algorithm << " " << alpha_S << " " << r_cone << " " << "0" << " " << Ecut << " " << ratiojetE2[i]  << " " << "1" << " " << error_E2[i] <<"\n";


 } // end of Ecut and pTcut

   cout << "Loop finished" << endl;

     write.close();


}
