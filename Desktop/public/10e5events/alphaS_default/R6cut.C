#define R6cut_cxx
#include "R6cut.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void R6cut::Loop_antikt()
{
//   In a ROOT session, you can do:
//      root> .L R5cut.C
//      root> R5cut t
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
double r_cone = 0.6;

if (fChain == 0) return;

// corresponds to event number
Long64_t nentries = fChain->GetEntriesFast();

Int_t r = r_cone*10;

Int_t nbin = 100;
Double_t xmin = 0.;
Double_t xmax = 50.;

Int_t angle_nbin = 150;

Int_t Ecut = 0;
Int_t pTcut= 0;
//
vector<int> pTcuts = {5,10,15,20,25};
vector<int> Ecuts = {5,10,15,20,25};

Double_t theta_min = M_PI/2.-0.55;
Double_t theta_max = M_PI/2.+0.55;

Int_t jetcountpT =0;
Int_t jetcountE=0;

Double_t jetthreepT=0;
Double_t jettwopT=0;
Double_t ratiojetpT=0.;

Double_t jetthreeE=0.;
Double_t jettwoE=0;
Double_t ratiojetE=0.;

//theta cut
Int_t jetcountpT2 =0;
Int_t jetcountE2=0;

Double_t jetthreepT2=0;
Double_t jettwopT2=0;
Double_t ratiojetpT2=0.;

Double_t jetthreeE2=0.;
Double_t jettwoE2=0;
Double_t ratiojetE2=0.;
//without theta cut

Int_t max_nb_jets =0;

//To make R size appear on the canvas
TText *conesize = new TText(0.6, 0.8, Form("R=%.1f",r_cone));
conesize->SetNDC(); // text position defined within [0,1]
conesize->SetTextSize(0.05);
conesize->SetTextColor(kGreen+2);

TText *theta_range = new TText(0.6, 0.8, Form("#theta in range [%.1f, %.1f]",theta_min,theta_max));
theta_range->SetNDC(); // text position defined within [0,1]
theta_range->SetTextSize(0.045);
theta_range->SetTextColor(kRed);



TText *without_theta = new TText(0.6, 0.7, "#theta in range [0, #PI]");
without_theta->SetNDC(); // text position defined within [0,1]
without_theta->SetTextSize(0.045);
without_theta->SetTextColor(kBlue);


TFile *kinematics = new TFile(Form("R%d_kinematics_antikt.root",r),"RECREATE");


TCanvas *c3 = new TCanvas("c3", "antikt #theta distribution", 800, 650);
TCanvas *c4 = new TCanvas("c4", "antikt #theta distribution", 800, 650);



for(int i=0; i<pTcuts.size(); i++)
{
  Ecut = Ecuts[i];
  pTcut = pTcuts[i];

  TText *t_pTcut = new TText(0.6, 0.75, Form("pT > %d GeV",pTcut));
  t_pTcut->SetNDC();
  t_pTcut->SetTextSize(0.05);
  t_pTcut->SetTextColor(kGreen+2);

  TText *t_Ecut = new TText(0.6, 0.75, Form("E > %d GeV",Ecut));
  t_Ecut->SetNDC();
  t_Ecut->SetTextSize(0.05);
  t_Ecut->SetTextColor(kGreen+2);

/*
  if (i!=0) {xmin = Ecuts[i]-5;}
  nbin = nentries/(xmax-xmin);
*/

//without theta cut
TH1D* hist_pT = new TH1D("hist_pT", "Jet p_{T} Distribution (anti-k_{T}) ; Jet #p_T (GeV); Counts", nbin, xmin, xmax);
TH1D* hist_E = new TH1D("hist_E", "Jet Energy Distribution (anti-k_{T}); Jet Energy (GeV); Counts", nbin, xmin, xmax);

TH1D* hist_theta_pTcut = new TH1D("hist_theta_pTcut", "antikt #theta distribution ;#theta; Counts", nbin , xmin, 3.2);
TH1D* hist_theta_Ecut = new TH1D("hist_theta_Ecut", "antikt #theta distribution ;#theta; Counts", nbin, xmin, 3.2);
//   TH1D* hist_phi = new TH1D("hist_phi", "antikt #phi distribution ;#phi; Counts", nbin, xmin, 1.7);

//   TH2F* hist_thetaphi = new TH2F("hist_thetaphi", "#phi-#theta;#phi;#theta",angle_nbin, 0.,1.7,100,0.,3.2);
TH2F* hist_thetaE = new TH2F(Form("hist_thetaE_pTcut%d",pTcut), "#theta-E;E(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
TH2F* hist_thetapT = new TH2F(Form("hist_thetapT_Ecut%d",Ecut), "#theta-pT;pT(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
//   TH2F* hist_phipT = new TH2F("hist_phipT", ";pT(GeV);#phi",angle_nbin, 0.,50.,100,0.,1.7);
//   TH2F* hist_phiE = new TH2F("hist_phiE", ";E(GeV);#phi",angle_nbin, 0.,50.,100,0.,1.7);

TH1D* hist_nb_jets_pTcut = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (Anti-k_{T}) ; Number of jets; Counts",60,0.,30.);
TH1D* hist_nb_jets_Ecut = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (Anti-k_{T}); Number of jets; Counts", 60,0.,30.);
/////end of without thetacut



//theta cut histogram
TH1D* hist_pT2 = new TH1D("hist_pT", "Jet p_{T} Distribution (Anti-k_{T}) ;pT(GeV); Counts", nbin, xmin, xmax);
TH1D* hist_E2 = new TH1D("hist_E", "Jet Energy Distribution (Anti-k_{T}) ;E(GeV); Counts", nbin, xmin, xmax);

TH1D* hist_theta_pTcut2 = new TH1D("hist_theta_pTcut", "antikt #theta distribution ;#theta; Counts", nbin , xmin, 3.2);
TH1D* hist_theta_Ecut2 = new TH1D("hist_theta_Ecut", "antikt #theta distribution ;#theta; Counts", nbin, xmin, 3.2);

TH2F* hist_thetaE2 = new TH2F(Form("hist_thetaE_pTcut%d",pTcut), "#theta-E;E(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
TH2F* hist_thetapT2 = new TH2F(Form("hist_thetapT_Ecut%d",Ecut), "#theta-pT;pT(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);

TH1D* hist_nb_jets_pTcut2 = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (Anti-k_{T}) ; Number of jets; Counts",60,0.,30.);
TH1D* hist_nb_jets_Ecut2 = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (Anti-k_{T}); Number of jets; Counts", 60,0.,30.);
//////end of theta cut histogram



Long64_t nbytes = 0, nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   b_jets_antikt_pT->GetEntry(jentry);
   b_jets_antikt_E->GetEntry(jentry);
   b_jets_antikt_theta->GetEntry(jentry);
   b_jets_antikt_phi->GetEntry(jentry);
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   // if (Cut(ientry) < 0) continue;

   jetcountpT=0;
   jetcountE=0;

   jetcountpT2=0;
   jetcountE2=0;


   for(int i=0; i<(*jets_antikt_pT).size(); i++)
   {


     if((*jets_antikt_pT)[i]>=pTcut)
     {
       hist_pT->Fill((*jets_antikt_pT)[i]);
       hist_theta_pTcut->Fill((*jets_antikt_theta)[i]);
       hist_thetaE->Fill((*jets_antikt_E)[i],(*jets_antikt_theta)[i]);
       jetcountpT++;

       if (((*jets_antikt_theta)[i]>theta_min) && ((*jets_antikt_theta)[i]<theta_max))
       {
         hist_pT2->Fill((*jets_antikt_pT)[i]);
         hist_theta_pTcut2->Fill((*jets_antikt_theta)[i]);
         hist_thetaE2->Fill((*jets_antikt_E)[i],(*jets_antikt_theta)[i]);
         jetcountpT2++;
       }

     }


     if((*jets_antikt_E)[i]>=Ecut)
     {
       hist_E->Fill((*jets_antikt_E)[i]);
       hist_theta_Ecut->Fill((*jets_antikt_theta)[i]);
       hist_thetapT->Fill((*jets_antikt_pT)[i],(*jets_antikt_theta)[i]);
       jetcountE++;

       if (((*jets_antikt_theta)[i]>theta_min) && ((*jets_antikt_theta)[i]<theta_max))
       {
         hist_E2->Fill((*jets_antikt_E)[i]);
         hist_theta_Ecut2->Fill((*jets_antikt_theta)[i]);
         hist_thetapT2->Fill((*jets_antikt_pT)[i],(*jets_antikt_theta)[i]);
         jetcountE2++;
       }

     }


   } // end of loop of 1 event

   hist_nb_jets_pTcut->Fill(jetcountpT);
   hist_nb_jets_Ecut->Fill(jetcountE);

   hist_nb_jets_pTcut2->Fill(jetcountpT2);
   hist_nb_jets_Ecut2->Fill(jetcountE2);

}//end of loop of all events


   TCanvas *c1 = new TCanvas("c1", "pT cut for antikt", 800, 650);
   TCanvas *c2 = new TCanvas("c2", "E cut for antikt", 800, 650);



   c1->cd();
   gStyle->SetOptStat(0);
   hist_pT->SetLineColor(kBlue);
   if(pTcut!=0) hist_pT->GetYaxis()->SetRangeUser(0,9000);
   hist_pT->Draw();
   hist_pT2->SetLineColor(kRed);
   if(pTcut!=0) hist_pT2->GetYaxis()->SetRangeUser(0,9000);
   hist_pT2->Draw("SAME");
   conesize->Draw();
  // theta_range->Draw();
   //without_theta->Draw();
   TLatex latex_thetacut;
   latex_thetacut.SetTextAlign(13);
   latex_thetacut.SetTextSize(0.045);
   latex_thetacut.DrawLatexNDC(0.3,0.65, Form("#color[2]{#theta #in [%.1f, %.1f]}",theta_min,theta_max));
   TLatex latex_thetawithout;
   latex_thetawithout.SetTextAlign(13);
   latex_thetawithout.SetTextSize(0.045);
   latex_thetawithout.DrawLatexNDC(0.3,0.7, "#color[4]{#theta #in [0, #Pi]}");

   c1->Update();
   //c1->Draw();
   c1->SaveAs(Form("antikt_graphs/R%d_antikt_pT%d.pdf",r,pTcut));


   c2->cd();
   gStyle->SetOptStat(0);
   hist_E->SetLineColor(kBlue);
   if(Ecut!=0) hist_E->GetYaxis()->SetRangeUser(0,9000);
   hist_E->Draw();
   hist_E2->SetLineColor(kRed);
   if(Ecut!=0) hist_E2->GetYaxis()->SetRangeUser(0,9000);
   hist_E2->Draw("SAME");
   conesize->Draw();

 //  c2->Draw();

 latex_thetacut.DrawLatexNDC(0.3,0.65, Form("#color[2]{#theta #in [%.1f, %.1f]}",theta_min,theta_max));

 latex_thetawithout.DrawLatexNDC(0.3,0.7, "#color[4]{#theta #in [0, #Pi]}");
    c2->Update();
   c2->SaveAs(Form("antikt_graphs/R%d_antikt_E%d.pdf",r,Ecut));


/*
////////without theta cut////////////
   TCanvas *c5 = new TCanvas("c5", "antikt #theta-#pT", 800, 650);
   TCanvas *c6 = new TCanvas("c6", "antikt #theta-#E", 800, 650);
   //gStyle->SetOptStat(0); // 그림 그렸을때 statistical box를 없애줌 (0)

   c5->cd();
   hist_thetaE->Draw("LEGO");
   conesize->Draw();
   t_pTcut->Draw();
   without_theta->Draw();
   c5->Update();
   c5->SaveAs(Form("antikt_graphs/R%d_antikt_thetaE_pT%d.png",r,Ecut));

   c6->cd();
   hist_thetapT->Draw("LEGO");
   conesize->Draw();
   without_theta->Draw();
   t_Ecut->Draw();
   c6->Update();
   c6->SaveAs(Form("antikt_graphs/R%d_antikt_thetapT_E%d.png",r,Ecut));
/////////end of without theta cut



///////with theta cut ////////
   TCanvas *c9 = new TCanvas("c9", "antikt #theta-#pT", 800, 650);
   TCanvas *c10 = new TCanvas("c10", "antikt #theta-#E", 800, 650);
   //gStyle->SetOptStat(0); // 그림 그렸을때 statistical box를 없애줌 (0)

   c9->cd();
   hist_thetaE2->Draw("LEGO");
   conesize->Draw();
   t_pTcut->Draw();
   theta_range->Draw();
   c9->Update();
   c9->SaveAs(Form("antikt_graphs/R%d_antikt_thetaE_pT%d_thetacut.png",r,Ecut));

   c10->cd();
   hist_thetapT2->Draw("LEGO");
   conesize->Draw();
   theta_range->Draw();
   t_Ecut->Draw();
   c10->Update();
   c10->SaveAs(Form("antikt_graphs/R%d_antikt_thetapT_E%d_thetacut.png",r,Ecut));
///////end of with theta cut
*/

// analysis of number of jets, R_{3/2}

   jettwopT = 0;
   jetthreepT = 0;
   ratiojetpT = 0.;

   jettwopT2 = 0;
   jetthreepT2 = 0;
   ratiojetpT2 = 0.;


 //  max_nb_jets = (int)(*hist_nb_jets_pTcut).GetXaxis()->GetXmax();
   max_nb_jets = 7;
   if (pTcut ==0 or Ecut ==0) max_nb_jets = 30;

   cout << "max_nb_jets : " << max_nb_jets << endl;
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


   ratiojetpT = jetthreepT/jettwopT;
   ratiojetpT2 = jetthreepT2/jettwopT2;

    jettwoE = 0;
    jetthreeE = 0;
    ratiojetE = 0.;

    jettwoE2 = 0;
    jetthreeE2 = 0;
    ratiojetE2 = 0.;



 //  max_nb_jets = (int)(*hist_nb_jets_Ecut).GetXaxis()->GetXmax();
   cout << "max_nb_jets : " << max_nb_jets << endl;
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

   ratiojetE = jetthreeE/jettwoE;
   ratiojetE2 = jetthreeE2/jettwoE2;

   TText *jetratiopT = new TText(0.15, 0.7, Form("R_{3/2} = %0.3f",ratiojetpT));
   jetratiopT->SetNDC(); // text position defined within [0,1]
   jetratiopT->SetTextSize(0.05);
   jetratiopT->SetTextColor(kBlue);


   TText *jetratioE = new TText(0.15, 0.7, Form("R_{3/2} = %0.3f",ratiojetE));
   jetratioE->SetNDC(); // text position defined within [0,1]
   jetratioE->SetTextSize(0.05);
   jetratioE->SetTextColor(kBlue);


   TText *jetratiopT2 = new TText(0.15, 0.65, Form("R_{3/2} = %0.3f",ratiojetpT2));
   jetratiopT2->SetNDC(); // text position defined within [0,1]
   jetratiopT2->SetTextSize(0.05);
   jetratiopT2->SetTextColor(kRed);


   TText *jetratioE2 = new TText(0.15, 0.65, Form("R_{3/2} = %0.3f",ratiojetE2));
   jetratioE2->SetNDC(); // text position defined within [0,1]
   jetratioE2->SetTextSize(0.05);
   jetratioE2->SetTextColor(kRed);




   TCanvas *c7 = new TCanvas("c7", "antikt number of jets", 1000, 650);
   TCanvas *c8 = new TCanvas("c8", "antikt number of jets", 1000, 650);

   c7->cd();
   if (pTcut != 0)
   {
     hist_nb_jets_pTcut->GetXaxis()->SetRangeUser(0,5);
     hist_nb_jets_pTcut2->GetXaxis()->SetRangeUser(0,5);
   }
   hist_nb_jets_pTcut->SetLineColor(kBlue);
   hist_nb_jets_pTcut2->SetLineColor(kRed);
   hist_nb_jets_pTcut->Draw();
   hist_nb_jets_pTcut2->Draw("SAME");
   conesize->Draw();
   t_pTcut->Draw();
  // theta_range->Draw();
  // without_theta->Draw();

 latex_thetacut.DrawLatexNDC(0.7,0.65, Form("#color[2]{#theta #in [%.1f, %.1f]}",theta_min,theta_max));
  latex_thetawithout.DrawLatexNDC(0.7,0.7, "#color[4]{#theta #in [0, #Pi]}");

  TLatex latex_jetratiopT;
  latex_jetratiopT.SetTextAlign(13);
  latex_jetratiopT.SetTextSize(0.045);
  latex_jetratiopT.DrawLatexNDC(0.5, 0.7, Form("#color[4]{R_{3/2} = %0.3f}",ratiojetpT));

  TLatex latex_jetratiopT2;
  latex_jetratiopT2.SetTextAlign(13);
  latex_jetratiopT2.SetTextSize(0.045);
  latex_jetratiopT2.DrawLatexNDC(0.5, 0.65, Form("#color[2]{R_{3/2} = %0.3f}",ratiojetpT2));
   //jetratiopT->Draw();
   //jetratiopT2->Draw();
   c7->Update();
   c7->SaveAs(Form("antikt_graphs/R%d_antikt_nb_jets_pT%d.pdf",r,pTcut));


   c8->cd();
   gStyle->SetOptStat(0);
   if (Ecut != 0)
   {
     hist_nb_jets_Ecut->GetXaxis()->SetRangeUser(0,5);
     hist_nb_jets_Ecut2->GetXaxis()->SetRangeUser(0,5);
   }
   hist_nb_jets_Ecut->SetLineColor(kBlue);
   hist_nb_jets_Ecut2->SetLineColor(kRed);
   hist_nb_jets_Ecut->Draw("");
   hist_nb_jets_Ecut2->Draw("SAME");
   hist_nb_jets_Ecut2->GetXaxis()->SetLabelSize(0.04);
   conesize->Draw();
   t_Ecut->Draw();


    latex_thetacut.DrawLatexNDC(0.7,0.65, Form("#color[2]{#theta #in [%.1f, %.1f]}",theta_min,theta_max));
   latex_thetawithout.DrawLatexNDC(0.7,0.7, "#color[4]{#theta #in [0, #Pi]}");

   TLatex latex_jetratioE;
   latex_jetratioE.SetTextAlign(13);
   latex_jetratioE.SetTextSize(0.045);
   latex_jetratioE.DrawLatexNDC(0.5, 0.7, Form("#color[4]{R_{3/2} = %0.3f}",ratiojetE));

   TLatex latex_jetratioE2;
   latex_jetratioE2.SetTextAlign(13);
   latex_jetratioE2.SetTextSize(0.045);
   latex_jetratioE2.DrawLatexNDC(0.5, 0.65, Form("#color[2]{R_{3/2} = %0.3f}",ratiojetE2));

   c8->Update();
   c8->SaveAs(Form("antikt_graphs/R%d_antikt_nb_jets_E%d.pdf",r,Ecut));

/*
   // Definition in the beginning
   c3->cd();
   hist_theta_pTcut2->SetFillColor(i+2);
   if (pTcut !=0)
   {
     hist_theta_pTcut2->Draw("SAME");
     conesize->Draw();
     t_pTcut->SetX(0.15);
     t_pTcut->SetY(0.7-0.05*i);
     t_pTcut->SetTextSize(0.04);
     t_pTcut->SetTextColor(i+2);
     t_pTcut->Draw("SAME");
     theta_range->Draw();
     c3->Update();
   }
//      c3->SaveAs(Form("antikt_graphs/R%d_antikt_theta_distritution_pT%d.png",r,pTcut));

   c4->cd();
   hist_theta_Ecut2->SetFillColor(i+2);
   if (pTcut !=0)
   {
     hist_theta_Ecut2->Draw("SAME");
     conesize->Draw();
     t_Ecut->SetX(0.15);
     t_Ecut->SetY(0.7-0.05*i);
     t_Ecut->SetTextSize(0.04);
     t_Ecut->SetTextColor(i+2);
     t_Ecut->Draw("SAME");
     theta_range->Draw();
     c4->Update();
   }
//      c4->SaveAs(Form("antikt_graphs/R%d_antikt_theta_distritution_E%d.png",r,Ecut));
*/

/*
   if (Ecut == 0. or pTcut==0.)
   {
     hist_E->Write();
     hist_pT->Write();
     hist_E2->Write();
     hist_pT2->Write();
   }

   hist_theta_pTcut->Write();
   hist_theta_Ecut->Write();
   hist_thetaE->Write();
   hist_thetapT->Write();
   hist_nb_jets_Ecut->Write();
   hist_nb_jets_pTcut->Write();

   hist_theta_pTcut2->Write();
   hist_theta_Ecut2->Write();
   hist_thetaE2->Write();
   hist_thetapT2->Write();
   hist_nb_jets_Ecut2->Write();
   hist_nb_jets_pTcut2->Write();
*/

 } // end of Ecut and pTcut

/*
 c3->SaveAs(Form("antikt_graphs/R%d_antikt_theta_distritution_pTcut.png",r));
 c4->SaveAs(Form("antikt_graphs/R%d_antikt_theta_distritution_Ecut.png",r));
*/
}

void R6cut::Loop_valencia()
{

double r_cone = 0.6;

if (fChain == 0) return;

// corresponds to event number
Long64_t nentries = fChain->GetEntriesFast();

Int_t r = r_cone*10;

Int_t nbin = 100;
Double_t xmin = 0.;
Double_t xmax = 50.;

Int_t angle_nbin = 150;

Int_t Ecut = 0;
Int_t pTcut= 0;
vector<int> pTcuts = {0,5,10,15,20,25};
vector<int> Ecuts = {0,5,10,15,20,25};

Double_t theta_min = M_PI/2.-0.55;
Double_t theta_max = M_PI/2.+0.55;

Int_t jetcountpT =0;
Int_t jetcountE=0;

Double_t jetthreepT=0;
Double_t jettwopT=0;
Double_t ratiojetpT=0.;

Double_t jetthreeE=0.;
Double_t jettwoE=0;
Double_t ratiojetE=0.;

//theta cut
Int_t jetcountpT2 =0;
Int_t jetcountE2=0;

Double_t jetthreepT2=0;
Double_t jettwopT2=0;
Double_t ratiojetpT2=0.;

Double_t jetthreeE2=0.;
Double_t jettwoE2=0;
Double_t ratiojetE2=0.;
//without theta cut

Int_t max_nb_jets =0;

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


TFile *kinematics = new TFile(Form("R%d_kinematics_valencia.root",r),"RECREATE");


TCanvas *c3 = new TCanvas("c3", "valencia #theta distribution", 800, 650);
TCanvas *c4 = new TCanvas("c4", "valencia #theta distribution", 800, 650);



for(int i=0; i<pTcuts.size(); i++)
{
  Ecut = Ecuts[i];
  pTcut = pTcuts[i];

  TText *t_pTcut = new TText(0.15, 0.85, Form("pT > %d GeV",pTcut));
  t_pTcut->SetNDC();
  t_pTcut->SetTextSize(0.05);
  t_pTcut->SetTextColor(kGreen+2);

  TText *t_Ecut = new TText(0.15, 0.85, Form("E > %d GeV",Ecut));
  t_Ecut->SetNDC();
  t_Ecut->SetTextSize(0.05);
  t_Ecut->SetTextColor(kGreen+2);

/*
  if (i!=0) {xmin = Ecuts[i]-5;}
  nbin = nentries/(xmax-xmin);
*/

//without theta cut
TH1D* hist_pT = new TH1D("hist_pT", "pT cut for valencia ;pT(GeV); Counts", nbin, xmin, xmax);
TH1D* hist_E = new TH1D("hist_E", "E cut for valencia ;E(GeV); Counts", nbin, xmin, xmax);

TH1D* hist_theta_pTcut = new TH1D("hist_theta_pTcut", "valencia #theta distribution ;#theta; Counts", nbin , xmin, 3.2);
TH1D* hist_theta_Ecut = new TH1D("hist_theta_Ecut", "valencia #theta distribution ;#theta; Counts", nbin, xmin, 3.2);
//   TH1D* hist_phi = new TH1D("hist_phi", "valencia #phi distribution ;#phi; Counts", nbin, xmin, 1.7);

//   TH2F* hist_thetaphi = new TH2F("hist_thetaphi", "#phi-#theta;#phi;#theta",angle_nbin, 0.,1.7,100,0.,3.2);
TH2F* hist_thetaE = new TH2F(Form("hist_thetaE_pTcut%d",pTcut), "#theta-E;E(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
TH2F* hist_thetapT = new TH2F(Form("hist_thetapT_Ecut%d",Ecut), "#theta-pT;pT(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
//   TH2F* hist_phipT = new TH2F("hist_phipT", ";pT(GeV);#phi",angle_nbin, 0.,50.,100,0.,1.7);
//   TH2F* hist_phiE = new TH2F("hist_phiE", ";E(GeV);#phi",angle_nbin, 0.,50.,100,0.,1.7);

TH1D* hist_nb_jets_pTcut = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (valencia) ; Number of jets; Counts",60,0.,30.);
TH1D* hist_nb_jets_Ecut = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (valencia); Number of jets; Counts", 60,0.,30.);
/////end of without thetacut



//theta cut histogram
TH1D* hist_pT2 = new TH1D("hist_pT", "pT cut for valencia ;pT(GeV); Counts", nbin, xmin, xmax);
TH1D* hist_E2 = new TH1D("hist_E", "E cut for valencia ;E(GeV); Counts", nbin, xmin, xmax);

TH1D* hist_theta_pTcut2 = new TH1D("hist_theta_pTcut", "valencia #theta distribution ;#theta; Counts", nbin , xmin, 3.2);
TH1D* hist_theta_Ecut2 = new TH1D("hist_theta_Ecut", "valencia #theta distribution ;#theta; Counts", nbin, xmin, 3.2);

TH2F* hist_thetaE2 = new TH2F(Form("hist_thetaE_pTcut%d",pTcut), "#theta-E;E(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
TH2F* hist_thetapT2 = new TH2F(Form("hist_thetapT_Ecut%d",Ecut), "#theta-pT;pT(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);

TH1D* hist_nb_jets_pTcut2 = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (valencia); Number of jets; Counts",60,0.,30.);
TH1D* hist_nb_jets_Ecut2 = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (valencia); Number of jets; Counts", 60,0.,30.);
//////end of theta cut histogram



Long64_t nbytes = 0, nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   b_jets_valencia_pT->GetEntry(jentry);
   b_jets_valencia_E->GetEntry(jentry);
   b_jets_valencia_theta->GetEntry(jentry);
   b_jets_valencia_phi->GetEntry(jentry);
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   // if (Cut(ientry) < 0) continue;

   jetcountpT=0;
   jetcountE=0;

   jetcountpT2=0;
   jetcountE2=0;


   for(int i=0; i<(*jets_valencia_pT).size(); i++)
   {


     if((*jets_valencia_pT)[i]>=pTcut)
     {
       hist_pT->Fill((*jets_valencia_pT)[i]);
       hist_theta_pTcut->Fill((*jets_valencia_theta)[i]);
       hist_thetaE->Fill((*jets_valencia_E)[i],(*jets_valencia_theta)[i]);
       jetcountpT++;

       if (((*jets_valencia_theta)[i]>theta_min) && ((*jets_valencia_theta)[i]<theta_max))
       {
         hist_pT2->Fill((*jets_valencia_pT)[i]);
         hist_theta_pTcut2->Fill((*jets_valencia_theta)[i]);
         hist_thetaE2->Fill((*jets_valencia_E)[i],(*jets_valencia_theta)[i]);
         jetcountpT2++;
       }

     }


     if((*jets_valencia_E)[i]>=Ecut)
     {
       hist_E->Fill((*jets_valencia_E)[i]);
       hist_theta_Ecut->Fill((*jets_valencia_theta)[i]);
       hist_thetapT->Fill((*jets_valencia_pT)[i],(*jets_valencia_theta)[i]);
       jetcountE++;

       if (((*jets_valencia_theta)[i]>theta_min) && ((*jets_valencia_theta)[i]<theta_max))
       {
         hist_E2->Fill((*jets_valencia_E)[i]);
         hist_theta_Ecut2->Fill((*jets_valencia_theta)[i]);
         hist_thetapT2->Fill((*jets_valencia_pT)[i],(*jets_valencia_theta)[i]);
         jetcountE2++;
       }

     }


   } // end of loop of 1 event

   hist_nb_jets_pTcut->Fill(jetcountpT);
   hist_nb_jets_Ecut->Fill(jetcountE);

   hist_nb_jets_pTcut2->Fill(jetcountpT2);
   hist_nb_jets_Ecut2->Fill(jetcountE2);

}//end of loop of all events

   TCanvas *c1 = new TCanvas("c1", "pT cut for valencia", 800, 650);
   TCanvas *c2 = new TCanvas("c2", "E cut for valencia", 800, 650);



   c1->cd();
   hist_pT->SetLineColor(kBlue);
   hist_pT->Draw();
   hist_pT2->SetLineColor(kRed);
   hist_pT2->Draw("SAME");
   conesize->Draw();
   theta_range->Draw();
   without_theta->Draw();
   c1->Update();
   //c1->Draw();
   c1->SaveAs(Form("valencia_graphs/R%d_valencia_pT%d.pdf",r,pTcut));


   c2->cd();
   hist_E->SetLineColor(kBlue);
   hist_E->Draw();
   hist_E2->SetLineColor(kRed);
   hist_E2->Draw("SAME");
   conesize->Draw();
   theta_range->Draw();
   without_theta->Draw();
   c2->Update();
 //  c2->Draw();
   c2->SaveAs(Form("valencia_graphs/R%d_valencia_E%d.pdf",r,Ecut));


/*
////////without theta cut////////////
   TCanvas *c5 = new TCanvas("c5", "valencia #theta-#pT", 800, 650);
   TCanvas *c6 = new TCanvas("c6", "valencia #theta-#E", 800, 650);
   //gStyle->SetOptStat(0); // 그림 그렸을때 statistical box를 없애줌 (0)

   c5->cd();
   hist_thetaE->Draw("LEGO");
   conesize->Draw();
   t_pTcut->Draw();
   without_theta->Draw();
   c5->Update();
   c5->SaveAs(Form("valencia_graphs/R%d_valencia_thetaE_pT%d.pdf",r,Ecut));

   c6->cd();
   hist_thetapT->Draw("LEGO");
   conesize->Draw();
   without_theta->Draw();
   t_Ecut->Draw();
   c6->Update();
   c6->SaveAs(Form("valencia_graphs/R%d_valencia_thetapT_E%d.pdf",r,Ecut));
/////////end of without theta cut



///////with theta cut ////////
   TCanvas *c9 = new TCanvas("c9", "valencia #theta-#pT", 800, 650);
   TCanvas *c10 = new TCanvas("c10", "valencia #theta-#E", 800, 650);
   //gStyle->SetOptStat(0); // 그림 그렸을때 statistical box를 없애줌 (0)

   c9->cd();
   hist_thetaE2->Draw("LEGO");
   conesize->Draw();
   t_pTcut->Draw();
   theta_range->Draw();
   c9->Update();
   c9->SaveAs(Form("valencia_graphs/R%d_valencia_thetaE_pT%d_thetacut.pdf",r,Ecut));

   c10->cd();
   hist_thetapT2->Draw("LEGO");
   conesize->Draw();
   theta_range->Draw();
   t_Ecut->Draw();
   c10->Update();
   c10->SaveAs(Form("valencia_graphs/R%d_valencia_thetapT_E%d_thetacut.pdf",r,Ecut));
///////end of with theta cut
*/

// analysis of number of jets, 3+jets / 2+jets

   jettwopT = 0;
   jetthreepT = 0;
   ratiojetpT = 0.;

   jettwopT2 = 0;
   jetthreepT2 = 0;
   ratiojetpT2 = 0.;


 //  max_nb_jets = (int)(*hist_nb_jets_pTcut).GetXaxis()->GetXmax();
   max_nb_jets = 7;
   if (pTcut ==0 or Ecut ==0) max_nb_jets = 30;

   cout << "max_nb_jets : " << max_nb_jets << endl;
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


   ratiojetpT = jetthreepT/jettwopT;
   ratiojetpT2 = jetthreepT2/jettwopT2;

    jettwoE = 0;
    jetthreeE = 0;
    ratiojetE = 0.;

    jettwoE2 = 0;
    jetthreeE2 = 0;
    ratiojetE2 = 0.;



 //  max_nb_jets = (int)(*hist_nb_jets_Ecut).GetXaxis()->GetXmax();
   cout << "max_nb_jets : " << max_nb_jets << endl;
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

   ratiojetE = jetthreeE/jettwoE;
   ratiojetE2 = jetthreeE2/jettwoE2;

   TText *jetratiopT = new TText(0.15, 0.7, Form("3+jets / 2+jets = %0.3f",ratiojetpT));
   jetratiopT->SetNDC(); // text position defined within [0,1]
   jetratiopT->SetTextSize(0.05);
   jetratiopT->SetTextColor(kBlue);


   TText *jetratioE = new TText(0.15, 0.7, Form("3+jets / 2+jets = %0.3f",ratiojetE));
   jetratioE->SetNDC(); // text position defined within [0,1]
   jetratioE->SetTextSize(0.05);
   jetratioE->SetTextColor(kBlue);


   TText *jetratiopT2 = new TText(0.15, 0.65, Form("3+jets / 2+jets = %0.3f",ratiojetpT2));
   jetratiopT2->SetNDC(); // text position defined within [0,1]
   jetratiopT2->SetTextSize(0.05);
   jetratiopT2->SetTextColor(kRed);


   TText *jetratioE2 = new TText(0.15, 0.65, Form("3+jets / 2+jets = %0.3f",ratiojetE2));
   jetratioE2->SetNDC(); // text position defined within [0,1]
   jetratioE2->SetTextSize(0.05);
   jetratioE2->SetTextColor(kRed);




   TCanvas *c7 = new TCanvas("c7", "valencia number of jets", 800, 650);
   TCanvas *c8 = new TCanvas("c8", "valencia number of jets", 800, 650);

   c7->cd();
   if (pTcut != 0)
   {
     hist_nb_jets_pTcut->GetXaxis()->SetRangeUser(0,5);
     hist_nb_jets_pTcut2->GetXaxis()->SetRangeUser(0,5);
   }
   hist_nb_jets_pTcut->SetLineColor(kBlue);
   hist_nb_jets_pTcut->Draw();
   hist_nb_jets_pTcut2->SetLineColor(kRed);
   hist_nb_jets_pTcut2->Draw("SAME");
   conesize->Draw();
   t_pTcut->Draw();
   theta_range->Draw();
   without_theta->Draw();
   jetratiopT->Draw();
   jetratiopT2->Draw();
   c7->Update();
   c7->SaveAs(Form("valencia_graphs/R%d_valencia_nb_jets_pT%d.pdf",r,pTcut));


   c8->cd();
   if (Ecut != 0)
   {
     hist_nb_jets_Ecut->GetXaxis()->SetRangeUser(0,5);
     hist_nb_jets_Ecut2->GetXaxis()->SetRangeUser(0,5);
   }
   hist_nb_jets_Ecut->SetLineColor(kBlue);
   hist_nb_jets_Ecut->Draw();
   hist_nb_jets_Ecut2->SetLineColor(kRed);
   hist_nb_jets_Ecut2->Draw("SAME");
   conesize->Draw();
   t_Ecut->Draw();
   theta_range->Draw();
   without_theta->Draw();
   jetratioE->Draw();
   jetratioE2->Draw();
   c8->Update();
   c8->SaveAs(Form("valencia_graphs/R%d_valencia_nb_jets_E%d.pdf",r,Ecut));


   // Definition in the beginning
   c3->cd();
   hist_theta_pTcut2->SetFillColor(i+2);
   if (pTcut !=0)
   {
     hist_theta_pTcut2->Draw("SAME");
     conesize->Draw();
     t_pTcut->SetX(0.15);
     t_pTcut->SetY(0.7-0.05*i);
     t_pTcut->SetTextSize(0.04);
     t_pTcut->SetTextColor(i+2);
     t_pTcut->Draw("SAME");
     theta_range->Draw();
     c3->Update();
   }
//      c3->SaveAs(Form("valencia_graphs/R%d_valencia_theta_distritution_pT%d.pdf",r,pTcut));

   c4->cd();
   hist_theta_Ecut2->SetFillColor(i+2);
   if (pTcut !=0)
   {
     hist_theta_Ecut2->Draw("SAME");
     conesize->Draw();
     t_Ecut->SetX(0.15);
     t_Ecut->SetY(0.7-0.05*i);
     t_Ecut->SetTextSize(0.04);
     t_Ecut->SetTextColor(i+2);
     t_Ecut->Draw("SAME");
     theta_range->Draw();
     c4->Update();
   }
//      c4->SaveAs(Form("valencia_graphs/R%d_valencia_theta_distritution_E%d.pdf",r,Ecut));


   if (Ecut == 0. or pTcut==0.)
   {
     hist_E->Write();
     hist_pT->Write();
     hist_E2->Write();
     hist_pT2->Write();
   }

   hist_theta_pTcut->Write();
   hist_theta_Ecut->Write();
   hist_thetaE->Write();
   hist_thetapT->Write();
   hist_nb_jets_Ecut->Write();
   hist_nb_jets_pTcut->Write();

   hist_theta_pTcut2->Write();
   hist_theta_Ecut2->Write();
   hist_thetaE2->Write();
   hist_thetapT2->Write();
   hist_nb_jets_Ecut2->Write();
   hist_nb_jets_pTcut2->Write();


 } // end of Ecut and pTcut

 c3->SaveAs(Form("valencia_graphs/R%d_valencia_theta_distritution_pTcut.pdf",r));
 c4->SaveAs(Form("valencia_graphs/R%d_valencia_theta_distritution_Ecut.pdf",r));

}
void R6cut::Loop_cambridge()
{

double r_cone = 0.6;

if (fChain == 0) return;

// corresponds to event number
Long64_t nentries = fChain->GetEntriesFast();

Int_t r = r_cone*10;

Int_t nbin = 100;
Double_t xmin = 0.;
Double_t xmax = 50.;

Int_t angle_nbin = 150;

Int_t Ecut = 0;
Int_t pTcut= 0;
vector<int> pTcuts = {0,5,10,15,20,25};
vector<int> Ecuts = {0,5,10,15,20,25};

Double_t theta_min = M_PI/2.-0.55;
Double_t theta_max = M_PI/2.+0.55;

Int_t jetcountpT =0;
Int_t jetcountE=0;

Double_t jetthreepT=0;
Double_t jettwopT=0;
Double_t ratiojetpT=0.;

Double_t jetthreeE=0.;
Double_t jettwoE=0;
Double_t ratiojetE=0.;

//theta cut
Int_t jetcountpT2 =0;
Int_t jetcountE2=0;

Double_t jetthreepT2=0;
Double_t jettwopT2=0;
Double_t ratiojetpT2=0.;

Double_t jetthreeE2=0.;
Double_t jettwoE2=0;
Double_t ratiojetE2=0.;
//without theta cut

Int_t max_nb_jets =0;

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


TFile *kinematics = new TFile(Form("R%d_kinematics_cambridge.root",r),"RECREATE");


TCanvas *c3 = new TCanvas("c3", "cambridge #theta distribution", 800, 650);
TCanvas *c4 = new TCanvas("c4", "cambridge #theta distribution", 800, 650);



for(int i=0; i<pTcuts.size(); i++)
{
  Ecut = Ecuts[i];
  pTcut = pTcuts[i];

  TText *t_pTcut = new TText(0.15, 0.85, Form("pT > %d GeV",pTcut));
  t_pTcut->SetNDC();
  t_pTcut->SetTextSize(0.05);
  t_pTcut->SetTextColor(kGreen+2);

  TText *t_Ecut = new TText(0.15, 0.85, Form("E > %d GeV",Ecut));
  t_Ecut->SetNDC();
  t_Ecut->SetTextSize(0.05);
  t_Ecut->SetTextColor(kGreen+2);

/*
  if (i!=0) {xmin = Ecuts[i]-5;}
  nbin = nentries/(xmax-xmin);
*/

//without theta cut
TH1D* hist_pT = new TH1D("hist_pT", "pT cut for cambridge ;pT(GeV); Counts", nbin, xmin, xmax);
TH1D* hist_E = new TH1D("hist_E", "E cut for cambridge ;E(GeV); Counts", nbin, xmin, xmax);

TH1D* hist_theta_pTcut = new TH1D("hist_theta_pTcut", "cambridge #theta distribution ;#theta; Counts", nbin , xmin, 3.2);
TH1D* hist_theta_Ecut = new TH1D("hist_theta_Ecut", "cambridge #theta distribution ;#theta; Counts", nbin, xmin, 3.2);
//   TH1D* hist_phi = new TH1D("hist_phi", "cambridge #phi distribution ;#phi; Counts", nbin, xmin, 1.7);

//   TH2F* hist_thetaphi = new TH2F("hist_thetaphi", "#phi-#theta;#phi;#theta",angle_nbin, 0.,1.7,100,0.,3.2);
TH2F* hist_thetaE = new TH2F(Form("hist_thetaE_pTcut%d",pTcut), "#theta-E;E(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
TH2F* hist_thetapT = new TH2F(Form("hist_thetapT_Ecut%d",Ecut), "#theta-pT;pT(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
//   TH2F* hist_phipT = new TH2F("hist_phipT", ";pT(GeV);#phi",angle_nbin, 0.,50.,100,0.,1.7);
//   TH2F* hist_phiE = new TH2F("hist_phiE", ";E(GeV);#phi",angle_nbin, 0.,50.,100,0.,1.7);

TH1D* hist_nb_jets_pTcut = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (cambridge); Number of jets; Counts",60,0.,30.);
TH1D* hist_nb_jets_Ecut = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (cambridge); Number of jets; Counts", 60,0.,30.);
/////end of without thetacut



//theta cut histogram
TH1D* hist_pT2 = new TH1D("hist_pT", "pT cut for cambridge ;pT(GeV); Counts", nbin, xmin, xmax);
TH1D* hist_E2 = new TH1D("hist_E", "E cut for cambridge ;E(GeV); Counts", nbin, xmin, xmax);

TH1D* hist_theta_pTcut2 = new TH1D("hist_theta_pTcut", "cambridge #theta distribution ;#theta; Counts", nbin , xmin, 3.2);
TH1D* hist_theta_Ecut2 = new TH1D("hist_theta_Ecut", "cambridge #theta distribution ;#theta; Counts", nbin, xmin, 3.2);

TH2F* hist_thetaE2 = new TH2F(Form("hist_thetaE_pTcut%d",pTcut), "#theta-E;E(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
TH2F* hist_thetapT2 = new TH2F(Form("hist_thetapT_Ecut%d",Ecut), "#theta-pT;pT(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);

TH1D* hist_nb_jets_pTcut2 = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (cambridge); Number of jets; Counts",60,0.,30.);
TH1D* hist_nb_jets_Ecut2 = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (cambridge); Number of jets; Counts", 60,0.,30.);
//////end of theta cut histogram



Long64_t nbytes = 0, nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   b_jets_cambridge_pT->GetEntry(jentry);
   b_jets_cambridge_E->GetEntry(jentry);
   b_jets_cambridge_theta->GetEntry(jentry);
   b_jets_cambridge_phi->GetEntry(jentry);
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   // if (Cut(ientry) < 0) continue;

   jetcountpT=0;
   jetcountE=0;

   jetcountpT2=0;
   jetcountE2=0;


   for(int i=0; i<(*jets_cambridge_pT).size(); i++)
   {


     if((*jets_cambridge_pT)[i]>=pTcut)
     {
       hist_pT->Fill((*jets_cambridge_pT)[i]);
       hist_theta_pTcut->Fill((*jets_cambridge_theta)[i]);
       hist_thetaE->Fill((*jets_cambridge_E)[i],(*jets_cambridge_theta)[i]);
       jetcountpT++;

       if (((*jets_cambridge_theta)[i]>theta_min) && ((*jets_cambridge_theta)[i]<theta_max))
       {
         hist_pT2->Fill((*jets_cambridge_pT)[i]);
         hist_theta_pTcut2->Fill((*jets_cambridge_theta)[i]);
         hist_thetaE2->Fill((*jets_cambridge_E)[i],(*jets_cambridge_theta)[i]);
         jetcountpT2++;
       }

     }


     if((*jets_cambridge_E)[i]>=Ecut)
     {
       hist_E->Fill((*jets_cambridge_E)[i]);
       hist_theta_Ecut->Fill((*jets_cambridge_theta)[i]);
       hist_thetapT->Fill((*jets_cambridge_pT)[i],(*jets_cambridge_theta)[i]);
       jetcountE++;

       if (((*jets_cambridge_theta)[i]>theta_min) && ((*jets_cambridge_theta)[i]<theta_max))
       {
         hist_E2->Fill((*jets_cambridge_E)[i]);
         hist_theta_Ecut2->Fill((*jets_cambridge_theta)[i]);
         hist_thetapT2->Fill((*jets_cambridge_pT)[i],(*jets_cambridge_theta)[i]);
         jetcountE2++;
       }

     }


   } // end of loop of 1 event

   hist_nb_jets_pTcut->Fill(jetcountpT);
   hist_nb_jets_Ecut->Fill(jetcountE);

   hist_nb_jets_pTcut2->Fill(jetcountpT2);
   hist_nb_jets_Ecut2->Fill(jetcountE2);

}//end of loop of all events

   TCanvas *c1 = new TCanvas("c1", "pT cut for cambridge", 800, 650);
   TCanvas *c2 = new TCanvas("c2", "E cut for cambridge", 800, 650);



   c1->cd();
   hist_pT->SetLineColor(kBlue);
   hist_pT->Draw();
   hist_pT2->SetLineColor(kRed);
   hist_pT2->Draw("SAME");
   conesize->Draw();
   theta_range->Draw();
   without_theta->Draw();
   c1->Update();
   //c1->Draw();
   c1->SaveAs(Form("cambridge_graphs/R%d_cambridge_pT%d.pdf",r,pTcut));


   c2->cd();
   hist_E->SetLineColor(kBlue);
   hist_E->Draw();
   hist_E2->SetLineColor(kRed);
   hist_E2->Draw("SAME");
   conesize->Draw();
   theta_range->Draw();
   without_theta->Draw();
   c2->Update();
 //  c2->Draw();
   c2->SaveAs(Form("cambridge_graphs/R%d_cambridge_E%d.pdf",r,Ecut));


/*
////////without theta cut////////////
   TCanvas *c5 = new TCanvas("c5", "cambridge #theta-#pT", 800, 650);
   TCanvas *c6 = new TCanvas("c6", "cambridge #theta-#E", 800, 650);
   //gStyle->SetOptStat(0); // 그림 그렸을때 statistical box를 없애줌 (0)

   c5->cd();
   hist_thetaE->Draw("LEGO");
   conesize->Draw();
   t_pTcut->Draw();
   without_theta->Draw();
   c5->Update();
   c5->SaveAs(Form("cambridge_graphs/R%d_cambridge_thetaE_pT%d.pdf",r,Ecut));

   c6->cd();
   hist_thetapT->Draw("LEGO");
   conesize->Draw();
   without_theta->Draw();
   t_Ecut->Draw();
   c6->Update();
   c6->SaveAs(Form("cambridge_graphs/R%d_cambridge_thetapT_E%d.pdf",r,Ecut));
/////////end of without theta cut



///////with theta cut ////////
   TCanvas *c9 = new TCanvas("c9", "cambridge #theta-#pT", 800, 650);
   TCanvas *c10 = new TCanvas("c10", "cambridge #theta-#E", 800, 650);
   //gStyle->SetOptStat(0); // 그림 그렸을때 statistical box를 없애줌 (0)

   c9->cd();
   hist_thetaE2->Draw("LEGO");
   conesize->Draw();
   t_pTcut->Draw();
   theta_range->Draw();
   c9->Update();
   c9->SaveAs(Form("cambridge_graphs/R%d_cambridge_thetaE_pT%d_thetacut.pdf",r,Ecut));

   c10->cd();
   hist_thetapT2->Draw("LEGO");
   conesize->Draw();
   theta_range->Draw();
   t_Ecut->Draw();
   c10->Update();
   c10->SaveAs(Form("cambridge_graphs/R%d_cambridge_thetapT_E%d_thetacut.pdf",r,Ecut));
///////end of with theta cut
*/

// analysis of number of jets, 3+jets / 2+jets

   jettwopT = 0;
   jetthreepT = 0;
   ratiojetpT = 0.;

   jettwopT2 = 0;
   jetthreepT2 = 0;
   ratiojetpT2 = 0.;


 //  max_nb_jets = (int)(*hist_nb_jets_pTcut).GetXaxis()->GetXmax();
   max_nb_jets = 7;
   if (pTcut ==0 or Ecut ==0) max_nb_jets = 30;

   cout << "max_nb_jets : " << max_nb_jets << endl;
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


   ratiojetpT = jetthreepT/jettwopT;
   ratiojetpT2 = jetthreepT2/jettwopT2;

    jettwoE = 0;
    jetthreeE = 0;
    ratiojetE = 0.;

    jettwoE2 = 0;
    jetthreeE2 = 0;
    ratiojetE2 = 0.;



 //  max_nb_jets = (int)(*hist_nb_jets_Ecut).GetXaxis()->GetXmax();
   cout << "max_nb_jets : " << max_nb_jets << endl;
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

   ratiojetE = jetthreeE/jettwoE;
   ratiojetE2 = jetthreeE2/jettwoE2;

   TText *jetratiopT = new TText(0.15, 0.7, Form("3+jets / 2+jets = %0.3f",ratiojetpT));
   jetratiopT->SetNDC(); // text position defined within [0,1]
   jetratiopT->SetTextSize(0.05);
   jetratiopT->SetTextColor(kBlue);


   TText *jetratioE = new TText(0.15, 0.7, Form("3+jets / 2+jets = %0.3f",ratiojetE));
   jetratioE->SetNDC(); // text position defined within [0,1]
   jetratioE->SetTextSize(0.05);
   jetratioE->SetTextColor(kBlue);


   TText *jetratiopT2 = new TText(0.15, 0.65, Form("3+jets / 2+jets = %0.3f",ratiojetpT2));
   jetratiopT2->SetNDC(); // text position defined within [0,1]
   jetratiopT2->SetTextSize(0.05);
   jetratiopT2->SetTextColor(kRed);


   TText *jetratioE2 = new TText(0.15, 0.65, Form("3+jets / 2+jets = %0.3f",ratiojetE2));
   jetratioE2->SetNDC(); // text position defined within [0,1]
   jetratioE2->SetTextSize(0.05);
   jetratioE2->SetTextColor(kRed);




   TCanvas *c7 = new TCanvas("c7", "cambridge number of jets", 800, 650);
   TCanvas *c8 = new TCanvas("c8", "cambridge number of jets", 800, 650);

   c7->cd();
   if (pTcut != 0)
   {
     hist_nb_jets_pTcut->GetXaxis()->SetRangeUser(0,5);
     hist_nb_jets_pTcut2->GetXaxis()->SetRangeUser(0,5);
   }
   hist_nb_jets_pTcut->SetLineColor(kBlue);
   hist_nb_jets_pTcut->Draw();
   hist_nb_jets_pTcut2->SetLineColor(kRed);
   hist_nb_jets_pTcut2->Draw("SAME");
   conesize->Draw();
   t_pTcut->Draw();
   theta_range->Draw();
   without_theta->Draw();
   jetratiopT->Draw();
   jetratiopT2->Draw();
   c7->Update();
   c7->SaveAs(Form("cambridge_graphs/R%d_cambridge_nb_jets_pT%d.pdf",r,pTcut));


   c8->cd();
   if (Ecut != 0)
   {
     hist_nb_jets_Ecut->GetXaxis()->SetRangeUser(0,5);
     hist_nb_jets_Ecut2->GetXaxis()->SetRangeUser(0,5);
   }
   hist_nb_jets_Ecut->SetLineColor(kBlue);
   hist_nb_jets_Ecut->Draw();
   hist_nb_jets_Ecut2->SetLineColor(kRed);
   hist_nb_jets_Ecut2->Draw("SAME");
   conesize->Draw();
   t_Ecut->Draw();
   theta_range->Draw();
   without_theta->Draw();
   jetratioE->Draw();
   jetratioE2->Draw();
   c8->Update();
   c8->SaveAs(Form("cambridge_graphs/R%d_cambridge_nb_jets_E%d.pdf",r,Ecut));


   // Definition in the beginning
   c3->cd();
   hist_theta_pTcut2->SetFillColor(i+2);
   if (pTcut !=0)
   {
     hist_theta_pTcut2->Draw("SAME");
     conesize->Draw();
     t_pTcut->SetX(0.15);
     t_pTcut->SetY(0.7-0.05*i);
     t_pTcut->SetTextSize(0.04);
     t_pTcut->SetTextColor(i+2);
     t_pTcut->Draw("SAME");
     theta_range->Draw();
     c3->Update();
   }
//      c3->SaveAs(Form("cambridge_graphs/R%d_cambridge_theta_distritution_pT%d.pdf",r,pTcut));

   c4->cd();
   hist_theta_Ecut2->SetFillColor(i+2);
   if (pTcut !=0)
   {
     hist_theta_Ecut2->Draw("SAME");
     conesize->Draw();
     t_Ecut->SetX(0.15);
     t_Ecut->SetY(0.7-0.05*i);
     t_Ecut->SetTextSize(0.04);
     t_Ecut->SetTextColor(i+2);
     t_Ecut->Draw("SAME");
     theta_range->Draw();
     c4->Update();
   }
//      c4->SaveAs(Form("cambridge_graphs/R%d_cambridge_theta_distritution_E%d.pdf",r,Ecut));


   if (Ecut == 0. or pTcut==0.)
   {
     hist_E->Write();
     hist_pT->Write();
     hist_E2->Write();
     hist_pT2->Write();
   }

   hist_theta_pTcut->Write();
   hist_theta_Ecut->Write();
   hist_thetaE->Write();
   hist_thetapT->Write();
   hist_nb_jets_Ecut->Write();
   hist_nb_jets_pTcut->Write();

   hist_theta_pTcut2->Write();
   hist_theta_Ecut2->Write();
   hist_thetaE2->Write();
   hist_thetapT2->Write();
   hist_nb_jets_Ecut2->Write();
   hist_nb_jets_pTcut2->Write();


 } // end of Ecut and pTcut

 c3->SaveAs(Form("cambridge_graphs/R%d_cambridge_theta_distritution_pTcut.pdf",r));
 c4->SaveAs(Form("cambridge_graphs/R%d_cambridge_theta_distritution_Ecut.pdf",r));

}

void R6cut::Loop_kt()
{

double r_cone = 0.6;

if (fChain == 0) return;

// corresponds to event number
Long64_t nentries = fChain->GetEntriesFast();

Int_t r = r_cone*10;

Int_t nbin = 100;
Double_t xmin = 0.;
Double_t xmax = 50.;

Int_t angle_nbin = 150;

Int_t Ecut = 0;
Int_t pTcut= 0;
vector<int> pTcuts = {0,5,10,15,20,25};
vector<int> Ecuts = {0,5,10,15,20,25};

Double_t theta_min = M_PI/2.-0.55;
Double_t theta_max = M_PI/2.+0.55;

Int_t jetcountpT =0;
Int_t jetcountE=0;

Double_t jetthreepT=0;
Double_t jettwopT=0;
Double_t ratiojetpT=0.;

Double_t jetthreeE=0.;
Double_t jettwoE=0;
Double_t ratiojetE=0.;

//theta cut
Int_t jetcountpT2 =0;
Int_t jetcountE2=0;

Double_t jetthreepT2=0;
Double_t jettwopT2=0;
Double_t ratiojetpT2=0.;

Double_t jetthreeE2=0.;
Double_t jettwoE2=0;
Double_t ratiojetE2=0.;
//without theta cut

Int_t max_nb_jets =0;

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


TFile *kinematics = new TFile(Form("R%d_kinematics_kt.root",r),"RECREATE");


TCanvas *c3 = new TCanvas("c3", "kt #theta distribution", 800, 650);
TCanvas *c4 = new TCanvas("c4", "kt #theta distribution", 800, 650);



for(int i=0; i<pTcuts.size(); i++)
{
  Ecut = Ecuts[i];
  pTcut = pTcuts[i];

  TText *t_pTcut = new TText(0.15, 0.85, Form("pT > %d GeV",pTcut));
  t_pTcut->SetNDC();
  t_pTcut->SetTextSize(0.05);
  t_pTcut->SetTextColor(kGreen+2);

  TText *t_Ecut = new TText(0.15, 0.85, Form("E > %d GeV",Ecut));
  t_Ecut->SetNDC();
  t_Ecut->SetTextSize(0.05);
  t_Ecut->SetTextColor(kGreen+2);

/*
  if (i!=0) {xmin = Ecuts[i]-5;}
  nbin = nentries/(xmax-xmin);
*/

//without theta cut
TH1D* hist_pT = new TH1D("hist_pT", "pT cut for kt ;pT(GeV); Counts", nbin, xmin, xmax);
TH1D* hist_E = new TH1D("hist_E", "E cut for kt ;E(GeV); Counts", nbin, xmin, xmax);

TH1D* hist_theta_pTcut = new TH1D("hist_theta_pTcut", "kt #theta distribution ;#theta; Counts", nbin , xmin, 3.2);
TH1D* hist_theta_Ecut = new TH1D("hist_theta_Ecut", "kt #theta distribution ;#theta; Counts", nbin, xmin, 3.2);
//   TH1D* hist_phi = new TH1D("hist_phi", "kt #phi distribution ;#phi; Counts", nbin, xmin, 1.7);

//   TH2F* hist_thetaphi = new TH2F("hist_thetaphi", "#phi-#theta;#phi;#theta",angle_nbin, 0.,1.7,100,0.,3.2);
TH2F* hist_thetaE = new TH2F(Form("hist_thetaE_pTcut%d",pTcut), "#theta-E;E(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
TH2F* hist_thetapT = new TH2F(Form("hist_thetapT_Ecut%d",Ecut), "#theta-pT;pT(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
//   TH2F* hist_phipT = new TH2F("hist_phipT", ";pT(GeV);#phi",angle_nbin, 0.,50.,100,0.,1.7);
//   TH2F* hist_phiE = new TH2F("hist_phiE", ";E(GeV);#phi",angle_nbin, 0.,50.,100,0.,1.7);

TH1D* hist_nb_jets_pTcut = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (kt); Number of jets; Counts",60,0.,30.);
TH1D* hist_nb_jets_Ecut = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (kt); Number of jets; Counts", 60,0.,30.);
/////end of without thetacut



//theta cut histogram
TH1D* hist_pT2 = new TH1D("hist_pT", "pT cut for kt ;pT(GeV); Counts", nbin, xmin, xmax);
TH1D* hist_E2 = new TH1D("hist_E", "E cut for kt ;E(GeV); Counts", nbin, xmin, xmax);

TH1D* hist_theta_pTcut2 = new TH1D("hist_theta_pTcut", "kt #theta distribution ;#theta; Counts", nbin , xmin, 3.2);
TH1D* hist_theta_Ecut2 = new TH1D("hist_theta_Ecut", "kt #theta distribution ;#theta; Counts", nbin, xmin, 3.2);

TH2F* hist_thetaE2 = new TH2F(Form("hist_thetaE_pTcut%d",pTcut), "#theta-E;E(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
TH2F* hist_thetapT2 = new TH2F(Form("hist_thetapT_Ecut%d",Ecut), "#theta-pT;pT(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);

TH1D* hist_nb_jets_pTcut2 = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (kt); Number of jets; Counts",60,0.,30.);
TH1D* hist_nb_jets_Ecut2 = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (kt); Number of jets; Counts", 60,0.,30.);
//////end of theta cut histogram



Long64_t nbytes = 0, nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   b_jets_kt_pT->GetEntry(jentry);
   b_jets_kt_E->GetEntry(jentry);
   b_jets_kt_theta->GetEntry(jentry);
   b_jets_kt_phi->GetEntry(jentry);
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   // if (Cut(ientry) < 0) continue;

   jetcountpT=0;
   jetcountE=0;

   jetcountpT2=0;
   jetcountE2=0;


   for(int i=0; i<(*jets_kt_pT).size(); i++)
   {


     if((*jets_kt_pT)[i]>=pTcut)
     {
       hist_pT->Fill((*jets_kt_pT)[i]);
       hist_theta_pTcut->Fill((*jets_kt_theta)[i]);
       hist_thetaE->Fill((*jets_kt_E)[i],(*jets_kt_theta)[i]);
       jetcountpT++;

       if (((*jets_kt_theta)[i]>theta_min) && ((*jets_kt_theta)[i]<theta_max))
       {
         hist_pT2->Fill((*jets_kt_pT)[i]);
         hist_theta_pTcut2->Fill((*jets_kt_theta)[i]);
         hist_thetaE2->Fill((*jets_kt_E)[i],(*jets_kt_theta)[i]);
         jetcountpT2++;
       }

     }


     if((*jets_kt_E)[i]>=Ecut)
     {
       hist_E->Fill((*jets_kt_E)[i]);
       hist_theta_Ecut->Fill((*jets_kt_theta)[i]);
       hist_thetapT->Fill((*jets_kt_pT)[i],(*jets_kt_theta)[i]);
       jetcountE++;

       if (((*jets_kt_theta)[i]>theta_min) && ((*jets_kt_theta)[i]<theta_max))
       {
         hist_E2->Fill((*jets_kt_E)[i]);
         hist_theta_Ecut2->Fill((*jets_kt_theta)[i]);
         hist_thetapT2->Fill((*jets_kt_pT)[i],(*jets_kt_theta)[i]);
         jetcountE2++;
       }

     }


   } // end of loop of 1 event

   hist_nb_jets_pTcut->Fill(jetcountpT);
   hist_nb_jets_Ecut->Fill(jetcountE);

   hist_nb_jets_pTcut2->Fill(jetcountpT2);
   hist_nb_jets_Ecut2->Fill(jetcountE2);

}//end of loop of all events

   TCanvas *c1 = new TCanvas("c1", "pT cut for kt", 800, 650);
   TCanvas *c2 = new TCanvas("c2", "E cut for kt", 800, 650);



   c1->cd();
   hist_pT->SetLineColor(kBlue);
   hist_pT->Draw();
   hist_pT2->SetLineColor(kRed);
   hist_pT2->Draw("SAME");
   conesize->Draw();
   theta_range->Draw();
   without_theta->Draw();
   c1->Update();
   //c1->Draw();
   c1->SaveAs(Form("kt_graphs/R%d_kt_pT%d.pdf",r,pTcut));


   c2->cd();
   hist_E->SetLineColor(kBlue);
   hist_E->Draw();
   hist_E2->SetLineColor(kRed);
   hist_E2->Draw("SAME");
   conesize->Draw();
   theta_range->Draw();
   without_theta->Draw();
   c2->Update();
 //  c2->Draw();
   c2->SaveAs(Form("kt_graphs/R%d_kt_E%d.pdf",r,Ecut));


/*
////////without theta cut////////////
   TCanvas *c5 = new TCanvas("c5", "kt #theta-#pT", 800, 650);
   TCanvas *c6 = new TCanvas("c6", "kt #theta-#E", 800, 650);
   //gStyle->SetOptStat(0); // 그림 그렸을때 statistical box를 없애줌 (0)

   c5->cd();
   hist_thetaE->Draw("LEGO");
   conesize->Draw();
   t_pTcut->Draw();
   without_theta->Draw();
   c5->Update();
   c5->SaveAs(Form("kt_graphs/R%d_kt_thetaE_pT%d.pdf",r,Ecut));

   c6->cd();
   hist_thetapT->Draw("LEGO");
   conesize->Draw();
   without_theta->Draw();
   t_Ecut->Draw();
   c6->Update();
   c6->SaveAs(Form("kt_graphs/R%d_kt_thetapT_E%d.pdf",r,Ecut));
/////////end of without theta cut



///////with theta cut ////////
   TCanvas *c9 = new TCanvas("c9", "kt #theta-#pT", 800, 650);
   TCanvas *c10 = new TCanvas("c10", "kt #theta-#E", 800, 650);
   //gStyle->SetOptStat(0); // 그림 그렸을때 statistical box를 없애줌 (0)

   c9->cd();
   hist_thetaE2->Draw("LEGO");
   conesize->Draw();
   t_pTcut->Draw();
   theta_range->Draw();
   c9->Update();
   c9->SaveAs(Form("kt_graphs/R%d_kt_thetaE_pT%d_thetacut.pdf",r,Ecut));

   c10->cd();
   hist_thetapT2->Draw("LEGO");
   conesize->Draw();
   theta_range->Draw();
   t_Ecut->Draw();
   c10->Update();
   c10->SaveAs(Form("kt_graphs/R%d_kt_thetapT_E%d_thetacut.pdf",r,Ecut));
///////end of with theta cut
*/

// analysis of number of jets, 3+jets / 2+jets

   jettwopT = 0;
   jetthreepT = 0;
   ratiojetpT = 0.;

   jettwopT2 = 0;
   jetthreepT2 = 0;
   ratiojetpT2 = 0.;


 //  max_nb_jets = (int)(*hist_nb_jets_pTcut).GetXaxis()->GetXmax();
   max_nb_jets = 7;
   if (pTcut ==0 or Ecut ==0) max_nb_jets = 30;

   cout << "max_nb_jets : " << max_nb_jets << endl;
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


   ratiojetpT = jetthreepT/jettwopT;
   ratiojetpT2 = jetthreepT2/jettwopT2;

    jettwoE = 0;
    jetthreeE = 0;
    ratiojetE = 0.;

    jettwoE2 = 0;
    jetthreeE2 = 0;
    ratiojetE2 = 0.;



 //  max_nb_jets = (int)(*hist_nb_jets_Ecut).GetXaxis()->GetXmax();
   cout << "max_nb_jets : " << max_nb_jets << endl;
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

   ratiojetE = jetthreeE/jettwoE;
   ratiojetE2 = jetthreeE2/jettwoE2;

   TText *jetratiopT = new TText(0.15, 0.7, Form("3+jets / 2+jets = %0.3f",ratiojetpT));
   jetratiopT->SetNDC(); // text position defined within [0,1]
   jetratiopT->SetTextSize(0.05);
   jetratiopT->SetTextColor(kBlue);


   TText *jetratioE = new TText(0.15, 0.7, Form("3+jets / 2+jets = %0.3f",ratiojetE));
   jetratioE->SetNDC(); // text position defined within [0,1]
   jetratioE->SetTextSize(0.05);
   jetratioE->SetTextColor(kBlue);


   TText *jetratiopT2 = new TText(0.15, 0.65, Form("3+jets / 2+jets = %0.3f",ratiojetpT2));
   jetratiopT2->SetNDC(); // text position defined within [0,1]
   jetratiopT2->SetTextSize(0.05);
   jetratiopT2->SetTextColor(kRed);


   TText *jetratioE2 = new TText(0.15, 0.65, Form("3+jets / 2+jets = %0.3f",ratiojetE2));
   jetratioE2->SetNDC(); // text position defined within [0,1]
   jetratioE2->SetTextSize(0.05);
   jetratioE2->SetTextColor(kRed);




   TCanvas *c7 = new TCanvas("c7", "kt number of jets", 800, 650);
   TCanvas *c8 = new TCanvas("c8", "kt number of jets", 800, 650);

   c7->cd();
   if (pTcut != 0)
   {
     hist_nb_jets_pTcut->GetXaxis()->SetRangeUser(0,5);
     hist_nb_jets_pTcut2->GetXaxis()->SetRangeUser(0,5);
   }
   hist_nb_jets_pTcut->SetLineColor(kBlue);
   hist_nb_jets_pTcut->Draw();
   hist_nb_jets_pTcut2->SetLineColor(kRed);
   hist_nb_jets_pTcut2->Draw("SAME");
   conesize->Draw();
   t_pTcut->Draw();
   theta_range->Draw();
   without_theta->Draw();
   jetratiopT->Draw();
   jetratiopT2->Draw();
   c7->Update();
   c7->SaveAs(Form("kt_graphs/R%d_kt_nb_jets_pT%d.pdf",r,pTcut));


   c8->cd();
   if (Ecut != 0)
   {
     hist_nb_jets_Ecut->GetXaxis()->SetRangeUser(0,5);
     hist_nb_jets_Ecut2->GetXaxis()->SetRangeUser(0,5);
   }
   hist_nb_jets_Ecut->SetLineColor(kBlue);
   hist_nb_jets_Ecut->Draw();
   hist_nb_jets_Ecut2->SetLineColor(kRed);
   hist_nb_jets_Ecut2->Draw("SAME");
   conesize->Draw();
   t_Ecut->Draw();
   theta_range->Draw();
   without_theta->Draw();
   jetratioE->Draw();
   jetratioE2->Draw();
   c8->Update();
   c8->SaveAs(Form("kt_graphs/R%d_kt_nb_jets_E%d.pdf",r,Ecut));


   // Definition in the beginning
   c3->cd();
   hist_theta_pTcut2->SetFillColor(i+2);
   if (pTcut !=0)
   {
     hist_theta_pTcut2->Draw("SAME");
     conesize->Draw();
     t_pTcut->SetX(0.15);
     t_pTcut->SetY(0.7-0.05*i);
     t_pTcut->SetTextSize(0.04);
     t_pTcut->SetTextColor(i+2);
     t_pTcut->Draw("SAME");
     theta_range->Draw();
     c3->Update();
   }
//      c3->SaveAs(Form("kt_graphs/R%d_kt_theta_distritution_pT%d.pdf",r,pTcut));

   c4->cd();
   hist_theta_Ecut2->SetFillColor(i+2);
   if (pTcut !=0)
   {
     hist_theta_Ecut2->Draw("SAME");
     conesize->Draw();
     t_Ecut->SetX(0.15);
     t_Ecut->SetY(0.7-0.05*i);
     t_Ecut->SetTextSize(0.04);
     t_Ecut->SetTextColor(i+2);
     t_Ecut->Draw("SAME");
     theta_range->Draw();
     c4->Update();
   }
//      c4->SaveAs(Form("kt_graphs/R%d_kt_theta_distritution_E%d.pdf",r,Ecut));


   if (Ecut == 0. or pTcut==0.)
   {
     hist_E->Write();
     hist_pT->Write();
     hist_E2->Write();
     hist_pT2->Write();
   }

   hist_theta_pTcut->Write();
   hist_theta_Ecut->Write();
   hist_thetaE->Write();
   hist_thetapT->Write();
   hist_nb_jets_Ecut->Write();
   hist_nb_jets_pTcut->Write();

   hist_theta_pTcut2->Write();
   hist_theta_Ecut2->Write();
   hist_thetaE2->Write();
   hist_thetapT2->Write();
   hist_nb_jets_Ecut2->Write();
   hist_nb_jets_pTcut2->Write();


 } // end of Ecut and pTcut

 c3->SaveAs(Form("kt_graphs/R%d_kt_theta_distritution_pTcut.pdf",r));
 c4->SaveAs(Form("kt_graphs/R%d_kt_theta_distritution_Ecut.pdf",r));

}

void R6cut::Loop_ee_genkt()
{

double r_cone = 0.6;

if (fChain == 0) return;

// corresponds to event number
Long64_t nentries = fChain->GetEntriesFast();

Int_t r = r_cone*10;

Int_t nbin = 100;
Double_t xmin = 0.;
Double_t xmax = 50.;

Int_t angle_nbin = 150;

Int_t Ecut = 0;
Int_t pTcut= 0;
vector<int> pTcuts = {0,5,10,15,20,25};
vector<int> Ecuts = {0,5,10,15,20,25};

Double_t theta_min = M_PI/2.-0.55;
Double_t theta_max = M_PI/2.+0.55;

Int_t jetcountpT =0;
Int_t jetcountE=0;

Double_t jetthreepT=0;
Double_t jettwopT=0;
Double_t ratiojetpT=0.;

Double_t jetthreeE=0.;
Double_t jettwoE=0;
Double_t ratiojetE=0.;

//theta cut
Int_t jetcountpT2 =0;
Int_t jetcountE2=0;

Double_t jetthreepT2=0;
Double_t jettwopT2=0;
Double_t ratiojetpT2=0.;

Double_t jetthreeE2=0.;
Double_t jettwoE2=0;
Double_t ratiojetE2=0.;
//without theta cut

Int_t max_nb_jets =0;

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


TFile *kinematics = new TFile(Form("R%d_kinematics_ee_genkt.root",r),"RECREATE");


TCanvas *c3 = new TCanvas("c3", "ee_genkt #theta distribution", 800, 650);
TCanvas *c4 = new TCanvas("c4", "ee_genkt #theta distribution", 800, 650);



for(int i=0; i<pTcuts.size(); i++)
{
  Ecut = Ecuts[i];
  pTcut = pTcuts[i];

  TText *t_pTcut = new TText(0.15, 0.85, Form("pT > %d GeV",pTcut));
  t_pTcut->SetNDC();
  t_pTcut->SetTextSize(0.05);
  t_pTcut->SetTextColor(kGreen+2);

  TText *t_Ecut = new TText(0.15, 0.85, Form("E > %d GeV",Ecut));
  t_Ecut->SetNDC();
  t_Ecut->SetTextSize(0.05);
  t_Ecut->SetTextColor(kGreen+2);

/*
  if (i!=0) {xmin = Ecuts[i]-5;}
  nbin = nentries/(xmax-xmin);
*/

//without theta cut
TH1D* hist_pT = new TH1D("hist_pT", "pT cut for ee_genkt ;pT(GeV); Counts", nbin, xmin, xmax);
TH1D* hist_E = new TH1D("hist_E", "E cut for ee_genkt ;E(GeV); Counts", nbin, xmin, xmax);

TH1D* hist_theta_pTcut = new TH1D("hist_theta_pTcut", "ee_genkt #theta distribution ;#theta; Counts", nbin , xmin, 3.2);
TH1D* hist_theta_Ecut = new TH1D("hist_theta_Ecut", "ee_genkt #theta distribution ;#theta; Counts", nbin, xmin, 3.2);
//   TH1D* hist_phi = new TH1D("hist_phi", "ee_genkt #phi distribution ;#phi; Counts", nbin, xmin, 1.7);

//   TH2F* hist_thetaphi = new TH2F("hist_thetaphi", "#phi-#theta;#phi;#theta",angle_nbin, 0.,1.7,100,0.,3.2);
TH2F* hist_thetaE = new TH2F(Form("hist_thetaE_pTcut%d",pTcut), "#theta-E;E(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
TH2F* hist_thetapT = new TH2F(Form("hist_thetapT_Ecut%d",Ecut), "#theta-pT;pT(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
//   TH2F* hist_phipT = new TH2F("hist_phipT", ";pT(GeV);#phi",angle_nbin, 0.,50.,100,0.,1.7);
//   TH2F* hist_phiE = new TH2F("hist_phiE", ";E(GeV);#phi",angle_nbin, 0.,50.,100,0.,1.7);

TH1D* hist_nb_jets_pTcut = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (ee_genkt); Number of jets; Counts",60,0.,30.);
TH1D* hist_nb_jets_Ecut = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (ee_genkt); Number of jets; Counts", 60,0.,30.);
/////end of without thetacut



//theta cut histogram
TH1D* hist_pT2 = new TH1D("hist_pT", "pT cut for ee_genkt ;pT(GeV); Counts", nbin, xmin, xmax);
TH1D* hist_E2 = new TH1D("hist_E", "E cut for ee_genkt ;E(GeV); Counts", nbin, xmin, xmax);

TH1D* hist_theta_pTcut2 = new TH1D("hist_theta_pTcut", "ee_genkt #theta distribution ;#theta; Counts", nbin , xmin, 3.2);
TH1D* hist_theta_Ecut2 = new TH1D("hist_theta_Ecut", "ee_genkt #theta distribution ;#theta; Counts", nbin, xmin, 3.2);

TH2F* hist_thetaE2 = new TH2F(Form("hist_thetaE_pTcut%d",pTcut), "#theta-E;E(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);
TH2F* hist_thetapT2 = new TH2F(Form("hist_thetapT_Ecut%d",Ecut), "#theta-pT;pT(GeV);#theta",angle_nbin, 0.,50.,100,0.,3.2);

TH1D* hist_nb_jets_pTcut2 = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (ee_genkt); Number of jets; Counts",60,0.,30.);
TH1D* hist_nb_jets_Ecut2 = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (ee_genkt); Number of jets; Counts", 60,0.,30.);
//////end of theta cut histogram



Long64_t nbytes = 0, nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   b_jets_ee_genkt_pT->GetEntry(jentry);
   b_jets_ee_genkt_E->GetEntry(jentry);
   b_jets_ee_genkt_theta->GetEntry(jentry);
   b_jets_ee_genkt_phi->GetEntry(jentry);
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   // if (Cut(ientry) < 0) continue;

   jetcountpT=0;
   jetcountE=0;

   jetcountpT2=0;
   jetcountE2=0;


   for(int i=0; i<(*jets_ee_genkt_pT).size(); i++)
   {


     if((*jets_ee_genkt_pT)[i]>=pTcut)
     {
       hist_pT->Fill((*jets_ee_genkt_pT)[i]);
       hist_theta_pTcut->Fill((*jets_ee_genkt_theta)[i]);
       hist_thetaE->Fill((*jets_ee_genkt_E)[i],(*jets_ee_genkt_theta)[i]);
       jetcountpT++;

       if (((*jets_ee_genkt_theta)[i]>theta_min) && ((*jets_ee_genkt_theta)[i]<theta_max))
       {
         hist_pT2->Fill((*jets_ee_genkt_pT)[i]);
         hist_theta_pTcut2->Fill((*jets_ee_genkt_theta)[i]);
         hist_thetaE2->Fill((*jets_ee_genkt_E)[i],(*jets_ee_genkt_theta)[i]);
         jetcountpT2++;
       }

     }


     if((*jets_ee_genkt_E)[i]>=Ecut)
     {
       hist_E->Fill((*jets_ee_genkt_E)[i]);
       hist_theta_Ecut->Fill((*jets_ee_genkt_theta)[i]);
       hist_thetapT->Fill((*jets_ee_genkt_pT)[i],(*jets_ee_genkt_theta)[i]);
       jetcountE++;

       if (((*jets_ee_genkt_theta)[i]>theta_min) && ((*jets_ee_genkt_theta)[i]<theta_max))
       {
         hist_E2->Fill((*jets_ee_genkt_E)[i]);
         hist_theta_Ecut2->Fill((*jets_ee_genkt_theta)[i]);
         hist_thetapT2->Fill((*jets_ee_genkt_pT)[i],(*jets_ee_genkt_theta)[i]);
         jetcountE2++;
       }

     }


   } // end of loop of 1 event

   hist_nb_jets_pTcut->Fill(jetcountpT);
   hist_nb_jets_Ecut->Fill(jetcountE);

   hist_nb_jets_pTcut2->Fill(jetcountpT2);
   hist_nb_jets_Ecut2->Fill(jetcountE2);

}//end of loop of all events

   TCanvas *c1 = new TCanvas("c1", "pT cut for ee_genkt", 800, 650);
   TCanvas *c2 = new TCanvas("c2", "E cut for ee_genkt", 800, 650);



   c1->cd();
   hist_pT->SetLineColor(kBlue);
   hist_pT->Draw();
   hist_pT2->SetLineColor(kRed);
   hist_pT2->Draw("SAME");
   conesize->Draw();
   theta_range->Draw();
   without_theta->Draw();
   c1->Update();
   //c1->Draw();
   c1->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_pT%d.pdf",r,pTcut));


   c2->cd();
   hist_E->SetLineColor(kBlue);
   hist_E->Draw();
   hist_E2->SetLineColor(kRed);
   hist_E2->Draw("SAME");
   conesize->Draw();
   theta_range->Draw();
   without_theta->Draw();
   c2->Update();
 //  c2->Draw();
   c2->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_E%d.pdf",r,Ecut));


/*
////////without theta cut////////////
   TCanvas *c5 = new TCanvas("c5", "ee_genkt #theta-#pT", 800, 650);
   TCanvas *c6 = new TCanvas("c6", "ee_genkt #theta-#E", 800, 650);
   //gStyle->SetOptStat(0); // 그림 그렸을때 statistical box를 없애줌 (0)

   c5->cd();
   hist_thetaE->Draw("LEGO");
   conesize->Draw();
   t_pTcut->Draw();
   without_theta->Draw();
   c5->Update();
   c5->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_thetaE_pT%d.pdf",r,Ecut));

   c6->cd();
   hist_thetapT->Draw("LEGO");
   conesize->Draw();
   without_theta->Draw();
   t_Ecut->Draw();
   c6->Update();
   c6->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_thetapT_E%d.pdf",r,Ecut));
/////////end of without theta cut



///////with theta cut ////////
   TCanvas *c9 = new TCanvas("c9", "ee_genkt #theta-#pT", 800, 650);
   TCanvas *c10 = new TCanvas("c10", "ee_genkt #theta-#E", 800, 650);
   //gStyle->SetOptStat(0); // 그림 그렸을때 statistical box를 없애줌 (0)

   c9->cd();
   hist_thetaE2->Draw("LEGO");
   conesize->Draw();
   t_pTcut->Draw();
   theta_range->Draw();
   c9->Update();
   c9->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_thetaE_pT%d_thetacut.pdf",r,Ecut));

   c10->cd();
   hist_thetapT2->Draw("LEGO");
   conesize->Draw();
   theta_range->Draw();
   t_Ecut->Draw();
   c10->Update();
   c10->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_thetapT_E%d_thetacut.pdf",r,Ecut));
///////end of with theta cut
*/

// analysis of number of jets, 3+jets / 2+jets

   jettwopT = 0;
   jetthreepT = 0;
   ratiojetpT = 0.;

   jettwopT2 = 0;
   jetthreepT2 = 0;
   ratiojetpT2 = 0.;


 //  max_nb_jets = (int)(*hist_nb_jets_pTcut).GetXaxis()->GetXmax();
   max_nb_jets = 7;
   if (pTcut ==0 or Ecut ==0) max_nb_jets = 30;

   cout << "max_nb_jets : " << max_nb_jets << endl;
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


   ratiojetpT = jetthreepT/jettwopT;
   ratiojetpT2 = jetthreepT2/jettwopT2;

    jettwoE = 0;
    jetthreeE = 0;
    ratiojetE = 0.;

    jettwoE2 = 0;
    jetthreeE2 = 0;
    ratiojetE2 = 0.;



 //  max_nb_jets = (int)(*hist_nb_jets_Ecut).GetXaxis()->GetXmax();
   cout << "max_nb_jets : " << max_nb_jets << endl;
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

   ratiojetE = jetthreeE/jettwoE;
   ratiojetE2 = jetthreeE2/jettwoE2;

   TText *jetratiopT = new TText(0.15, 0.7, Form("3+jets / 2+jets = %0.3f",ratiojetpT));
   jetratiopT->SetNDC(); // text position defined within [0,1]
   jetratiopT->SetTextSize(0.05);
   jetratiopT->SetTextColor(kBlue);


   TText *jetratioE = new TText(0.15, 0.7, Form("3+jets / 2+jets = %0.3f",ratiojetE));
   jetratioE->SetNDC(); // text position defined within [0,1]
   jetratioE->SetTextSize(0.05);
   jetratioE->SetTextColor(kBlue);


   TText *jetratiopT2 = new TText(0.15, 0.65, Form("3+jets / 2+jets = %0.3f",ratiojetpT2));
   jetratiopT2->SetNDC(); // text position defined within [0,1]
   jetratiopT2->SetTextSize(0.05);
   jetratiopT2->SetTextColor(kRed);


   TText *jetratioE2 = new TText(0.15, 0.65, Form("3+jets / 2+jets = %0.3f",ratiojetE2));
   jetratioE2->SetNDC(); // text position defined within [0,1]
   jetratioE2->SetTextSize(0.05);
   jetratioE2->SetTextColor(kRed);




   TCanvas *c7 = new TCanvas("c7", "ee_genkt number of jets", 800, 650);
   TCanvas *c8 = new TCanvas("c8", "ee_genkt number of jets", 800, 650);

   c7->cd();
   if (pTcut != 0)
   {
     hist_nb_jets_pTcut->GetXaxis()->SetRangeUser(0,5);
     hist_nb_jets_pTcut2->GetXaxis()->SetRangeUser(0,5);
   }
   hist_nb_jets_pTcut->SetLineColor(kBlue);
   hist_nb_jets_pTcut->Draw();
   hist_nb_jets_pTcut2->SetLineColor(kRed);
   hist_nb_jets_pTcut2->Draw("SAME");
   conesize->Draw();
   t_pTcut->Draw();
   theta_range->Draw();
   without_theta->Draw();
   jetratiopT->Draw();
   jetratiopT2->Draw();
   c7->Update();
   c7->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_nb_jets_pT%d.pdf",r,pTcut));


   c8->cd();
   if (Ecut != 0)
   {
     hist_nb_jets_Ecut->GetXaxis()->SetRangeUser(0,5);
     hist_nb_jets_Ecut2->GetXaxis()->SetRangeUser(0,5);
   }
   hist_nb_jets_Ecut->SetLineColor(kBlue);
   hist_nb_jets_Ecut->Draw();
   hist_nb_jets_Ecut2->SetLineColor(kRed);
   hist_nb_jets_Ecut2->Draw("SAME");
   conesize->Draw();
   t_Ecut->Draw();
   theta_range->Draw();
   without_theta->Draw();
   jetratioE->Draw();
   jetratioE2->Draw();
   c8->Update();
   c8->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_nb_jets_E%d.pdf",r,Ecut));


   // Definition in the beginning
   c3->cd();
   hist_theta_pTcut2->SetFillColor(i+2);
   if (pTcut !=0)
   {
     hist_theta_pTcut2->Draw("SAME");
     conesize->Draw();
     t_pTcut->SetX(0.15);
     t_pTcut->SetY(0.7-0.05*i);
     t_pTcut->SetTextSize(0.04);
     t_pTcut->SetTextColor(i+2);
     t_pTcut->Draw("SAME");
     theta_range->Draw();
     c3->Update();
   }
//      c3->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_theta_distritution_pT%d.pdf",r,pTcut));

   c4->cd();
   hist_theta_Ecut2->SetFillColor(i+2);
   if (pTcut !=0)
   {
     hist_theta_Ecut2->Draw("SAME");
     conesize->Draw();
     t_Ecut->SetX(0.15);
     t_Ecut->SetY(0.7-0.05*i);
     t_Ecut->SetTextSize(0.04);
     t_Ecut->SetTextColor(i+2);
     t_Ecut->Draw("SAME");
     theta_range->Draw();
     c4->Update();
   }
//      c4->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_theta_distritution_E%d.pdf",r,Ecut));


   if (Ecut == 0. or pTcut==0.)
   {
     hist_E->Write();
     hist_pT->Write();
     hist_E2->Write();
     hist_pT2->Write();
   }

   hist_theta_pTcut->Write();
   hist_theta_Ecut->Write();
   hist_thetaE->Write();
   hist_thetapT->Write();
   hist_nb_jets_Ecut->Write();
   hist_nb_jets_pTcut->Write();

   hist_theta_pTcut2->Write();
   hist_theta_Ecut2->Write();
   hist_thetaE2->Write();
   hist_thetapT2->Write();
   hist_nb_jets_Ecut2->Write();
   hist_nb_jets_pTcut2->Write();


 } // end of Ecut and pTcut

 c3->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_theta_distritution_pTcut.pdf",r));
 c4->SaveAs(Form("ee_genkt_graphs/R%d_ee_genkt_theta_distritution_Ecut.pdf",r));

}
