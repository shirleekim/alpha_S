//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon May  3 15:16:00 2021 by ROOT version 6.24/00
// from TTree events/events
// found on file: ISRoff_alphaS127_R5.root
//////////////////////////////////////////////////////////

#ifndef alphaS127_jetratio_h
#define alphaS127_jetratio_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"

class alphaS127_jetratio {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *MC_pT;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *MC_theta;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *MC_phi;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *MC_e;
   vector<bool>    *JET_btag;
   Int_t           EVT_nbtag;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *RP_px;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *RP_py;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *RP_pz;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *RP_e;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_kt_px;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_kt_py;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_kt_pz;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_kt_pT;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_kt_E;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_kt_theta;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_kt_phi;
   vector<vector<int> > *jetconstituents_kt;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_antikt_px;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_antikt_py;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_antikt_pz;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_antikt_pT;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_antikt_E;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_antikt_theta;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_antikt_phi;
   vector<vector<int> > *jetconstituents_antikt;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_cambridge_px;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_cambridge_py;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_cambridge_pz;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_cambridge_pT;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_cambridge_E;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_cambridge_theta;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_cambridge_phi;
   vector<vector<int> > *jetconstituents_cambridge;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_ee_genkt_px;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_ee_genkt_py;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_ee_genkt_pz;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_ee_genkt_pT;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_ee_genkt_E;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_ee_genkt_theta;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_ee_genkt_phi;
   vector<vector<int> > *jetconstituents_ee_genkt;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_valencia_px;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_valencia_py;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_valencia_pz;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_valencia_pT;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_valencia_E;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_valencia_theta;
   vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *jets_valencia_phi;
   vector<vector<int> > *jetconstituents_valencia;

   // List of branches
   TBranch        *b_MC_pT;   //!
   TBranch        *b_MC_theta;   //!
   TBranch        *b_MC_phi;   //!
   TBranch        *b_MC_e;   //!
   TBranch        *b_JET_btag;   //!
   TBranch        *b_EVT_nbtag;   //!
   TBranch        *b_RP_px;   //!
   TBranch        *b_RP_py;   //!
   TBranch        *b_RP_pz;   //!
   TBranch        *b_RP_e;   //!
   TBranch        *b_jets_kt_px;   //!
   TBranch        *b_jets_kt_py;   //!
   TBranch        *b_jets_kt_pz;   //!
   TBranch        *b_jets_kt_pT;   //!
   TBranch        *b_jets_kt_E;   //!
   TBranch        *b_jets_kt_theta;   //!
   TBranch        *b_jets_kt_phi;   //!
   TBranch        *b_jetconstituents_kt;   //!
   TBranch        *b_jets_antikt_px;   //!
   TBranch        *b_jets_antikt_py;   //!
   TBranch        *b_jets_antikt_pz;   //!
   TBranch        *b_jets_antikt_pT;   //!
   TBranch        *b_jets_antikt_E;   //!
   TBranch        *b_jets_antikt_theta;   //!
   TBranch        *b_jets_antikt_phi;   //!
   TBranch        *b_jetconstituents_antikt;   //!
   TBranch        *b_jets_cambridge_px;   //!
   TBranch        *b_jets_cambridge_py;   //!
   TBranch        *b_jets_cambridge_pz;   //!
   TBranch        *b_jets_cambridge_pT;   //!
   TBranch        *b_jets_cambridge_E;   //!
   TBranch        *b_jets_cambridge_theta;   //!
   TBranch        *b_jets_cambridge_phi;   //!
   TBranch        *b_jetconstituents_cambridge;   //!
   TBranch        *b_jets_ee_genkt_px;   //!
   TBranch        *b_jets_ee_genkt_py;   //!
   TBranch        *b_jets_ee_genkt_pz;   //!
   TBranch        *b_jets_ee_genkt_pT;   //!
   TBranch        *b_jets_ee_genkt_E;   //!
   TBranch        *b_jets_ee_genkt_theta;   //!
   TBranch        *b_jets_ee_genkt_phi;   //!
   TBranch        *b_jetconstituents_ee_genkt;   //!
   TBranch        *b_jets_valencia_px;   //!
   TBranch        *b_jets_valencia_py;   //!
   TBranch        *b_jets_valencia_pz;   //!
   TBranch        *b_jets_valencia_pT;   //!
   TBranch        *b_jets_valencia_E;   //!
   TBranch        *b_jets_valencia_theta;   //!
   TBranch        *b_jets_valencia_phi;   //!
   TBranch        *b_jetconstituents_valencia;   //!

   alphaS127_jetratio(TTree *tree=0);
   virtual ~alphaS127_jetratio();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef alphaS127_jetratio_cxx
alphaS127_jetratio::alphaS127_jetratio(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ISRoff_alphaS127_R5.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ISRoff_alphaS127_R5.root");
      }
      f->GetObject("events",tree);

   }
   Init(tree);
}

alphaS127_jetratio::~alphaS127_jetratio()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t alphaS127_jetratio::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t alphaS127_jetratio::LoadTree(Long64_t entry)
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

void alphaS127_jetratio::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   MC_pT = 0;
   MC_theta = 0;
   MC_phi = 0;
   MC_e = 0;
   JET_btag = 0;
   RP_px = 0;
   RP_py = 0;
   RP_pz = 0;
   RP_e = 0;
   jets_kt_px = 0;
   jets_kt_py = 0;
   jets_kt_pz = 0;
   jets_kt_pT = 0;
   jets_kt_E = 0;
   jets_kt_theta = 0;
   jets_kt_phi = 0;
   jetconstituents_kt = 0;
   jets_antikt_px = 0;
   jets_antikt_py = 0;
   jets_antikt_pz = 0;
   jets_antikt_pT = 0;
   jets_antikt_E = 0;
   jets_antikt_theta = 0;
   jets_antikt_phi = 0;
   jetconstituents_antikt = 0;
   jets_cambridge_px = 0;
   jets_cambridge_py = 0;
   jets_cambridge_pz = 0;
   jets_cambridge_pT = 0;
   jets_cambridge_E = 0;
   jets_cambridge_theta = 0;
   jets_cambridge_phi = 0;
   jetconstituents_cambridge = 0;
   jets_ee_genkt_px = 0;
   jets_ee_genkt_py = 0;
   jets_ee_genkt_pz = 0;
   jets_ee_genkt_pT = 0;
   jets_ee_genkt_E = 0;
   jets_ee_genkt_theta = 0;
   jets_ee_genkt_phi = 0;
   jetconstituents_ee_genkt = 0;
   jets_valencia_px = 0;
   jets_valencia_py = 0;
   jets_valencia_pz = 0;
   jets_valencia_pT = 0;
   jets_valencia_E = 0;
   jets_valencia_theta = 0;
   jets_valencia_phi = 0;
   jetconstituents_valencia = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("MC_pT", &MC_pT, &b_MC_pT);
   fChain->SetBranchAddress("MC_theta", &MC_theta, &b_MC_theta);
   fChain->SetBranchAddress("MC_phi", &MC_phi, &b_MC_phi);
   fChain->SetBranchAddress("MC_e", &MC_e, &b_MC_e);
   fChain->SetBranchAddress("JET_btag", &JET_btag, &b_JET_btag);
   fChain->SetBranchAddress("EVT_nbtag", &EVT_nbtag, &b_EVT_nbtag);
   fChain->SetBranchAddress("RP_px", &RP_px, &b_RP_px);
   fChain->SetBranchAddress("RP_py", &RP_py, &b_RP_py);
   fChain->SetBranchAddress("RP_pz", &RP_pz, &b_RP_pz);
   fChain->SetBranchAddress("RP_e", &RP_e, &b_RP_e);
   fChain->SetBranchAddress("jets_kt_px", &jets_kt_px, &b_jets_kt_px);
   fChain->SetBranchAddress("jets_kt_py", &jets_kt_py, &b_jets_kt_py);
   fChain->SetBranchAddress("jets_kt_pz", &jets_kt_pz, &b_jets_kt_pz);
   fChain->SetBranchAddress("jets_kt_pT", &jets_kt_pT, &b_jets_kt_pT);
   fChain->SetBranchAddress("jets_kt_E", &jets_kt_E, &b_jets_kt_E);
   fChain->SetBranchAddress("jets_kt_theta", &jets_kt_theta, &b_jets_kt_theta);
   fChain->SetBranchAddress("jets_kt_phi", &jets_kt_phi, &b_jets_kt_phi);
   fChain->SetBranchAddress("jetconstituents_kt", &jetconstituents_kt, &b_jetconstituents_kt);
   fChain->SetBranchAddress("jets_antikt_px", &jets_antikt_px, &b_jets_antikt_px);
   fChain->SetBranchAddress("jets_antikt_py", &jets_antikt_py, &b_jets_antikt_py);
   fChain->SetBranchAddress("jets_antikt_pz", &jets_antikt_pz, &b_jets_antikt_pz);
   fChain->SetBranchAddress("jets_antikt_pT", &jets_antikt_pT, &b_jets_antikt_pT);
   fChain->SetBranchAddress("jets_antikt_E", &jets_antikt_E, &b_jets_antikt_E);
   fChain->SetBranchAddress("jets_antikt_theta", &jets_antikt_theta, &b_jets_antikt_theta);
   fChain->SetBranchAddress("jets_antikt_phi", &jets_antikt_phi, &b_jets_antikt_phi);
   fChain->SetBranchAddress("jetconstituents_antikt", &jetconstituents_antikt, &b_jetconstituents_antikt);
   fChain->SetBranchAddress("jets_cambridge_px", &jets_cambridge_px, &b_jets_cambridge_px);
   fChain->SetBranchAddress("jets_cambridge_py", &jets_cambridge_py, &b_jets_cambridge_py);
   fChain->SetBranchAddress("jets_cambridge_pz", &jets_cambridge_pz, &b_jets_cambridge_pz);
   fChain->SetBranchAddress("jets_cambridge_pT", &jets_cambridge_pT, &b_jets_cambridge_pT);
   fChain->SetBranchAddress("jets_cambridge_E", &jets_cambridge_E, &b_jets_cambridge_E);
   fChain->SetBranchAddress("jets_cambridge_theta", &jets_cambridge_theta, &b_jets_cambridge_theta);
   fChain->SetBranchAddress("jets_cambridge_phi", &jets_cambridge_phi, &b_jets_cambridge_phi);
   fChain->SetBranchAddress("jetconstituents_cambridge", &jetconstituents_cambridge, &b_jetconstituents_cambridge);
   fChain->SetBranchAddress("jets_ee_genkt_px", &jets_ee_genkt_px, &b_jets_ee_genkt_px);
   fChain->SetBranchAddress("jets_ee_genkt_py", &jets_ee_genkt_py, &b_jets_ee_genkt_py);
   fChain->SetBranchAddress("jets_ee_genkt_pz", &jets_ee_genkt_pz, &b_jets_ee_genkt_pz);
   fChain->SetBranchAddress("jets_ee_genkt_pT", &jets_ee_genkt_pT, &b_jets_ee_genkt_pT);
   fChain->SetBranchAddress("jets_ee_genkt_E", &jets_ee_genkt_E, &b_jets_ee_genkt_E);
   fChain->SetBranchAddress("jets_ee_genkt_theta", &jets_ee_genkt_theta, &b_jets_ee_genkt_theta);
   fChain->SetBranchAddress("jets_ee_genkt_phi", &jets_ee_genkt_phi, &b_jets_ee_genkt_phi);
   fChain->SetBranchAddress("jetconstituents_ee_genkt", &jetconstituents_ee_genkt, &b_jetconstituents_ee_genkt);
   fChain->SetBranchAddress("jets_valencia_px", &jets_valencia_px, &b_jets_valencia_px);
   fChain->SetBranchAddress("jets_valencia_py", &jets_valencia_py, &b_jets_valencia_py);
   fChain->SetBranchAddress("jets_valencia_pz", &jets_valencia_pz, &b_jets_valencia_pz);
   fChain->SetBranchAddress("jets_valencia_pT", &jets_valencia_pT, &b_jets_valencia_pT);
   fChain->SetBranchAddress("jets_valencia_E", &jets_valencia_E, &b_jets_valencia_E);
   fChain->SetBranchAddress("jets_valencia_theta", &jets_valencia_theta, &b_jets_valencia_theta);
   fChain->SetBranchAddress("jets_valencia_phi", &jets_valencia_phi, &b_jets_valencia_phi);
   fChain->SetBranchAddress("jetconstituents_valencia", &jetconstituents_valencia, &b_jetconstituents_valencia);
   Notify();
}

Bool_t alphaS127_jetratio::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void alphaS127_jetratio::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t alphaS127_jetratio::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef alphaS127_jetratio_cxx
