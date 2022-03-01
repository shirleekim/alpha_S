//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr 15 01:43:51 2021 by ROOT version 6.22/08
// from TTree jetratio/Jet ratio
// found on file: jetratio.root
//////////////////////////////////////////////////////////

#ifndef R_jetratio_h
#define R_jetratio_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class R_jetratio {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        Rvalues[5];
   Int_t           n;
   Double_t        pTcuts[14];   //[n]
   Double_t        Ecuts[14];   //[n]
   Double_t        R5jetratio_pTcut_without_thetaCut[14];   //[n]
   Double_t        R5jetratio_Ecut_without_thetaCut[14];   //[n]
   Double_t        R5jetratio_pTcut[14];   //[n]
   Double_t        R5jetratio_Ecut[14];   //[n]
   Double_t        R4jetratio_pTcut_without_thetaCut[14];   //[n]
   Double_t        R4jetratio_Ecut_without_thetaCut[14];   //[n]
   Double_t        R4jetratio_pTcut[14];   //[n]
   Double_t        R4jetratio_Ecut[14];   //[n]
   Double_t        R6jetratio_pTcut_without_thetaCut[14];   //[n]
   Double_t        R6jetratio_Ecut_without_thetaCut[14];   //[n]
   Double_t        R6jetratio_pTcut[14];   //[n]
   Double_t        R6jetratio_Ecut[14];   //[n]
   Double_t        R7jetratio_pTcut_without_thetaCut[14];   //[n]
   Double_t        R7jetratio_Ecut_without_thetaCut[14];   //[n]
   Double_t        R7jetratio_pTcut[14];   //[n]
   Double_t        R7jetratio_Ecut[14];   //[n]
   Double_t        R3jetratio_pTcut_without_thetaCut[14];   //[n]
   Double_t        R3jetratio_Ecut_without_thetaCut[14];   //[n]
   Double_t        R3jetratio_pTcut[14];   //[n]
   Double_t        R3jetratio_Ecut[14];   //[n]

   // List of branches
   TBranch        *b_Rvalues;   //!
   TBranch        *b_n;   //!
   TBranch        *b_pTcuts;   //!
   TBranch        *b_Ecuts;   //!
   TBranch        *b_R5jetratio_pTcut_without_thetaCut;   //!
   TBranch        *b_R5jetratio_Ecut_without_thetaCut;   //!
   TBranch        *b_R5jetratio_pTcut;   //!
   TBranch        *b_R5jetratio_Ecut;   //!
   TBranch        *b_R4jetratio_pTcut_without_thetaCut;   //!
   TBranch        *b_R4jetratio_Ecut_without_thetaCut;   //!
   TBranch        *b_R4jetratio_pTcut;   //!
   TBranch        *b_R4jetratio_Ecut;   //!
   TBranch        *b_R6jetratio_pTcut_without_thetaCut;   //!
   TBranch        *b_R6jetratio_Ecut_without_thetaCut;   //!
   TBranch        *b_R6jetratio_pTcut;   //!
   TBranch        *b_R6jetratio_Ecut;   //!
   TBranch        *b_R7jetratio_pTcut_without_thetaCut;   //!
   TBranch        *b_R7jetratio_Ecut_without_thetaCut;   //!
   TBranch        *b_R7jetratio_pTcut;   //!
   TBranch        *b_R7jetratio_Ecut;   //!  //!
   TBranch        *b_R3jetratio_pTcut_without_thetaCut;   //!
   TBranch        *b_R3jetratio_Ecut_without_thetaCut;   //!
   TBranch        *b_R3jetratio_pTcut;   //!
   TBranch        *b_R3jetratio_Ecut;   //!

   R_jetratio(TTree *tree=0);
   virtual ~R_jetratio();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef R_jetratio_cxx
R_jetratio::R_jetratio(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("jetratio.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("jetratio.root");
      }
      f->GetObject("jetratio",tree);

   }
   Init(tree);
}

R_jetratio::~R_jetratio()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t R_jetratio::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t R_jetratio::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void R_jetratio::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Rvalues", Rvalues, &b_Rvalues);
   fChain->SetBranchAddress("n", &n, &b_n);
   fChain->SetBranchAddress("pTcuts", pTcuts, &b_pTcuts);
   fChain->SetBranchAddress("Ecuts", Ecuts, &b_Ecuts);
   fChain->SetBranchAddress("R5jetratio_pTcut_without_thetaCut", R5jetratio_pTcut_without_thetaCut, &b_R5jetratio_pTcut_without_thetaCut);
   fChain->SetBranchAddress("R5jetratio_Ecut_without_thetaCut", R5jetratio_Ecut_without_thetaCut, &b_R5jetratio_Ecut_without_thetaCut);
   fChain->SetBranchAddress("R5jetratio_pTcut", R5jetratio_pTcut, &b_R5jetratio_pTcut);
   fChain->SetBranchAddress("R5jetratio_Ecut", R5jetratio_Ecut, &b_R5jetratio_Ecut);
   fChain->SetBranchAddress("R4jetratio_pTcut_without_thetaCut", R4jetratio_pTcut_without_thetaCut, &b_R4jetratio_pTcut_without_thetaCut);
   fChain->SetBranchAddress("R4jetratio_Ecut_without_thetaCut", R4jetratio_Ecut_without_thetaCut, &b_R4jetratio_Ecut_without_thetaCut);
   fChain->SetBranchAddress("R4jetratio_pTcut", R4jetratio_pTcut, &b_R4jetratio_pTcut);
   fChain->SetBranchAddress("R4jetratio_Ecut", R4jetratio_Ecut, &b_R4jetratio_Ecut);
   fChain->SetBranchAddress("R6jetratio_pTcut_without_thetaCut", R6jetratio_pTcut_without_thetaCut, &b_R6jetratio_pTcut_without_thetaCut);
   fChain->SetBranchAddress("R6jetratio_Ecut_without_thetaCut", R6jetratio_Ecut_without_thetaCut, &b_R6jetratio_Ecut_without_thetaCut);
   fChain->SetBranchAddress("R6jetratio_pTcut", R6jetratio_pTcut, &b_R6jetratio_pTcut);
   fChain->SetBranchAddress("R6jetratio_Ecut", R6jetratio_Ecut, &b_R6jetratio_Ecut);
   fChain->SetBranchAddress("R7jetratio_pTcut_without_thetaCut", R7jetratio_pTcut_without_thetaCut, &b_R7jetratio_pTcut_without_thetaCut);
   fChain->SetBranchAddress("R7jetratio_Ecut_without_thetaCut", R7jetratio_Ecut_without_thetaCut, &b_R7jetratio_Ecut_without_thetaCut);
   fChain->SetBranchAddress("R7jetratio_pTcut", R7jetratio_pTcut, &b_R7jetratio_pTcut);
   fChain->SetBranchAddress("R7jetratio_Ecut", R7jetratio_Ecut, &b_R7jetratio_Ecut);
   fChain->SetBranchAddress("R3jetratio_pTcut_without_thetaCut", R3jetratio_pTcut_without_thetaCut, &b_R3jetratio_pTcut_without_thetaCut);
   fChain->SetBranchAddress("R3jetratio_Ecut_without_thetaCut", R3jetratio_Ecut_without_thetaCut, &b_R3jetratio_Ecut_without_thetaCut);
   fChain->SetBranchAddress("R3jetratio_pTcut", R3jetratio_pTcut, &b_R3jetratio_pTcut);
   fChain->SetBranchAddress("R3jetratio_Ecut", R3jetratio_Ecut, &b_R3jetratio_Ecut);
   Notify();
}

Bool_t R_jetratio::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void R_jetratio::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t R_jetratio::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef R_jetratio_cxx
