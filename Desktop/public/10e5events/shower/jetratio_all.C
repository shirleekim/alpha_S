#include <iostream>

using namespace std;

// macro that collects all the jet ratio values (theta cut applied)

void jetratio_all()
{
  Int_t algorithm;
  Double_t alpha_S;
  Double_t R;
  Int_t pT_cut;
  Int_t E_cut;
  Double_t jet_ratio;

  Double_t dump;


  TFile *f = new TFile("jetratio_all.root", "RECREATE");
  TTree *tree = new TTree("jetratio", "3+/2+ Jet Ratio with theta cut");

  tree->Branch("Jet_algorithm", &algorithm, "Jet_algorithm/I");
  tree->Branch("alpha_S", &alpha_S, "alpha_S/D");
  tree->Branch("R", &R, "R/D");
  tree->Branch("pT_cut", &pT_cut, "pT_cut/I");
  tree->Branch("E_cut", &E_cut, "E_cut/I");
  tree->Branch("Jet_ratio", &jet_ratio, "jet_ratio/D");

  string line;


  int alphaS=0;
  string algo;
  string str;

  ifstream read1, read2;


  for (int i=0; i<5; i++)
  {

      if (i==0) algo = "antikt";
      if (i==1) algo = "ee_genkt";
      if (i==2) algo = "kt";
      if (i==3) algo = "valencia";
      if (i==4) algo = "cambridge";


    read1.open(Form("../alphaS_default/jetratio_%s.txt",algo.c_str()));
    getline(read1,line); // ignore first line *line indicating column names*

    for(int n=0; n<140; n++)
    {
      read1 >> algorithm >> dump >> R >> pT_cut >> E_cut >> jet_ratio ;
    //  cout << algorithm << " " << alpha_S << " " << R <<" "<< pT_cut << " " << E_cut << " " << jet_ratio << endl;
      alpha_S = 0.1365;
      tree -> Fill();
    }
    cout << algo.c_str() << " operation done" << endl;
    read1.close();

  }

  for (int i=0; i<5; i++)
  {
    if (i==0) algo = "antikt";
    if (i==1) algo = "ee_genkt";
    if (i==2) algo = "kt";
    if (i==3) algo = "valencia";
    if (i==4) algo = "cambridge";


    for (int j=0; j<4; j++)
    {
      {
        if (j==0) alphaS = 11;
        if (j==1) alphaS = 115;
        if (j==2) alphaS = 12;
        if (j==3) alphaS = 125;
      }

      read2.open(Form("alphaS%d/jetratio_%s.txt",alphaS,algo.c_str()));
      getline(read2,line); // ignore first line *line indicating column names*

      for(int n=0; n<140; n++)
      {
        read2 >> algorithm >> alpha_S >> R >> pT_cut >> E_cut >> jet_ratio ;
        tree -> Fill();
      }
      cout << algo.c_str() << " operation done" << endl;
      read2.close();

    }

  }

  tree->Write();
  f->Close();

}
