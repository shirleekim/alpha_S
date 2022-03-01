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
  Int_t thetacut; // 0: no theta cut, 1: theta cut applied
  Double_t error; // jetratio statistical uncertainty;

  Double_t dump;


  TFile *f = new TFile("jetratio_all.root", "RECREATE");
  TTree *tree = new TTree("jetratio", "3+/2+ Jet Ratio with theta cut");

  tree->Branch("Jet_algorithm", &algorithm, "Jet_algorithm/I");
  tree->Branch("alpha_S", &alpha_S, "alpha_S/D");
  tree->Branch("R", &R, "R/D");
  tree->Branch("pT_cut", &pT_cut, "pT_cut/I");
  tree->Branch("E_cut", &E_cut, "E_cut/I");
  tree->Branch("Jet_ratio", &jet_ratio, "jet_ratio/D");
  tree->Branch("theta_cut", &thetacut, "theta_cut/I");
  tree->Branch("error", &error, "error/D");


  string line;


  int alphaS=0;
  string algo;
  string str;

  ifstream read1;

  algo = "antikt";

  for(int alphaS = 110; alphaS<=130; alphaS++)
  {

    read1.open(Form("alphaS%d_R5jetratio_%s.txt",alphaS,algo.c_str()));
    getline(read1,line); // ignore first line *line indicating column names*

    for(int n=0; n<28; n++)
    {
      read1 >> algorithm >> alpha_S >> R >> pT_cut >> E_cut >> jet_ratio >> thetacut >> error;
    //  cout << algorithm << " " << alpha_S << " " << R <<" "<< pT_cut << " " << E_cut << " " << jet_ratio << endl;
      tree -> Fill();
    }
    cout << alphaS << " operation done" << endl;
    read1.close();
  }

///////below here will contain different alphaS and R values

  read1.open(Form("alphaS1365_R5jetratio_%s.txt",algo.c_str()));
  getline(read1,line); // ignore first line *line indicating column names*

  for(int n=0; n<140; n++)
  {
    read1 >> algorithm >> alpha_S >> R >> pT_cut >> E_cut >> jet_ratio >> thetacut >> error ;
  //  cout << algorithm << " " << alpha_S << " " << R <<" "<< pT_cut << " " << E_cut << " " << jet_ratio << endl;

    tree -> Fill();
  }
  cout << 1365 << " operation done" << endl;
  read1.close();





  tree->Write();
  f->Close();

}
