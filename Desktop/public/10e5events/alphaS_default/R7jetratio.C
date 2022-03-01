#define R7jetratio_cxx
#include "R7jetratio.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void R7jetratio::Loop_antikt()
{
//   In a ROOT session, you can do:
//      root> .L R7jetratio.C
//      root> R7jetratio t
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

 Bool_t first = true;

// corresponds to event number
Long64_t nentries = fChain->GetEntriesFast();
double r_cone = 0.7;
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

Double_t jetthreepT=0;
Double_t jettwopT=0;
Double_t ratiojetpT[size];

Double_t jetthreeE=0.;
Double_t jettwoE=0;
Double_t ratiojetE[size];

//theta cut
Int_t jetcountpT2 =0;
Int_t jetcountE2=0;

Double_t jetthreepT2=0;
Double_t jettwopT2=0;
Double_t ratiojetpT2[size];

Double_t jetthreeE2=0.;
Double_t jettwoE2=0;
Double_t ratiojetE2[size];
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


////only wh




   TH2F* hist_jetratio_pT = new TH2F(Form("hist_jetratio_pTcut%d_withoutthetacut",pTcut), "Jet ratio in function of pT cut (antikt); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E = new TH2F(Form("hist_jetratio_Ecut%d_withoutthetacut",Ecut), "Jet ratio in function of E cut (antikt); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);

   TH2F* hist_jetratio_pT2 = new TH2F(Form("hist_jetratio_pTcut%d",pTcut), "Jet ratio in function of pT cut (antikt); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E2 = new TH2F(Form("hist_jetratio_Ecut%d",Ecut), "Jet ratio in function of E cut (antikt); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);



/*
//ONLY when creating root file for the first time.//
   TFile *jetratio = new TFile("antikt_graphs/jetratio/jetratio.root","RECREATE");
   TTree *tree=new TTree("jetratio","Jet ratio");
   tree->Branch("Rvalues", Rvalues, "Rvalues[5]/D");
   tree->Branch("n", &size, "n/I");
   tree->Branch("pTcuts", pTcuts, "pTcuts[n]/D");
   tree->Branch("Ecuts", Ecuts, "Ecuts[n]/D");

   tree->Branch(Form("R%djetratio_pTcut_without_thetaCut",r), ratiojetpT, "ratiojetpT[14]/D");
   tree->Branch(Form("R%djetratio_Ecut_without_thetaCut",r), ratiojetE, "ratiojetE[14]/D");
   tree->Branch(Form("R%djetratio_pTcut",r), ratiojetpT2, "ratiojetpT2[14]/D");
   tree->Branch(Form("R%djetratio_Ecut",r), ratiojetE2, "ratiojetE2[14]/D");
///////////
*/


// size = 14
/////ONLY when adding more branches
   TFile *jetratio = new TFile("antikt_graphs/jetratio/jetratio.root","update");
   TTree *tree= (TTree*) jetratio->Get("jetratio");
   TBranch *b_ratiojetpT = tree->Branch(Form("R%djetratio_pTcut_without_thetaCut",r), ratiojetpT, "ratiojetpT[14]/D");
   TBranch *b_ratiojetE = tree->Branch(Form("R%djetratio_Ecut_without_thetaCut",r), ratiojetE, "ratiojetE[14]/D");
   TBranch *b_ratiojetpT2 = tree->Branch(Form("R%djetratio_pTcut",r), ratiojetpT2, "ratiojetpT2[14]/D");
   TBranch *b_ratiojetE2 = tree->Branch(Form("R%djetratio_Ecut",r), ratiojetE2, "ratiojetE2[14]/D");
////////////////////////////////////


for(int i=0; i<size; i++)
{
  Ecut = Ecuts[i];
  pTcut = pTcuts[i];



 //without theta cut
    TH1D* hist_nb_jets_pTcut = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (antikt) ; Number of jets; Counts",60,0.,30.);
    TH1D* hist_nb_jets_Ecut = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (antikt) ; Number of jets; Counts", 60,0.,30.);

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
 //  if (jetthreepT2/jettwopT2>0.0001)
   ratiojetpT2[i] = jetthreepT2/jettwopT2;

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
 //if (jetthreeE2/jettwoE2>0.0001)
 ratiojetE2[i] = jetthreeE2/jettwoE2;

/*
   if (ratiojetpT2[i]!=0) hist_jetratio_pT2->Fill(pTcut, ratiojetpT2[i]);
   if (ratiojetpT[i]!=0) hist_jetratio_pT->Fill(pTcut, ratiojetpT[i]);

   if (ratiojetE2[i]!=0) hist_jetratio_E2->Fill(Ecut, ratiojetE2[i]);
   if (ratiojetE[i]!=0) hist_jetratio_E->Fill(Ecut, ratiojetE[i]);
*/


 hist_jetratio_pT2->Fill(pTcut, ratiojetpT2[i]);
 cout << "ratiojetpT2 : " << pTcut<< " " << ratiojetpT2[i] << endl;
 hist_jetratio_pT->Fill(pTcut, ratiojetpT[i]);

 hist_jetratio_E2->Fill(Ecut, ratiojetE2[i]);
     cout << "ratiojetE2 : " << Ecut<< " " << ratiojetE2[i] << endl;
 hist_jetratio_E->Fill(Ecut, ratiojetE[i]);



 } // end of Ecut and pTcut

/*
   TText *jetratiopT = new TText(0.15, 0.7, Form(">=3jets / >=2jets = %0.3f",ratiojetpT));
   jetratiopT->SetNDC(); // text position defined within [0,1]
   jetratiopT->SetTextSize(0.05);
   jetratiopT->SetTextColor(kBlue);


   TText *jetratioE = new TText(0.15, 0.7, Form(">=3jets / >=2jets = %0.3f",ratiojetE));
   jetratioE->SetNDC(); // text position defined within [0,1]
   jetratioE->SetTextSize(0.05);
   jetratioE->SetTextColor(kBlue);


   TText *jetratiopT2 = new TText(0.15, 0.65, Form(">=3jets / >=2jets = %0.3f",ratiojetpT2));
   jetratiopT2->SetNDC(); // text position defined within [0,1]
   jetratiopT2->SetTextSize(0.05);
   jetratiopT2->SetTextColor(kRed);


   TText *jetratioE2 = new TText(0.15, 0.65, Form(">=3jets / >=2jets = %0.3f",ratiojetE2));
   jetratioE2->SetNDC(); // text position defined within [0,1]
   jetratioE2->SetTextSize(0.05);
   jetratioE2->SetTextColor(kRed);
*/

   cout << "Loop finished" << endl;

   TCanvas *c1 = new TCanvas("c1", "antikt jet ratio in function of pT cut", 800, 650);
   TCanvas *c2 = new TCanvas("c2", "antikt jet ratio in function of E cut", 800, 650);

   TCanvas *c3 = new TCanvas("c3", "antikt jet ratio in function of pT cut", 800, 650);
   TCanvas *c4 = new TCanvas("c4", "antikt jet ratio in function of E cut", 800, 650);
   TCanvas *c5 = new TCanvas("c5", "antikt jet ratio in function of pT and E cut", 800, 650);

   TGraph *gr1=new TGraph(size, pTcuts,ratiojetpT);
   TGraph *gr3=new TGraph(size, pTcuts,ratiojetpT2);
   TGraph *gr2=new TGraph(size, Ecuts, ratiojetE);
   TGraph *gr4=new TGraph(size, Ecuts, ratiojetE2) ;

   gr1->SetName(Form("graph_R%d_jetratio_pTcut_notheta",r));
   gr3->SetName(Form("graph_R%d_jetratio_pTcut_theta",r));
   gr2->SetName(Form("graph_R%d_jetratio_Ecut_notheta",r));
   gr4->SetName(Form("graph_R%d_jetratio_Ecut_theta",r));
 //  gr5->SetName(Form("graph_R%d_jetratio_pTandEcut_theta",r))

   TText *t_pTcut = new TText(0.6, 0.65, "pT cut");
   t_pTcut->SetNDC();
   t_pTcut->SetTextSize(0.05);
   t_pTcut->SetTextColor(kBlue);

   TText *t_Ecut = new TText(0.6, 0.6, "E cut");
   t_Ecut->SetNDC();
   t_Ecut->SetTextSize(0.05);
   t_Ecut->SetTextColor(kRed);


   c1->cd();
   //hist_jetratio_pT->SetMarkerStyle(21);
   //hist_jetratio_pT->SetMArkerColor(kBlue);
    hist_jetratio_pT->Draw();
//    hist_jetratio_pT2->SetFillColor(kRed);
//    hist_jetratio_pT2->Draw("SAME");

   gr1->SetMarkerStyle(21);
   gr1->Draw("SAME P");
   conesize->Draw();
 //  theta_range->Draw();
   without_theta->Draw();
   c1->Update();
   c1->SaveAs(Form("antikt_graphs/jetratio/R%d_jetratio_pTcut_notheta.pdf",r));


   c2->cd();
    //hist_jetratio_E->SetFillColor(kBlue);
   hist_jetratio_E->Draw();
 //  hist_jetratio_E2->SetFillColor(kRed);
//    hist_jetratio_E2->Draw("SAME");
 gr2->SetMarkerStyle(21);
 gr2->Draw("SAME P");
   conesize->Draw();
 //  theta_range->Draw();
   without_theta->Draw();
   c2->Update();
   c2->SaveAs(Form("antikt_graphs/jetratio/R%d_jetratio_Ecut_notheta.pdf",r));

   c3->cd();
   //hist_jetratio_pT2->SetFillColor(kRed);
   hist_jetratio_pT2->Draw();
   gr3->SetMarkerStyle(21);
   gr3->Draw("SAME P");
   conesize->Draw();
   theta_range->Draw();
 //  without_theta->Draw();
   c3->Update();
   c3->SaveAs(Form("antikt_graphs/jetratio/R%d_jetratio_pTcut_theta.pdf",r));


   c4->cd();

   //hist_jetratio_E2->SetFillColor(kRed);
   hist_jetratio_E2->Draw();
   gr4->SetMarkerStyle(21);
   gr4->Draw("SAME P");
   conesize->Draw();
   theta_range->Draw();
   //without_theta->Draw();
   c4->Update();
   c4->SaveAs(Form("antikt_graphs/jetratio/R%d_jetratio_Ecut_theta.pdf",r));


   c5->cd();
   hist_jetratio_pT2->Draw();
   hist_jetratio_E2->Draw("SAME");
   gr3->SetMarkerColor(kBlue);
   gr3->SetMarkerStyle(21);
   gr3->Draw("SAME P");
   gr4->SetMarkerColor(kRed);
   gr4->SetMarkerStyle(21);
   gr4->Draw("SAME P");
   t_pTcut->Draw();
   t_Ecut->Draw();
   theta_range->Draw();
   conesize->Draw();
   c5->Update();
   c5->SaveAs(Form("antikt_graphs/jetratio/R%d_jetratio_E_and_pT_thetacut.pdf",r));

/*
//ONLY when creating for the first time
   tree->Fill();
   tree->Write();
*/

   //AFTER 2nd run
   b_ratiojetE->Fill();
   b_ratiojetE2->Fill();
   b_ratiojetpT->Fill();
   b_ratiojetpT2->Fill();


   hist_jetratio_pT2->Write();
   hist_jetratio_E->Write();
   hist_jetratio_E2->Write();
   hist_jetratio_pT->Write();
   gr1->Write();
   gr2->Write();
   gr3->Write();
   gr4->Write();




   jetratio->Write();
   jetratio->Close();



}

void R7jetratio::Loop_valencia()
{
//   In a ROOT session, you can do:
//      root> .L R7jetratio.C
//      root> R7jetratio t
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

 Bool_t first = true;

// corresponds to event number
Long64_t nentries = fChain->GetEntriesFast();
double r_cone = 0.7;
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

Double_t jetthreepT=0;
Double_t jettwopT=0;
Double_t ratiojetpT[size];

Double_t jetthreeE=0.;
Double_t jettwoE=0;
Double_t ratiojetE[size];

//theta cut
Int_t jetcountpT2 =0;
Int_t jetcountE2=0;

Double_t jetthreepT2=0;
Double_t jettwopT2=0;
Double_t ratiojetpT2[size];

Double_t jetthreeE2=0.;
Double_t jettwoE2=0;
Double_t ratiojetE2[size];
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


////only wh




   TH2F* hist_jetratio_pT = new TH2F(Form("hist_jetratio_pTcut%d_withoutthetacut",pTcut), "Jet ratio in function of pT cut (valencia); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E = new TH2F(Form("hist_jetratio_Ecut%d_withoutthetacut",Ecut), "Jet ratio in function of E cut (valencia); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);

   TH2F* hist_jetratio_pT2 = new TH2F(Form("hist_jetratio_pTcut%d",pTcut), "Jet ratio in function of pT cut (valencia); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E2 = new TH2F(Form("hist_jetratio_Ecut%d",Ecut), "Jet ratio in function of E cut (valencia); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);



/*
//ONLY when creating root file for the first time.//
   TFile *jetratio = new TFile("valencia_graphs/jetratio/jetratio.root","RECREATE");
   TTree *tree=new TTree("jetratio","Jet ratio");
   tree->Branch("Rvalues", Rvalues, "Rvalues[5]/D");
   tree->Branch("n", &size, "n/I");
   tree->Branch("pTcuts", pTcuts, "pTcuts[n]/D");
   tree->Branch("Ecuts", Ecuts, "Ecuts[n]/D");

   tree->Branch(Form("R%djetratio_pTcut_without_thetaCut",r), ratiojetpT, "ratiojetpT[14]/D");
   tree->Branch(Form("R%djetratio_Ecut_without_thetaCut",r), ratiojetE, "ratiojetE[14]/D");
   tree->Branch(Form("R%djetratio_pTcut",r), ratiojetpT2, "ratiojetpT2[14]/D");
   tree->Branch(Form("R%djetratio_Ecut",r), ratiojetE2, "ratiojetE2[14]/D");
///////////
*/


// size = 14
/////ONLY when adding more branches
   TFile *jetratio = new TFile("valencia_graphs/jetratio/jetratio.root","update");
   TTree *tree= (TTree*) jetratio->Get("jetratio");
   TBranch *b_ratiojetpT = tree->Branch(Form("R%djetratio_pTcut_without_thetaCut",r), ratiojetpT, "ratiojetpT[14]/D");
   TBranch *b_ratiojetE = tree->Branch(Form("R%djetratio_Ecut_without_thetaCut",r), ratiojetE, "ratiojetE[14]/D");
   TBranch *b_ratiojetpT2 = tree->Branch(Form("R%djetratio_pTcut",r), ratiojetpT2, "ratiojetpT2[14]/D");
   TBranch *b_ratiojetE2 = tree->Branch(Form("R%djetratio_Ecut",r), ratiojetE2, "ratiojetE2[14]/D");
////////////////////////////////////


for(int i=0; i<size; i++)
{
  Ecut = Ecuts[i];
  pTcut = pTcuts[i];



 //without theta cut
    TH1D* hist_nb_jets_pTcut = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (valencia) ; Number of jets; Counts",60,0.,30.);
    TH1D* hist_nb_jets_Ecut = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (valencia) ; Number of jets; Counts", 60,0.,30.);

 /////end of without thetacut

 //theta cut histogram
    TH1D* hist_nb_jets_pTcut2 = new TH1D(Form("hist_nb_jets_pTcut%d_2",pTcut), "Number of jets (valencia); Number of jets; Counts",60,0.,30.);
    TH1D* hist_nb_jets_Ecut2 = new TH1D(Form("hist_nb_jets_Ecut%d_2",Ecut), "Number of jets (valencia); Number of jets; Counts", 60,0.,30.);

 //////end of theta cut histogram


Long64_t nbytes = 0, nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   b_jets_valencia_pT->GetEntry(jentry);
   b_jets_valencia_E->GetEntry(jentry);
   b_jets_valencia_theta->GetEntry(jentry);
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   // if (Cut(ientry) < 0) continue;


   jetcountpT=0;
   jetcountE=0;

   jetcountpT2=0;
   jetcountE2=0;


   for(int i=0; i<(*jets_valencia_pT).size(); i++)
   { //for 1 event


     if((*jets_valencia_pT)[i]>=pTcut)
     {
       jetcountpT++;

       if (((*jets_valencia_theta)[i]>theta_min) && ((*jets_valencia_theta)[i]<theta_max))
       {
         jetcountpT2++;
       }

     }


     if((*jets_valencia_E)[i]>=Ecut)
     {
       jetcountE++;

       if (((*jets_valencia_theta)[i]>theta_min) && ((*jets_valencia_theta)[i]<theta_max))
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
 //  if (jetthreepT2/jettwopT2>0.0001)
   ratiojetpT2[i] = jetthreepT2/jettwopT2;

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
 //if (jetthreeE2/jettwoE2>0.0001)
 ratiojetE2[i] = jetthreeE2/jettwoE2;

/*
   if (ratiojetpT2[i]!=0) hist_jetratio_pT2->Fill(pTcut, ratiojetpT2[i]);
   if (ratiojetpT[i]!=0) hist_jetratio_pT->Fill(pTcut, ratiojetpT[i]);

   if (ratiojetE2[i]!=0) hist_jetratio_E2->Fill(Ecut, ratiojetE2[i]);
   if (ratiojetE[i]!=0) hist_jetratio_E->Fill(Ecut, ratiojetE[i]);
*/


 hist_jetratio_pT2->Fill(pTcut, ratiojetpT2[i]);
 cout << "ratiojetpT2 : " << pTcut<< " " << ratiojetpT2[i] << endl;
 hist_jetratio_pT->Fill(pTcut, ratiojetpT[i]);

 hist_jetratio_E2->Fill(Ecut, ratiojetE2[i]);
     cout << "ratiojetE2 : " << Ecut<< " " << ratiojetE2[i] << endl;
 hist_jetratio_E->Fill(Ecut, ratiojetE[i]);



 } // end of Ecut and pTcut

/*
   TText *jetratiopT = new TText(0.15, 0.7, Form(">=3jets / >=2jets = %0.3f",ratiojetpT));
   jetratiopT->SetNDC(); // text position defined within [0,1]
   jetratiopT->SetTextSize(0.05);
   jetratiopT->SetTextColor(kBlue);


   TText *jetratioE = new TText(0.15, 0.7, Form(">=3jets / >=2jets = %0.3f",ratiojetE));
   jetratioE->SetNDC(); // text position defined within [0,1]
   jetratioE->SetTextSize(0.05);
   jetratioE->SetTextColor(kBlue);


   TText *jetratiopT2 = new TText(0.15, 0.65, Form(">=3jets / >=2jets = %0.3f",ratiojetpT2));
   jetratiopT2->SetNDC(); // text position defined within [0,1]
   jetratiopT2->SetTextSize(0.05);
   jetratiopT2->SetTextColor(kRed);


   TText *jetratioE2 = new TText(0.15, 0.65, Form(">=3jets / >=2jets = %0.3f",ratiojetE2));
   jetratioE2->SetNDC(); // text position defined within [0,1]
   jetratioE2->SetTextSize(0.05);
   jetratioE2->SetTextColor(kRed);
*/

   cout << "Loop finished" << endl;

   TCanvas *c1 = new TCanvas("c1", "valencia jet ratio in function of pT cut", 800, 650);
   TCanvas *c2 = new TCanvas("c2", "valencia jet ratio in function of E cut", 800, 650);

   TCanvas *c3 = new TCanvas("c3", "valencia jet ratio in function of pT cut", 800, 650);
   TCanvas *c4 = new TCanvas("c4", "valencia jet ratio in function of E cut", 800, 650);
   TCanvas *c5 = new TCanvas("c5", "valencia jet ratio in function of pT and E cut", 800, 650);

   TGraph *gr1=new TGraph(size, pTcuts,ratiojetpT);
   TGraph *gr3=new TGraph(size, pTcuts,ratiojetpT2);
   TGraph *gr2=new TGraph(size, Ecuts, ratiojetE);
   TGraph *gr4=new TGraph(size, Ecuts, ratiojetE2) ;

   gr1->SetName(Form("graph_R%d_jetratio_pTcut_notheta",r));
   gr3->SetName(Form("graph_R%d_jetratio_pTcut_theta",r));
   gr2->SetName(Form("graph_R%d_jetratio_Ecut_notheta",r));
   gr4->SetName(Form("graph_R%d_jetratio_Ecut_theta",r));
 //  gr5->SetName(Form("graph_R%d_jetratio_pTandEcut_theta",r))

   TText *t_pTcut = new TText(0.6, 0.65, "pT cut");
   t_pTcut->SetNDC();
   t_pTcut->SetTextSize(0.05);
   t_pTcut->SetTextColor(kBlue);

   TText *t_Ecut = new TText(0.6, 0.6, "E cut");
   t_Ecut->SetNDC();
   t_Ecut->SetTextSize(0.05);
   t_Ecut->SetTextColor(kRed);


   c1->cd();
   //hist_jetratio_pT->SetMarkerStyle(21);
   //hist_jetratio_pT->SetMArkerColor(kBlue);
    hist_jetratio_pT->Draw();
//    hist_jetratio_pT2->SetFillColor(kRed);
//    hist_jetratio_pT2->Draw("SAME");

   gr1->SetMarkerStyle(21);
   gr1->Draw("SAME P");
   conesize->Draw();
 //  theta_range->Draw();
   without_theta->Draw();
   c1->Update();
   c1->SaveAs(Form("valencia_graphs/jetratio/R%d_jetratio_pTcut_notheta.pdf",r));


   c2->cd();
    //hist_jetratio_E->SetFillColor(kBlue);
   hist_jetratio_E->Draw();
 //  hist_jetratio_E2->SetFillColor(kRed);
//    hist_jetratio_E2->Draw("SAME");
 gr2->SetMarkerStyle(21);
 gr2->Draw("SAME P");
   conesize->Draw();
 //  theta_range->Draw();
   without_theta->Draw();
   c2->Update();
   c2->SaveAs(Form("valencia_graphs/jetratio/R%d_jetratio_Ecut_notheta.pdf",r));

   c3->cd();
   //hist_jetratio_pT2->SetFillColor(kRed);
   hist_jetratio_pT2->Draw();
   gr3->SetMarkerStyle(21);
   gr3->Draw("SAME P");
   conesize->Draw();
   theta_range->Draw();
 //  without_theta->Draw();
   c3->Update();
   c3->SaveAs(Form("valencia_graphs/jetratio/R%d_jetratio_pTcut_theta.pdf",r));


   c4->cd();

   //hist_jetratio_E2->SetFillColor(kRed);
   hist_jetratio_E2->Draw();
   gr4->SetMarkerStyle(21);
   gr4->Draw("SAME P");
   conesize->Draw();
   theta_range->Draw();
   //without_theta->Draw();
   c4->Update();
   c4->SaveAs(Form("valencia_graphs/jetratio/R%d_jetratio_Ecut_theta.pdf",r));


   c5->cd();
   hist_jetratio_pT2->Draw();
   hist_jetratio_E2->Draw("SAME");
   gr3->SetMarkerColor(kBlue);
   gr3->SetMarkerStyle(21);
   gr3->Draw("SAME P");
   gr4->SetMarkerColor(kRed);
   gr4->SetMarkerStyle(21);
   gr4->Draw("SAME P");
   t_pTcut->Draw();
   t_Ecut->Draw();
   theta_range->Draw();
   conesize->Draw();
   c5->Update();
   c5->SaveAs(Form("valencia_graphs/jetratio/R%d_jetratio_E_and_pT_thetacut.pdf",r));

/*
//ONLY when creating for the first time
   tree->Fill();
   tree->Write();
*/

   //AFTER 2nd run
   b_ratiojetE->Fill();
   b_ratiojetE2->Fill();
   b_ratiojetpT->Fill();
   b_ratiojetpT2->Fill();


   hist_jetratio_pT2->Write();
   hist_jetratio_E->Write();
   hist_jetratio_E2->Write();
   hist_jetratio_pT->Write();
   gr1->Write();
   gr2->Write();
   gr3->Write();
   gr4->Write();




   jetratio->Write();
   jetratio->Close();



}

void R7jetratio::Loop_kt()
{
//   In a ROOT session, you can do:
//      root> .L R7jetratio.C
//      root> R7jetratio t
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

 Bool_t first = true;

// corresponds to event number
Long64_t nentries = fChain->GetEntriesFast();
double r_cone = 0.7;
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

Double_t jetthreepT=0;
Double_t jettwopT=0;
Double_t ratiojetpT[size];

Double_t jetthreeE=0.;
Double_t jettwoE=0;
Double_t ratiojetE[size];

//theta cut
Int_t jetcountpT2 =0;
Int_t jetcountE2=0;

Double_t jetthreepT2=0;
Double_t jettwopT2=0;
Double_t ratiojetpT2[size];

Double_t jetthreeE2=0.;
Double_t jettwoE2=0;
Double_t ratiojetE2[size];
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


////only wh




   TH2F* hist_jetratio_pT = new TH2F(Form("hist_jetratio_pTcut%d_withoutthetacut",pTcut), "Jet ratio in function of pT cut (kt); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E = new TH2F(Form("hist_jetratio_Ecut%d_withoutthetacut",Ecut), "Jet ratio in function of E cut (kt); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);

   TH2F* hist_jetratio_pT2 = new TH2F(Form("hist_jetratio_pTcut%d",pTcut), "Jet ratio in function of pT cut (kt); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E2 = new TH2F(Form("hist_jetratio_Ecut%d",Ecut), "Jet ratio in function of E cut (kt); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);



/*
//ONLY when creating root file for the first time.//
   TFile *jetratio = new TFile("kt_graphs/jetratio/jetratio.root","RECREATE");
   TTree *tree=new TTree("jetratio","Jet ratio");
   tree->Branch("Rvalues", Rvalues, "Rvalues[5]/D");
   tree->Branch("n", &size, "n/I");
   tree->Branch("pTcuts", pTcuts, "pTcuts[n]/D");
   tree->Branch("Ecuts", Ecuts, "Ecuts[n]/D");

   tree->Branch(Form("R%djetratio_pTcut_without_thetaCut",r), ratiojetpT, "ratiojetpT[14]/D");
   tree->Branch(Form("R%djetratio_Ecut_without_thetaCut",r), ratiojetE, "ratiojetE[14]/D");
   tree->Branch(Form("R%djetratio_pTcut",r), ratiojetpT2, "ratiojetpT2[14]/D");
   tree->Branch(Form("R%djetratio_Ecut",r), ratiojetE2, "ratiojetE2[14]/D");
///////////
*/


// size = 14
/////ONLY when adding more branches
   TFile *jetratio = new TFile("kt_graphs/jetratio/jetratio.root","update");
   TTree *tree= (TTree*) jetratio->Get("jetratio");
   TBranch *b_ratiojetpT = tree->Branch(Form("R%djetratio_pTcut_without_thetaCut",r), ratiojetpT, "ratiojetpT[14]/D");
   TBranch *b_ratiojetE = tree->Branch(Form("R%djetratio_Ecut_without_thetaCut",r), ratiojetE, "ratiojetE[14]/D");
   TBranch *b_ratiojetpT2 = tree->Branch(Form("R%djetratio_pTcut",r), ratiojetpT2, "ratiojetpT2[14]/D");
   TBranch *b_ratiojetE2 = tree->Branch(Form("R%djetratio_Ecut",r), ratiojetE2, "ratiojetE2[14]/D");
////////////////////////////////////


for(int i=0; i<size; i++)
{
  Ecut = Ecuts[i];
  pTcut = pTcuts[i];



 //without theta cut
    TH1D* hist_nb_jets_pTcut = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (kt) ; Number of jets; Counts",60,0.,30.);
    TH1D* hist_nb_jets_Ecut = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (kt) ; Number of jets; Counts", 60,0.,30.);

 /////end of without thetacut

 //theta cut histogram
    TH1D* hist_nb_jets_pTcut2 = new TH1D(Form("hist_nb_jets_pTcut%d_2",pTcut), "Number of jets (kt); Number of jets; Counts",60,0.,30.);
    TH1D* hist_nb_jets_Ecut2 = new TH1D(Form("hist_nb_jets_Ecut%d_2",Ecut), "Number of jets (kt); Number of jets; Counts", 60,0.,30.);

 //////end of theta cut histogram


Long64_t nbytes = 0, nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   b_jets_kt_pT->GetEntry(jentry);
   b_jets_kt_E->GetEntry(jentry);
   b_jets_kt_theta->GetEntry(jentry);
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   // if (Cut(ientry) < 0) continue;


   jetcountpT=0;
   jetcountE=0;

   jetcountpT2=0;
   jetcountE2=0;


   for(int i=0; i<(*jets_kt_pT).size(); i++)
   { //for 1 event


     if((*jets_kt_pT)[i]>=pTcut)
     {
       jetcountpT++;

       if (((*jets_kt_theta)[i]>theta_min) && ((*jets_kt_theta)[i]<theta_max))
       {
         jetcountpT2++;
       }

     }


     if((*jets_kt_E)[i]>=Ecut)
     {
       jetcountE++;

       if (((*jets_kt_theta)[i]>theta_min) && ((*jets_kt_theta)[i]<theta_max))
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
 //  if (jetthreepT2/jettwopT2>0.0001)
   ratiojetpT2[i] = jetthreepT2/jettwopT2;

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
 //if (jetthreeE2/jettwoE2>0.0001)
 ratiojetE2[i] = jetthreeE2/jettwoE2;

/*
   if (ratiojetpT2[i]!=0) hist_jetratio_pT2->Fill(pTcut, ratiojetpT2[i]);
   if (ratiojetpT[i]!=0) hist_jetratio_pT->Fill(pTcut, ratiojetpT[i]);

   if (ratiojetE2[i]!=0) hist_jetratio_E2->Fill(Ecut, ratiojetE2[i]);
   if (ratiojetE[i]!=0) hist_jetratio_E->Fill(Ecut, ratiojetE[i]);
*/


 hist_jetratio_pT2->Fill(pTcut, ratiojetpT2[i]);
 cout << "ratiojetpT2 : " << pTcut<< " " << ratiojetpT2[i] << endl;
 hist_jetratio_pT->Fill(pTcut, ratiojetpT[i]);

 hist_jetratio_E2->Fill(Ecut, ratiojetE2[i]);
     cout << "ratiojetE2 : " << Ecut<< " " << ratiojetE2[i] << endl;
 hist_jetratio_E->Fill(Ecut, ratiojetE[i]);



 } // end of Ecut and pTcut

/*
   TText *jetratiopT = new TText(0.15, 0.7, Form(">=3jets / >=2jets = %0.3f",ratiojetpT));
   jetratiopT->SetNDC(); // text position defined within [0,1]
   jetratiopT->SetTextSize(0.05);
   jetratiopT->SetTextColor(kBlue);


   TText *jetratioE = new TText(0.15, 0.7, Form(">=3jets / >=2jets = %0.3f",ratiojetE));
   jetratioE->SetNDC(); // text position defined within [0,1]
   jetratioE->SetTextSize(0.05);
   jetratioE->SetTextColor(kBlue);


   TText *jetratiopT2 = new TText(0.15, 0.65, Form(">=3jets / >=2jets = %0.3f",ratiojetpT2));
   jetratiopT2->SetNDC(); // text position defined within [0,1]
   jetratiopT2->SetTextSize(0.05);
   jetratiopT2->SetTextColor(kRed);


   TText *jetratioE2 = new TText(0.15, 0.65, Form(">=3jets / >=2jets = %0.3f",ratiojetE2));
   jetratioE2->SetNDC(); // text position defined within [0,1]
   jetratioE2->SetTextSize(0.05);
   jetratioE2->SetTextColor(kRed);
*/

   cout << "Loop finished" << endl;

   TCanvas *c1 = new TCanvas("c1", "kt jet ratio in function of pT cut", 800, 650);
   TCanvas *c2 = new TCanvas("c2", "kt jet ratio in function of E cut", 800, 650);

   TCanvas *c3 = new TCanvas("c3", "kt jet ratio in function of pT cut", 800, 650);
   TCanvas *c4 = new TCanvas("c4", "kt jet ratio in function of E cut", 800, 650);
   TCanvas *c5 = new TCanvas("c5", "kt jet ratio in function of pT and E cut", 800, 650);

   TGraph *gr1=new TGraph(size, pTcuts,ratiojetpT);
   TGraph *gr3=new TGraph(size, pTcuts,ratiojetpT2);
   TGraph *gr2=new TGraph(size, Ecuts, ratiojetE);
   TGraph *gr4=new TGraph(size, Ecuts, ratiojetE2) ;

   gr1->SetName(Form("graph_R%d_jetratio_pTcut_notheta",r));
   gr3->SetName(Form("graph_R%d_jetratio_pTcut_theta",r));
   gr2->SetName(Form("graph_R%d_jetratio_Ecut_notheta",r));
   gr4->SetName(Form("graph_R%d_jetratio_Ecut_theta",r));
 //  gr5->SetName(Form("graph_R%d_jetratio_pTandEcut_theta",r))

   TText *t_pTcut = new TText(0.6, 0.65, "pT cut");
   t_pTcut->SetNDC();
   t_pTcut->SetTextSize(0.05);
   t_pTcut->SetTextColor(kBlue);

   TText *t_Ecut = new TText(0.6, 0.6, "E cut");
   t_Ecut->SetNDC();
   t_Ecut->SetTextSize(0.05);
   t_Ecut->SetTextColor(kRed);


   c1->cd();
   //hist_jetratio_pT->SetMarkerStyle(21);
   //hist_jetratio_pT->SetMArkerColor(kBlue);
    hist_jetratio_pT->Draw();
//    hist_jetratio_pT2->SetFillColor(kRed);
//    hist_jetratio_pT2->Draw("SAME");

   gr1->SetMarkerStyle(21);
   gr1->Draw("SAME P");
   conesize->Draw();
 //  theta_range->Draw();
   without_theta->Draw();
   c1->Update();
   c1->SaveAs(Form("kt_graphs/jetratio/R%d_jetratio_pTcut_notheta.pdf",r));


   c2->cd();
    //hist_jetratio_E->SetFillColor(kBlue);
   hist_jetratio_E->Draw();
 //  hist_jetratio_E2->SetFillColor(kRed);
//    hist_jetratio_E2->Draw("SAME");
 gr2->SetMarkerStyle(21);
 gr2->Draw("SAME P");
   conesize->Draw();
 //  theta_range->Draw();
   without_theta->Draw();
   c2->Update();
   c2->SaveAs(Form("kt_graphs/jetratio/R%d_jetratio_Ecut_notheta.pdf",r));

   c3->cd();
   //hist_jetratio_pT2->SetFillColor(kRed);
   hist_jetratio_pT2->Draw();
   gr3->SetMarkerStyle(21);
   gr3->Draw("SAME P");
   conesize->Draw();
   theta_range->Draw();
 //  without_theta->Draw();
   c3->Update();
   c3->SaveAs(Form("kt_graphs/jetratio/R%d_jetratio_pTcut_theta.pdf",r));


   c4->cd();

   //hist_jetratio_E2->SetFillColor(kRed);
   hist_jetratio_E2->Draw();
   gr4->SetMarkerStyle(21);
   gr4->Draw("SAME P");
   conesize->Draw();
   theta_range->Draw();
   //without_theta->Draw();
   c4->Update();
   c4->SaveAs(Form("kt_graphs/jetratio/R%d_jetratio_Ecut_theta.pdf",r));


   c5->cd();
   hist_jetratio_pT2->Draw();
   hist_jetratio_E2->Draw("SAME");
   gr3->SetMarkerColor(kBlue);
   gr3->SetMarkerStyle(21);
   gr3->Draw("SAME P");
   gr4->SetMarkerColor(kRed);
   gr4->SetMarkerStyle(21);
   gr4->Draw("SAME P");
   t_pTcut->Draw();
   t_Ecut->Draw();
   theta_range->Draw();
   conesize->Draw();
   c5->Update();
   c5->SaveAs(Form("kt_graphs/jetratio/R%d_jetratio_E_and_pT_thetacut.pdf",r));

/*
//ONLY when creating for the first time
   tree->Fill();
   tree->Write();
*/

   //AFTER 2nd run
   b_ratiojetE->Fill();
   b_ratiojetE2->Fill();
   b_ratiojetpT->Fill();
   b_ratiojetpT2->Fill();


   hist_jetratio_pT2->Write();
   hist_jetratio_E->Write();
   hist_jetratio_E2->Write();
   hist_jetratio_pT->Write();
   gr1->Write();
   gr2->Write();
   gr3->Write();
   gr4->Write();




   jetratio->Write();
   jetratio->Close();



}

void R7jetratio::Loop_ee_genkt()
{
if (fChain == 0) return;

 Bool_t first = true;

// corresponds to event number
Long64_t nentries = fChain->GetEntriesFast();
double r_cone = 0.7;
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

Double_t jetthreepT=0;
Double_t jettwopT=0;
Double_t ratiojetpT[size];

Double_t jetthreeE=0.;
Double_t jettwoE=0;
Double_t ratiojetE[size];

//theta cut
Int_t jetcountpT2 =0;
Int_t jetcountE2=0;

Double_t jetthreepT2=0;
Double_t jettwopT2=0;
Double_t ratiojetpT2[size];

Double_t jetthreeE2=0.;
Double_t jettwoE2=0;
Double_t ratiojetE2[size];
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


////only wh




   TH2F* hist_jetratio_pT = new TH2F(Form("hist_jetratio_pTcut%d_withoutthetacut",pTcut), "Jet ratio in function of pT cut (ee_genkt); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E = new TH2F(Form("hist_jetratio_Ecut%d_withoutthetacut",Ecut), "Jet ratio in function of E cut (ee_genkt); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);

   TH2F* hist_jetratio_pT2 = new TH2F(Form("hist_jetratio_pTcut%d",pTcut), "Jet ratio in function of pT cut (ee_genkt); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E2 = new TH2F(Form("hist_jetratio_Ecut%d",Ecut), "Jet ratio in function of E cut (ee_genkt); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);



/*
//ONLY when creating root file for the first time.//
   TFile *jetratio = new TFile("ee_genkt_graphs/jetratio/jetratio.root","RECREATE");
   TTree *tree=new TTree("jetratio","Jet ratio");
   tree->Branch("Rvalues", Rvalues, "Rvalues[5]/D");
   tree->Branch("n", &size, "n/I");
   tree->Branch("pTcuts", pTcuts, "pTcuts[n]/D");
   tree->Branch("Ecuts", Ecuts, "Ecuts[n]/D");

   tree->Branch(Form("R%djetratio_pTcut_without_thetaCut",r), ratiojetpT, "ratiojetpT[14]/D");
   tree->Branch(Form("R%djetratio_Ecut_without_thetaCut",r), ratiojetE, "ratiojetE[14]/D");
   tree->Branch(Form("R%djetratio_pTcut",r), ratiojetpT2, "ratiojetpT2[14]/D");
   tree->Branch(Form("R%djetratio_Ecut",r), ratiojetE2, "ratiojetE2[14]/D");
///////////
*/


// size = 14
/////ONLY when adding more branches
   TFile *jetratio = new TFile("ee_genkt_graphs/jetratio/jetratio.root","update");
   TTree *tree= (TTree*) jetratio->Get("jetratio");
   TBranch *b_ratiojetpT = tree->Branch(Form("R%djetratio_pTcut_without_thetaCut",r), ratiojetpT, "ratiojetpT[14]/D");
   TBranch *b_ratiojetE = tree->Branch(Form("R%djetratio_Ecut_without_thetaCut",r), ratiojetE, "ratiojetE[14]/D");
   TBranch *b_ratiojetpT2 = tree->Branch(Form("R%djetratio_pTcut",r), ratiojetpT2, "ratiojetpT2[14]/D");
   TBranch *b_ratiojetE2 = tree->Branch(Form("R%djetratio_Ecut",r), ratiojetE2, "ratiojetE2[14]/D");
////////////////////////////////////


for(int i=0; i<size; i++)
{
  Ecut = Ecuts[i];
  pTcut = pTcuts[i];



 //without theta cut
    TH1D* hist_nb_jets_pTcut = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (ee_genkt) ; Number of jets; Counts",60,0.,30.);
    TH1D* hist_nb_jets_Ecut = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (ee_genkt) ; Number of jets; Counts", 60,0.,30.);

 /////end of without thetacut

 //theta cut histogram
    TH1D* hist_nb_jets_pTcut2 = new TH1D(Form("hist_nb_jets_pTcut%d_2",pTcut), "Number of jets (ee_genkt); Number of jets; Counts",60,0.,30.);
    TH1D* hist_nb_jets_Ecut2 = new TH1D(Form("hist_nb_jets_Ecut%d_2",Ecut), "Number of jets (ee_genkt); Number of jets; Counts", 60,0.,30.);

 //////end of theta cut histogram


Long64_t nbytes = 0, nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   b_jets_ee_genkt_pT->GetEntry(jentry);
   b_jets_ee_genkt_E->GetEntry(jentry);
   b_jets_ee_genkt_theta->GetEntry(jentry);
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   // if (Cut(ientry) < 0) continue;


   jetcountpT=0;
   jetcountE=0;

   jetcountpT2=0;
   jetcountE2=0;


   for(int i=0; i<(*jets_ee_genkt_pT).size(); i++)
   { //for 1 event


     if((*jets_ee_genkt_pT)[i]>=pTcut)
     {
       jetcountpT++;

       if (((*jets_ee_genkt_theta)[i]>theta_min) && ((*jets_ee_genkt_theta)[i]<theta_max))
       {
         jetcountpT2++;
       }

     }


     if((*jets_ee_genkt_E)[i]>=Ecut)
     {
       jetcountE++;

       if (((*jets_ee_genkt_theta)[i]>theta_min) && ((*jets_ee_genkt_theta)[i]<theta_max))
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
 //  if (jetthreepT2/jettwopT2>0.0001)
   ratiojetpT2[i] = jetthreepT2/jettwopT2;

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
 //if (jetthreeE2/jettwoE2>0.0001)
 ratiojetE2[i] = jetthreeE2/jettwoE2;

/*
   if (ratiojetpT2[i]!=0) hist_jetratio_pT2->Fill(pTcut, ratiojetpT2[i]);
   if (ratiojetpT[i]!=0) hist_jetratio_pT->Fill(pTcut, ratiojetpT[i]);

   if (ratiojetE2[i]!=0) hist_jetratio_E2->Fill(Ecut, ratiojetE2[i]);
   if (ratiojetE[i]!=0) hist_jetratio_E->Fill(Ecut, ratiojetE[i]);
*/


 hist_jetratio_pT2->Fill(pTcut, ratiojetpT2[i]);
 cout << "ratiojetpT2 : " << pTcut<< " " << ratiojetpT2[i] << endl;
 hist_jetratio_pT->Fill(pTcut, ratiojetpT[i]);

 hist_jetratio_E2->Fill(Ecut, ratiojetE2[i]);
     cout << "ratiojetE2 : " << Ecut<< " " << ratiojetE2[i] << endl;
 hist_jetratio_E->Fill(Ecut, ratiojetE[i]);



 } // end of Ecut and pTcut

/*
   TText *jetratiopT = new TText(0.15, 0.7, Form(">=3jets / >=2jets = %0.3f",ratiojetpT));
   jetratiopT->SetNDC(); // text position defined within [0,1]
   jetratiopT->SetTextSize(0.05);
   jetratiopT->SetTextColor(kBlue);


   TText *jetratioE = new TText(0.15, 0.7, Form(">=3jets / >=2jets = %0.3f",ratiojetE));
   jetratioE->SetNDC(); // text position defined within [0,1]
   jetratioE->SetTextSize(0.05);
   jetratioE->SetTextColor(kBlue);


   TText *jetratiopT2 = new TText(0.15, 0.65, Form(">=3jets / >=2jets = %0.3f",ratiojetpT2));
   jetratiopT2->SetNDC(); // text position defined within [0,1]
   jetratiopT2->SetTextSize(0.05);
   jetratiopT2->SetTextColor(kRed);


   TText *jetratioE2 = new TText(0.15, 0.65, Form(">=3jets / >=2jets = %0.3f",ratiojetE2));
   jetratioE2->SetNDC(); // text position defined within [0,1]
   jetratioE2->SetTextSize(0.05);
   jetratioE2->SetTextColor(kRed);
*/

   cout << "Loop finished" << endl;

   TCanvas *c1 = new TCanvas("c1", "ee_genkt jet ratio in function of pT cut", 800, 650);
   TCanvas *c2 = new TCanvas("c2", "ee_genkt jet ratio in function of E cut", 800, 650);

   TCanvas *c3 = new TCanvas("c3", "ee_genkt jet ratio in function of pT cut", 800, 650);
   TCanvas *c4 = new TCanvas("c4", "ee_genkt jet ratio in function of E cut", 800, 650);
   TCanvas *c5 = new TCanvas("c5", "ee_genkt jet ratio in function of pT and E cut", 800, 650);

   TGraph *gr1=new TGraph(size, pTcuts,ratiojetpT);
   TGraph *gr3=new TGraph(size, pTcuts,ratiojetpT2);
   TGraph *gr2=new TGraph(size, Ecuts, ratiojetE);
   TGraph *gr4=new TGraph(size, Ecuts, ratiojetE2) ;

   gr1->SetName(Form("graph_R%d_jetratio_pTcut_notheta",r));
   gr3->SetName(Form("graph_R%d_jetratio_pTcut_theta",r));
   gr2->SetName(Form("graph_R%d_jetratio_Ecut_notheta",r));
   gr4->SetName(Form("graph_R%d_jetratio_Ecut_theta",r));
 //  gr5->SetName(Form("graph_R%d_jetratio_pTandEcut_theta",r))

   TText *t_pTcut = new TText(0.6, 0.65, "pT cut");
   t_pTcut->SetNDC();
   t_pTcut->SetTextSize(0.05);
   t_pTcut->SetTextColor(kBlue);

   TText *t_Ecut = new TText(0.6, 0.6, "E cut");
   t_Ecut->SetNDC();
   t_Ecut->SetTextSize(0.05);
   t_Ecut->SetTextColor(kRed);


   c1->cd();
   //hist_jetratio_pT->SetMarkerStyle(21);
   //hist_jetratio_pT->SetMArkerColor(kBlue);
    hist_jetratio_pT->Draw();
//    hist_jetratio_pT2->SetFillColor(kRed);
//    hist_jetratio_pT2->Draw("SAME");

   gr1->SetMarkerStyle(21);
   gr1->Draw("SAME P");
   conesize->Draw();
 //  theta_range->Draw();
   without_theta->Draw();
   c1->Update();
   c1->SaveAs(Form("ee_genkt_graphs/jetratio/R%d_jetratio_pTcut_notheta.pdf",r));


   c2->cd();
    //hist_jetratio_E->SetFillColor(kBlue);
   hist_jetratio_E->Draw();
 //  hist_jetratio_E2->SetFillColor(kRed);
//    hist_jetratio_E2->Draw("SAME");
 gr2->SetMarkerStyle(21);
 gr2->Draw("SAME P");
   conesize->Draw();
 //  theta_range->Draw();
   without_theta->Draw();
   c2->Update();
   c2->SaveAs(Form("ee_genkt_graphs/jetratio/R%d_jetratio_Ecut_notheta.pdf",r));

   c3->cd();
   //hist_jetratio_pT2->SetFillColor(kRed);
   hist_jetratio_pT2->Draw();
   gr3->SetMarkerStyle(21);
   gr3->Draw("SAME P");
   conesize->Draw();
   theta_range->Draw();
 //  without_theta->Draw();
   c3->Update();
   c3->SaveAs(Form("ee_genkt_graphs/jetratio/R%d_jetratio_pTcut_theta.pdf",r));


   c4->cd();

   //hist_jetratio_E2->SetFillColor(kRed);
   hist_jetratio_E2->Draw();
   gr4->SetMarkerStyle(21);
   gr4->Draw("SAME P");
   conesize->Draw();
   theta_range->Draw();
   //without_theta->Draw();
   c4->Update();
   c4->SaveAs(Form("ee_genkt_graphs/jetratio/R%d_jetratio_Ecut_theta.pdf",r));


   c5->cd();
   hist_jetratio_pT2->Draw();
   hist_jetratio_E2->Draw("SAME");
   gr3->SetMarkerColor(kBlue);
   gr3->SetMarkerStyle(21);
   gr3->Draw("SAME P");
   gr4->SetMarkerColor(kRed);
   gr4->SetMarkerStyle(21);
   gr4->Draw("SAME P");
   t_pTcut->Draw();
   t_Ecut->Draw();
   theta_range->Draw();
   conesize->Draw();
   c5->Update();
   c5->SaveAs(Form("ee_genkt_graphs/jetratio/R%d_jetratio_E_and_pT_thetacut.pdf",r));

/*
//ONLY when creating for the first time
   tree->Fill();
   tree->Write();
*/

   //AFTER 2nd run
   b_ratiojetE->Fill();
   b_ratiojetE2->Fill();
   b_ratiojetpT->Fill();
   b_ratiojetpT2->Fill();


   hist_jetratio_pT2->Write();
   hist_jetratio_E->Write();
   hist_jetratio_E2->Write();
   hist_jetratio_pT->Write();
   gr1->Write();
   gr2->Write();
   gr3->Write();
   gr4->Write();




   jetratio->Write();
   jetratio->Close();



}

void R7jetratio::Loop_cambridge()
{
if (fChain == 0) return;

 Bool_t first = true;

// corresponds to event number
Long64_t nentries = fChain->GetEntriesFast();
double r_cone = 0.7;
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

Double_t jetthreepT=0;
Double_t jettwopT=0;
Double_t ratiojetpT[size];

Double_t jetthreeE=0.;
Double_t jettwoE=0;
Double_t ratiojetE[size];

//theta cut
Int_t jetcountpT2 =0;
Int_t jetcountE2=0;

Double_t jetthreepT2=0;
Double_t jettwopT2=0;
Double_t ratiojetpT2[size];

Double_t jetthreeE2=0.;
Double_t jettwoE2=0;
Double_t ratiojetE2[size];
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


////only wh




   TH2F* hist_jetratio_pT = new TH2F(Form("hist_jetratio_pTcut%d_withoutthetacut",pTcut), "Jet ratio in function of pT cut (cambridge); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E = new TH2F(Form("hist_jetratio_Ecut%d_withoutthetacut",Ecut), "Jet ratio in function of E cut (cambridge); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);

   TH2F* hist_jetratio_pT2 = new TH2F(Form("hist_jetratio_pTcut%d",pTcut), "Jet ratio in function of pT cut (cambridge); pT cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);
   TH2F* hist_jetratio_E2 = new TH2F(Form("hist_jetratio_Ecut%d",Ecut), "Jet ratio in function of E cut (cambridge); E cut(GeV); Jet ratio",60, 0.,30.,100,0.,1.);



/*
//ONLY when creating root file for the first time.//
   TFile *jetratio = new TFile("cambridge_graphs/jetratio/jetratio.root","RECREATE");
   TTree *tree=new TTree("jetratio","Jet ratio");
   tree->Branch("Rvalues", Rvalues, "Rvalues[5]/D");
   tree->Branch("n", &size, "n/I");
   tree->Branch("pTcuts", pTcuts, "pTcuts[n]/D");
   tree->Branch("Ecuts", Ecuts, "Ecuts[n]/D");

   tree->Branch(Form("R%djetratio_pTcut_without_thetaCut",r), ratiojetpT, "ratiojetpT[14]/D");
   tree->Branch(Form("R%djetratio_Ecut_without_thetaCut",r), ratiojetE, "ratiojetE[14]/D");
   tree->Branch(Form("R%djetratio_pTcut",r), ratiojetpT2, "ratiojetpT2[14]/D");
   tree->Branch(Form("R%djetratio_Ecut",r), ratiojetE2, "ratiojetE2[14]/D");
///////////
*/


// size = 14
/////ONLY when adding more branches
   TFile *jetratio = new TFile("cambridge_graphs/jetratio/jetratio.root","update");
   TTree *tree= (TTree*) jetratio->Get("jetratio");
   TBranch *b_ratiojetpT = tree->Branch(Form("R%djetratio_pTcut_without_thetaCut",r), ratiojetpT, "ratiojetpT[14]/D");
   TBranch *b_ratiojetE = tree->Branch(Form("R%djetratio_Ecut_without_thetaCut",r), ratiojetE, "ratiojetE[14]/D");
   TBranch *b_ratiojetpT2 = tree->Branch(Form("R%djetratio_pTcut",r), ratiojetpT2, "ratiojetpT2[14]/D");
   TBranch *b_ratiojetE2 = tree->Branch(Form("R%djetratio_Ecut",r), ratiojetE2, "ratiojetE2[14]/D");
////////////////////////////////////


for(int i=0; i<size; i++)
{
  Ecut = Ecuts[i];
  pTcut = pTcuts[i];



 //without theta cut
    TH1D* hist_nb_jets_pTcut = new TH1D(Form("hist_nb_jets_pTcut%d",pTcut), "Number of jets (cambridge) ; Number of jets; Counts",60,0.,30.);
    TH1D* hist_nb_jets_Ecut = new TH1D(Form("hist_nb_jets_Ecut%d",Ecut), "Number of jets (cambridge) ; Number of jets; Counts", 60,0.,30.);

 /////end of without thetacut

 //theta cut histogram
    TH1D* hist_nb_jets_pTcut2 = new TH1D(Form("hist_nb_jets_pTcut%d_2",pTcut), "Number of jets (cambridge); Number of jets; Counts",60,0.,30.);
    TH1D* hist_nb_jets_Ecut2 = new TH1D(Form("hist_nb_jets_Ecut%d_2",Ecut), "Number of jets (cambridge); Number of jets; Counts", 60,0.,30.);

 //////end of theta cut histogram


Long64_t nbytes = 0, nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
   Long64_t ientry = LoadTree(jentry);
   if (ientry < 0) break;
   b_jets_cambridge_pT->GetEntry(jentry);
   b_jets_cambridge_E->GetEntry(jentry);
   b_jets_cambridge_theta->GetEntry(jentry);
   nb = fChain->GetEntry(jentry);   nbytes += nb;
   // if (Cut(ientry) < 0) continue;


   jetcountpT=0;
   jetcountE=0;

   jetcountpT2=0;
   jetcountE2=0;


   for(int i=0; i<(*jets_cambridge_pT).size(); i++)
   { //for 1 event


     if((*jets_cambridge_pT)[i]>=pTcut)
     {
       jetcountpT++;

       if (((*jets_cambridge_theta)[i]>theta_min) && ((*jets_cambridge_theta)[i]<theta_max))
       {
         jetcountpT2++;
       }

     }


     if((*jets_cambridge_E)[i]>=Ecut)
     {
       jetcountE++;

       if (((*jets_cambridge_theta)[i]>theta_min) && ((*jets_cambridge_theta)[i]<theta_max))
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
 //  if (jetthreepT2/jettwopT2>0.0001)
   ratiojetpT2[i] = jetthreepT2/jettwopT2;

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
 //if (jetthreeE2/jettwoE2>0.0001)
 ratiojetE2[i] = jetthreeE2/jettwoE2;

/*
   if (ratiojetpT2[i]!=0) hist_jetratio_pT2->Fill(pTcut, ratiojetpT2[i]);
   if (ratiojetpT[i]!=0) hist_jetratio_pT->Fill(pTcut, ratiojetpT[i]);

   if (ratiojetE2[i]!=0) hist_jetratio_E2->Fill(Ecut, ratiojetE2[i]);
   if (ratiojetE[i]!=0) hist_jetratio_E->Fill(Ecut, ratiojetE[i]);
*/


 hist_jetratio_pT2->Fill(pTcut, ratiojetpT2[i]);
 cout << "ratiojetpT2 : " << pTcut<< " " << ratiojetpT2[i] << endl;
 hist_jetratio_pT->Fill(pTcut, ratiojetpT[i]);

 hist_jetratio_E2->Fill(Ecut, ratiojetE2[i]);
     cout << "ratiojetE2 : " << Ecut<< " " << ratiojetE2[i] << endl;
 hist_jetratio_E->Fill(Ecut, ratiojetE[i]);



 } // end of Ecut and pTcut

/*
   TText *jetratiopT = new TText(0.15, 0.7, Form(">=3jets / >=2jets = %0.3f",ratiojetpT));
   jetratiopT->SetNDC(); // text position defined within [0,1]
   jetratiopT->SetTextSize(0.05);
   jetratiopT->SetTextColor(kBlue);


   TText *jetratioE = new TText(0.15, 0.7, Form(">=3jets / >=2jets = %0.3f",ratiojetE));
   jetratioE->SetNDC(); // text position defined within [0,1]
   jetratioE->SetTextSize(0.05);
   jetratioE->SetTextColor(kBlue);


   TText *jetratiopT2 = new TText(0.15, 0.65, Form(">=3jets / >=2jets = %0.3f",ratiojetpT2));
   jetratiopT2->SetNDC(); // text position defined within [0,1]
   jetratiopT2->SetTextSize(0.05);
   jetratiopT2->SetTextColor(kRed);


   TText *jetratioE2 = new TText(0.15, 0.65, Form(">=3jets / >=2jets = %0.3f",ratiojetE2));
   jetratioE2->SetNDC(); // text position defined within [0,1]
   jetratioE2->SetTextSize(0.05);
   jetratioE2->SetTextColor(kRed);
*/

   cout << "Loop finished" << endl;

   TCanvas *c1 = new TCanvas("c1", "cambridge jet ratio in function of pT cut", 800, 650);
   TCanvas *c2 = new TCanvas("c2", "cambridge jet ratio in function of E cut", 800, 650);

   TCanvas *c3 = new TCanvas("c3", "cambridge jet ratio in function of pT cut", 800, 650);
   TCanvas *c4 = new TCanvas("c4", "cambridge jet ratio in function of E cut", 800, 650);
   TCanvas *c5 = new TCanvas("c5", "cambridge jet ratio in function of pT and E cut", 800, 650);

   TGraph *gr1=new TGraph(size, pTcuts,ratiojetpT);
   TGraph *gr3=new TGraph(size, pTcuts,ratiojetpT2);
   TGraph *gr2=new TGraph(size, Ecuts, ratiojetE);
   TGraph *gr4=new TGraph(size, Ecuts, ratiojetE2) ;

   gr1->SetName(Form("graph_R%d_jetratio_pTcut_notheta",r));
   gr3->SetName(Form("graph_R%d_jetratio_pTcut_theta",r));
   gr2->SetName(Form("graph_R%d_jetratio_Ecut_notheta",r));
   gr4->SetName(Form("graph_R%d_jetratio_Ecut_theta",r));
 //  gr5->SetName(Form("graph_R%d_jetratio_pTandEcut_theta",r))

   TText *t_pTcut = new TText(0.6, 0.65, "pT cut");
   t_pTcut->SetNDC();
   t_pTcut->SetTextSize(0.05);
   t_pTcut->SetTextColor(kBlue);

   TText *t_Ecut = new TText(0.6, 0.6, "E cut");
   t_Ecut->SetNDC();
   t_Ecut->SetTextSize(0.05);
   t_Ecut->SetTextColor(kRed);


   c1->cd();
   //hist_jetratio_pT->SetMarkerStyle(21);
   //hist_jetratio_pT->SetMArkerColor(kBlue);
    hist_jetratio_pT->Draw();
//    hist_jetratio_pT2->SetFillColor(kRed);
//    hist_jetratio_pT2->Draw("SAME");

   gr1->SetMarkerStyle(21);
   gr1->Draw("SAME P");
   conesize->Draw();
 //  theta_range->Draw();
   without_theta->Draw();
   c1->Update();
   c1->SaveAs(Form("cambridge_graphs/jetratio/R%d_jetratio_pTcut_notheta.pdf",r));


   c2->cd();
    //hist_jetratio_E->SetFillColor(kBlue);
   hist_jetratio_E->Draw();
 //  hist_jetratio_E2->SetFillColor(kRed);
//    hist_jetratio_E2->Draw("SAME");
 gr2->SetMarkerStyle(21);
 gr2->Draw("SAME P");
   conesize->Draw();
 //  theta_range->Draw();
   without_theta->Draw();
   c2->Update();
   c2->SaveAs(Form("cambridge_graphs/jetratio/R%d_jetratio_Ecut_notheta.pdf",r));

   c3->cd();
   //hist_jetratio_pT2->SetFillColor(kRed);
   hist_jetratio_pT2->Draw();
   gr3->SetMarkerStyle(21);
   gr3->Draw("SAME P");
   conesize->Draw();
   theta_range->Draw();
 //  without_theta->Draw();
   c3->Update();
   c3->SaveAs(Form("cambridge_graphs/jetratio/R%d_jetratio_pTcut_theta.pdf",r));


   c4->cd();

   //hist_jetratio_E2->SetFillColor(kRed);
   hist_jetratio_E2->Draw();
   gr4->SetMarkerStyle(21);
   gr4->Draw("SAME P");
   conesize->Draw();
   theta_range->Draw();
   //without_theta->Draw();
   c4->Update();
   c4->SaveAs(Form("cambridge_graphs/jetratio/R%d_jetratio_Ecut_theta.pdf",r));


   c5->cd();
   hist_jetratio_pT2->Draw();
   hist_jetratio_E2->Draw("SAME");
   gr3->SetMarkerColor(kBlue);
   gr3->SetMarkerStyle(21);
   gr3->Draw("SAME P");
   gr4->SetMarkerColor(kRed);
   gr4->SetMarkerStyle(21);
   gr4->Draw("SAME P");
   t_pTcut->Draw();
   t_Ecut->Draw();
   theta_range->Draw();
   conesize->Draw();
   c5->Update();
   c5->SaveAs(Form("cambridge_graphs/jetratio/R%d_jetratio_E_and_pT_thetacut.pdf",r));

/*
//ONLY when creating for the first time
   tree->Fill();
   tree->Write();
*/

   //AFTER 2nd run
   b_ratiojetE->Fill();
   b_ratiojetE2->Fill();
   b_ratiojetpT->Fill();
   b_ratiojetpT2->Fill();


   hist_jetratio_pT2->Write();
   hist_jetratio_E->Write();
   hist_jetratio_E2->Write();
   hist_jetratio_pT->Write();
   gr1->Write();
   gr2->Write();
   gr3->Write();
   gr4->Write();




   jetratio->Write();
   jetratio->Close();



}
