//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Apr 26 19:32:34 2021 by ROOT version 6.22/06
// from TTree jetratio/3+/2+ Jet Ratio with theta cut
// found on file: jetratio_all.root
//////////////////////////////////////////////////////////

#ifndef jetratio_all_graphs_h
#define jetratio_all_graphs_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class jetratio_all_graphs {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           Jet_algorithm;
   Double_t        alpha_S;
   Double_t        R;
   Int_t           pT_cut;
   Int_t           E_cut;
   Double_t        Jet_ratio;

   // List of branches
   TBranch        *b_Jet_algorithm;   //!
   TBranch        *b_alpha_S;   //!
   TBranch        *b_R;   //!
   TBranch        *b_pT_cut;   //!
   TBranch        *b_E_cut;   //!
   TBranch        *b_jet_ratio;   //!

   jetratio_all_graphs(TTree *tree=0);
   virtual ~jetratio_all_graphs();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop_algo_alphaS();
   virtual void     Loop_alphaS_pT();
   virtual void     Loop_alphaS_E();
   virtual void     Loop_alphaS_R();
   virtual void     Loop_alphaS_R_double();
   virtual void     Loop_alphaS_Ecut_double();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef jetratio_all_graphs_cxx
jetratio_all_graphs::jetratio_all_graphs(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("jetratio_all.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("jetratio_all.root");
      }
      f->GetObject("jetratio",tree);

   }
   Init(tree);
}

jetratio_all_graphs::~jetratio_all_graphs()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t jetratio_all_graphs::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t jetratio_all_graphs::LoadTree(Long64_t entry)
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

void jetratio_all_graphs::Init(TTree *tree)
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

   fChain->SetBranchAddress("Jet_algorithm", &Jet_algorithm, &b_Jet_algorithm);
   fChain->SetBranchAddress("alpha_S", &alpha_S, &b_alpha_S);
   fChain->SetBranchAddress("R", &R, &b_R);
   fChain->SetBranchAddress("pT_cut", &pT_cut, &b_pT_cut);
   fChain->SetBranchAddress("E_cut", &E_cut, &b_E_cut);
   fChain->SetBranchAddress("Jet_ratio", &Jet_ratio, &b_jet_ratio);
   Notify();
}

Bool_t jetratio_all_graphs::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void jetratio_all_graphs::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t jetratio_all_graphs::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef jetratio_all_graphs_cxx
