#define jetratio_all_graphs_cxx
#include "jetratio_all_graphs.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

//macro that takes jetratio_all.root to make some graphs

void jetratio_all_graphs::Loop_algo_alphaS()
{
     if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   Int_t pT_cut_value = 10;
   Int_t E_cut_value = 10;
   Double_t R_value = 0.5;
   Double_t alpha_S_value = 0.1365;
    //algorithm 0: antikt, 1:ee_genkt, 2:kt, 3:valencia, 4:cambridge
   Int_t Jet_algorithm_value = 0;
   Double_t Jet_ratio_value ;

   Int_t R_value_int = R_value*10;

  // TFile *f = new TFile("jetratio_all_histogram.root", "RECREATE");
  // TTree *tree = new TTree("jetratio", "3+/2+ Jet Ratio histogram with theta cut");

  // TH2F* hist_algo_alphaS = new TH2F(Form("hist_algo_alphaS_pTcut%d",pT_cut_value), "Jet ratio (algorithm,alphaS) at pT cut;",angle_nbin, 0.,50.,100,0.,3.2);

  TGraph2D * gr_algo_alphaS_pT = new TGraph2D(3);
  TGraph2D * gr_algo_alphaS_E = new TGraph2D(3);

int point1 =0;
int point2 = 0;

   for (Long64_t jentry=0; jentry<nentries;jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      fChain->GetEntry(jentry);
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;


         // Jet ratio as function of (ALGORITHM, ALPHAS)

         if ((pT_cut==pT_cut_value) && (R==R_value) &&(E_cut ==0))
         {
           gr_algo_alphaS_pT->SetPoint(point1, Jet_algorithm, alpha_S, Jet_ratio);
           point1++;
        //   cout << Jet_algorithm << " " << alpha_S << " " << Jet_ratio << endl;
         }


         if ((E_cut==E_cut_value) && (R==R_value)&&(pT_cut ==0))
         {
           gr_algo_alphaS_E->SetPoint(point2, Jet_algorithm, alpha_S, Jet_ratio);
           point2++;
           cout << Jet_algorithm << " " << alpha_S << " " << Jet_ratio << endl;
         }


    }

      TCanvas *c1 = new TCanvas("c1", "c1", 800, 650);
      TCanvas *c2 = new TCanvas("c2", "c2", 800, 650);


      c1->cd();
      gr_algo_alphaS_pT->SetTitle(Form("Jet ratio at pT cut %d, R=%.1f; Jet Algorithm;  #alpha_{S}",pT_cut_value, R_value));
      gr_algo_alphaS_pT->GetXaxis()->SetTitle("Jet Algorithm");
      gr_algo_alphaS_pT->GetYaxis()->SetTitle(" #alpha_{S}");
      gr_algo_alphaS_pT->GetHistogram()->GetXaxis()->SetTitleOffset(2.5);
      gr_algo_alphaS_pT->GetHistogram()->GetYaxis()->SetTitleSize(0.025);
      gr_algo_alphaS_pT->GetHistogram()->GetYaxis()->SetTitleOffset(3);
      gr_algo_alphaS_pT->Draw("surf1");
      c1->Update();
      c1->SaveAs(Form("jetratio_algo_alphaS_pTcut%d_R%d.pdf",pT_cut_value, R_value_int));

      c2->cd();
      gr_algo_alphaS_E->SetTitle(Form("Jet ratio at E cut %d, R=%.1f; Jet Algorithm;  #alpha_{S}",E_cut_value, R_value));
      gr_algo_alphaS_E->GetXaxis()->SetTitle("Jet Algorithm");
      gr_algo_alphaS_E->GetYaxis()->SetTitle(" #alpha_{S}");
      gr_algo_alphaS_E->GetHistogram()->GetXaxis()->SetTitleOffset(2.5);
      gr_algo_alphaS_pT->GetHistogram()->GetYaxis()->SetTitleSize(0.025);
      gr_algo_alphaS_E->GetHistogram()->GetYaxis()->SetTitleOffset(3);
      gr_algo_alphaS_E->Draw("surf1");
      c2->Update();
      c2->SaveAs(Form("jetratio_algo_alphaS_Ecut%d_R%d.pdf",E_cut_value, R_value_int));

/*
      gr_algo_alphaS_pT->Write();
      gr_algo_alphaS_E->Write();

    f->Close();
*/

  }

  void jetratio_all_graphs::Loop_alphaS_pT()
  {
       if (fChain == 0) return;

     Long64_t nentries = fChain->GetEntriesFast();

     Long64_t nbytes = 0, nb = 0;

     Int_t pT_cut_value = 0;
     Int_t E_cut_value = 0;
     Double_t R_value = 0.5;
     Double_t alpha_S_value = 0;
      //algorithm 0: antikt, 1:ee_genkt, 2:kt, 3:valencia, 4:cambridge
     Int_t Jet_algorithm_value = 0;
     Double_t Jet_ratio_value ;

     Int_t R_value_int = R_value*10;

     Double_t R_array[5] = {0.3, 0.4, 0.5, 0.6, 0.7};
     Double_t alpha_S_array[5] = {0.11, 0.115, 0.12, 0.125, 0.1365};
     Double_t Jet_algorithm_array[5] = {0,1,2,3,4};

     TFile *f = new TFile("jetratio_all_histogram.root", "UPDATE");
    // TTree *tree = new TTree("jetratio", "3+/2+ Jet Ratio histogram with theta cut");

    // TH2F* hist_algo_alphaS = new TH2F(Form("hist_algo_alphaS_pTcut%d",pT_cut_value), "Jet ratio (algorithm,alphaS) at pT cut;",angle_nbin, 0.,50.,100,0.,3.2);

for (int algo=0; algo<5; algo++)
{

    TGraph2D * gr_alphaS_pT = new TGraph2D(3);
    //TGraph2D * gr_algo_alphaS_E = new TGraph2D(3);

  int point1 =0;
  int point2 = 0;

     for (Long64_t jentry=0; jentry<nentries;jentry++)
     {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        fChain->GetEntry(jentry);
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;


           // Jet ratio as function of (ALGORITHM, ALPHAS)

           if ((Jet_algorithm==algo) && (R==R_value) && (E_cut==0))
           {
             gr_alphaS_pT->SetPoint(point1, alpha_S, pT_cut, Jet_ratio);
             point1++;
          //   cout << Jet_algorithm << " " << alpha_S << " " << Jet_ratio << endl;
           }





      }

        TCanvas *c1 = new TCanvas("c1", "c1", 800, 650);


        c1->cd();
        gr_alphaS_pT->SetTitle(Form("Jet ratio with algorithm %d, R=%.1f; #alpha_{S}; pT cut",algo, R_value));
        gr_alphaS_pT->GetXaxis()->SetTitle(" #alpha_{S}");
        gr_alphaS_pT->GetYaxis()->SetTitle("pT cut");
        gr_alphaS_pT->GetHistogram()->GetXaxis()->SetTitleOffset(1.6);
        gr_alphaS_pT->GetHistogram()->GetXaxis()->SetTitleSize(0.025);
        gr_alphaS_pT->GetHistogram()->GetYaxis()->SetTitleOffset(1.6);
        c1 ->SetTheta(-21.);
        c1 ->SetPhi(21.);
        c1->Update();
        gr_alphaS_pT->Draw("surf1");
        c1->SaveAs(Form("jetratio_alphaS_pT_algo%d_R%d.pdf",algo, R_value_int));

        gr_alphaS_pT->Write();


}
        f->Close();


    }


    void jetratio_all_graphs::Loop_alphaS_E()
    {
         if (fChain == 0) return;

       Long64_t nentries = fChain->GetEntriesFast();

       Long64_t nbytes = 0, nb = 0;

       Int_t pT_cut_value = 0;
       Int_t E_cut_value = 0;
       Double_t R_value = 0.5;
       Double_t alpha_S_value = 0;
        //algorithm 0: antikt, 1:ee_genkt, 2:kt, 3:valencia, 4:cambridge
       Int_t Jet_algorithm_value = 0;
       Double_t Jet_ratio_value ;

       Int_t R_value_int = R_value*10;

       Double_t R_array[5] = {0.3, 0.4, 0.5, 0.6, 0.7};
       Double_t alpha_S_array[5] = {0.11, 0.115, 0.12, 0.125, 0.1365};
       Double_t Jet_algorithm_array[5] = {0,1,2,3,4};

       string algorithm;

       TFile *f = new TFile("jetratio_all_histogram.root", "UPDATE");
      // TTree *tree = new TTree("jetratio", "3+/2+ Jet Ratio histogram with theta cut");

      // TH2F* hist_algo_alphaS = new TH2F(Form("hist_algo_alphaS_pTcut%d",pT_cut_value), "Jet ratio (algorithm,alphaS) at pT cut;",angle_nbin, 0.,50.,100,0.,3.2);

  for (int algo=0; algo<5; algo++)
  {

      TGraph2D * gr_alphaS_E = new TGraph2D(3);
      //TGraph2D * gr_algo_alphaS_E = new TGraph2D(3);

    int point1 =0;
    int point2 = 0;

       for (Long64_t jentry=0; jentry<nentries;jentry++)
       {
          Long64_t ientry = LoadTree(jentry);
          if (ientry < 0) break;
          fChain->GetEntry(jentry);
          nb = fChain->GetEntry(jentry);   nbytes += nb;
          // if (Cut(ientry) < 0) continue;


             // Jet ratio as function of (ALGORITHM, ALPHAS)

             if ((Jet_algorithm==algo) && (R==R_value) && (pT_cut ==0))
             {
               gr_alphaS_E->SetPoint(point1, alpha_S, E_cut, Jet_ratio);
               point1++;
            //   cout << Jet_algorithm << " " << alpha_S << " " << Jet_ratio << endl;
             }





        }

          TCanvas *c1 = new TCanvas("c1", "c1", 800, 650);



                      if (algo==0) algorithm = "anti-k_{T}";
                      if (algo==1) algorithm = "ee_genk_{T}";
                      if (algo==2) algorithm = "k_{T}";
                      if (algo==3) algorithm = "Valencia";
                      if (algo==4) algorithm = "Cambridge";


          c1->cd();
          gr_alphaS_E->SetTitle(Form("R_{3/2} with %s algorithm, R=%.1f;  #alpha_{S}; E cut (GeV); R_{3/2}",algorithm.c_str(), R_value));
          gr_alphaS_E->GetHistogram()->GetXaxis()->SetTitleOffset(1.7);
          gr_alphaS_E->GetHistogram()->GetXaxis()->SetLabelSize(0.035);
          gr_alphaS_E->GetHistogram()->GetXaxis()->SetTitleSize(0.03);
          gr_alphaS_E->GetHistogram()->GetYaxis()->SetTitleOffset(1.6);
          gr_alphaS_E->GetHistogram()->GetYaxis()->SetLabelSize(0.035);
          gr_alphaS_E->GetHistogram()->GetZaxis()->SetTitleOffset(1.2);
          c1 ->SetTheta(-21.);
          c1 ->SetPhi(21.);
          c1->Update();
          gr_alphaS_E->Draw("surf1");
          c1->SaveAs(Form("jetratio_alphaS_E_algo%d_R%d.pdf",algo, R_value_int));

          gr_alphaS_E->Write();


  }
          f->Close();


      }


void jetratio_all_graphs::Loop_alphaS_R()
      {
           if (fChain == 0) return;

         Long64_t nentries = fChain->GetEntriesFast();

         Long64_t nbytes = 0, nb = 0;

         Int_t pT_cut_value = 10;
         Int_t E_cut_value = 10;
         Double_t R_value = 0.5;
         Double_t alpha_S_value = 0.1365;
          //algorithm 0: antikt, 1:ee_genkt, 2:kt, 3:valencia, 4:cambridge
         Int_t Jet_algorithm_value = 0;
         Double_t Jet_ratio_value ;

         Int_t R_value_int = R_value*10;

        string algorithm;

         TFile *f = new TFile("jetratio_all_histogram.root", "UPDATE");
        // TTree *tree = new TTree("jetratio", "3+/2+ Jet Ratio histogram with theta cut");

        // TH2F* hist_algo_alphaS = new TH2F(Form("hist_algo_alphaS_pTcut%d",pT_cut_value), "Jet ratio (algorithm,alphaS) at pT cut;",angle_nbin, 0.,50.,100,0.,3.2);
for (int algo=0; algo<5; algo++)
{
        TGraph2D * gr_alphaS_R_pT = new TGraph2D(3);
        TGraph2D * gr_alphaS_R_E = new TGraph2D(3);

      int point1 =0;
      int point2 = 0;


         for (Long64_t jentry=0; jentry<nentries;jentry++)
         {
            Long64_t ientry = LoadTree(jentry);
            if (ientry < 0) break;
            fChain->GetEntry(jentry);
            nb = fChain->GetEntry(jentry);   nbytes += nb;
            // if (Cut(ientry) < 0) continue;


               // Jet ratio as function of (ALGORITHM, ALPHAS)

               if ((pT_cut==pT_cut_value) && (Jet_algorithm==algo) &&(E_cut ==0))
               {
                 gr_alphaS_R_pT->SetPoint(point1, alpha_S, R, Jet_ratio);
                 point1++;
               }


               if ((E_cut==E_cut_value) && (Jet_algorithm==algo)&&(pT_cut ==0))
               {
                 gr_alphaS_R_E->SetPoint(point2, alpha_S,R, Jet_ratio);
                 point2++;
               }


          }

            TCanvas *c1 = new TCanvas("c1", "c1", 800, 650);
            TCanvas *c2 = new TCanvas("c2", "c2", 800, 650);

            if (algo==0) algorithm = "anti-k_{T}";
            if (algo==1) algorithm = "ee_genk_{T}";
            if (algo==2) algorithm = "k_{T}";
            if (algo==3) algorithm = "Valencia";
            if (algo==4) algorithm = "Cambridge";


            c1->cd();
            gr_alphaS_R_pT->SetTitle(Form("R_{3/2} with p_T %d > GeV, %s algorithm; #alpha_{S}; R;R_{3/2}",pT_cut_value, algorithm.c_str()));
            gr_alphaS_R_pT->GetXaxis()->SetTitle("#alpha_{S}");
            gr_alphaS_R_pT->GetYaxis()->SetTitle("R");
            gr_alphaS_R_pT->GetHistogram()->GetXaxis()->SetTitleOffset(1.7);
            gr_alphaS_R_pT->GetHistogram()->GetXaxis()->SetLabelSize(0.03);
            gr_alphaS_R_pT->GetHistogram()->GetXaxis()->SetTitleSize(0.03);
            gr_alphaS_R_pT->GetHistogram()->GetYaxis()->SetTitleOffset(1.6);
            gr_alphaS_R_pT->GetHistogram()->GetYaxis()->SetLabelSize(0.03);
            c1 ->SetTheta(-21.);
            c1 ->SetPhi(21.);
            c1->Update();
            gr_alphaS_R_pT->Draw("surf1");
            c1->SaveAs(Form("jetratio_alphaS_R_pTcut%d_algo%d.pdf",pT_cut_value, algo));

            c2->cd();
            gr_alphaS_R_E->SetTitle(Form("R_{3/2} with E > %d GeV,  %s algorithm; #alpha_{S}; R;R_{3/2}",E_cut_value, algorithm.c_str()));
            gr_alphaS_R_E->GetXaxis()->SetTitle("#alpha_{S}");
            gr_alphaS_R_E->GetYaxis()->SetTitle("R");
            gr_alphaS_R_E->GetZaxis()->SetTitle("R_{3/2}");
            gr_alphaS_R_E->GetHistogram()->GetXaxis()->SetTitleOffset(1.7);
            gr_alphaS_R_E->GetHistogram()->GetXaxis()->SetLabelSize(0.03);
            gr_alphaS_R_E->GetHistogram()->GetXaxis()->SetTitleSize(0.03);
            gr_alphaS_R_E->GetHistogram()->GetYaxis()->SetTitleOffset(1.6);
            gr_alphaS_R_E->GetHistogram()->GetYaxis()->SetLabelSize(0.03);
            gr_alphaS_R_E->GetHistogram()->GetZaxis()->SetTitleOffset(1.3);
            c2 ->SetTheta(-21.);
            c2 ->SetPhi(21.);
            c2->Update();
            gr_alphaS_R_E->Draw("surf1");
            c2->SaveAs(Form("jetratio_alphaS_R_Ecut%d_algo%d.pdf",E_cut_value, algo));


            gr_alphaS_R_pT->Write();
            gr_alphaS_R_E->Write();
}
            f->Close();


        }



// calculates double ratio  jetratio/anikt jetratio
void jetratio_all_graphs::Loop_alphaS_R_double()
              {
                   if (fChain == 0) return;

                 Long64_t nentries = fChain->GetEntriesFast();

                 Long64_t nbytes = 0, nb = 0;

                 Int_t pT_cut_value = 10;
                 Int_t E_cut_value = 10;
                 Double_t R_value[] = {0.3,0.4,0.5,0.6,0.7};
                 Double_t alpha_S_value[] = {0.11,0.115,0.12,0.125,0.1365};
                  //algorithm 0: antikt, 1:ee_genkt, 2:kt, 3:valencia, 4:cambridge
                 Int_t Jet_algorithm_value = 0;
                 Double_t Jet_ratio_value ;

                 Double_t antikt_jetratio;
                 Double_t other_jetratio;
                 Double_t double_jetratio;

                 string algorithm;

                 //TH1D* hist_double_jetratio = new TH1D(Form("hist_double_jetratio_Ecut%d_2",E_cut_value), "double jetratio; Number of jets; Counts", 60,0.,30.);


                 TFile *f = new TFile("jetratio_all_histogram.root", "UPDATE");
                // TTree *tree = new TTree("jetratio", "3+/2+ Jet Ratio histogram with theta cut");

                // TH2F* hist_algo_alphaS = new TH2F(Form("hist_algo_alphaS_pTcut%d",pT_cut_value), "Jet ratio (algorithm,alphaS) at pT cut;",angle_nbin, 0.,50.,100,0.,3.2);
        for (int algo=1; algo<5; algo++)
        {

                TGraph2D * gr_alphaS_R_double = new TGraph2D(3);
                int point1 =0;
                int point2 = 0;

              for(int r=0;r<5;r++)
              {
                for(int a=0; a<5; a++)
                {
                 for (Long64_t jentry=0; jentry<nentries;jentry++)
                 {
                    Long64_t ientry = LoadTree(jentry);
                    if (ientry < 0) break;
                    fChain->GetEntry(jentry);
                    nb = fChain->GetEntry(jentry);   nbytes += nb;
                    // if (Cut(ientry) < 0) continue;


                       // Jet ratio as function of (ALGORITHM, ALPHAS)

                       if ((E_cut==E_cut_value) &&(pT_cut ==0) && (Jet_algorithm==0) && (R==R_value[r]) && (alpha_S==alpha_S_value[a]))
                       {
                          antikt_jetratio = Jet_ratio;
                        }

                        if ((E_cut==E_cut_value) &&(pT_cut ==0)&&(Jet_algorithm==algo)&&(R==R_value[r])&& (alpha_S==alpha_S_value[a]))
                        {
                          other_jetratio = Jet_ratio;
                        }

                  }
                  double_jetratio = other_jetratio/antikt_jetratio;
                  cout << "R : " << R_value[r] << ", antikt : " << antikt_jetratio << ", other_jetratio : " << other_jetratio << endl;
                  gr_alphaS_R_double->SetPoint(point2, alpha_S_value[a],R_value[r], double_jetratio);
                  point2++;

                  }
                }



                    TCanvas *c2 = new TCanvas("c2", "c2", 800, 650);

                    if (algo==0) algorithm = "antikt";
                    if (algo==1) algorithm = "ee_genkt";
                    if (algo==2) algorithm = "kt";
                    if (algo==3) algorithm = "valencia";
                    if (algo==4) algorithm = "cambridge";

                    c2->cd();
                    gr_alphaS_R_double->SetTitle(Form("R_{3/2} of %s / R_{3/2} of antikt; #alpha_{S}; R",algorithm.c_str()));
                    gr_alphaS_R_double->GetXaxis()->SetTitle("#alpha_{S}");
                    gr_alphaS_R_double->GetYaxis()->SetTitle("R");
                    gr_alphaS_R_double->GetHistogram()->GetXaxis()->SetTitleOffset(1.7);
                    gr_alphaS_R_double->GetHistogram()->GetXaxis()->SetTitleSize(0.035);
                    gr_alphaS_R_double->GetHistogram()->GetYaxis()->SetTitleOffset(1.7);
                    c2 ->SetTheta(-21.);
                    c2 ->SetPhi(21.);
                    c2->Update();
                    gr_alphaS_R_double->Draw("surf1");
                    c2->SaveAs(Form("jetratio_alphaS_R_double_Ecut%d_algo%d.pdf",E_cut_value, algo));

                    gr_alphaS_R_double->Write();
        }
                    f->Close();


        }
//double ratio (alhaS, Jet energy cut)
void jetratio_all_graphs::Loop_alphaS_Ecut_double()
{
                           if (fChain == 0) return;

                         Long64_t nentries = fChain->GetEntriesFast();

                         Long64_t nbytes = 0, nb = 0;

                         Int_t pT_cut_value = 0;
                         Int_t E_cut_value[] = {0,5,6,7,8,9,10,11,12,13,14,15,20,25};
                         Double_t R_value = 0.5;
                         int R_value_int = R_value*10;
                         Double_t alpha_S_value[] = {0.11,0.115,0.12,0.125,0.1365};
                          //algorithm 0: antikt, 1:ee_genkt, 2:kt, 3:valencia, 4:cambridge
                         Int_t Jet_algorithm_value = 0;
                         Double_t Jet_ratio_value ;

                         Double_t antikt_jetratio;
                         Double_t other_jetratio;
                         Double_t double_jetratio;

                         string algorithm;

                         //TH1D* hist_double_jetratio = new TH1D(Form("hist_double_jetratio_Ecut%d_2",E_cut_value), "double jetratio; Number of jets; Counts", 60,0.,30.);


                         TFile *f = new TFile("jetratio_all_histogram.root", "UPDATE");
                        // TTree *tree = new TTree("jetratio", "3+/2+ Jet Ratio histogram with theta cut");

                        // TH2F* hist_algo_alphaS = new TH2F(Form("hist_algo_alphaS_pTcut%d",pT_cut_value), "Jet ratio (algorithm,alphaS) at pT cut;",angle_nbin, 0.,50.,100,0.,3.2);
                for (int algo=1; algo<5; algo++)
                {

                        TGraph2D * gr_alphaS_Ecut_double = new TGraph2D(3);
                        int point1 =0;
                        int point2 = 0;

                      for(int e=0; e<14;e++)
                      {
                        for(int a=0; a<5; a++)
                        {
                         for (Long64_t jentry=0; jentry<nentries;jentry++)
                         {
                            Long64_t ientry = LoadTree(jentry);
                            if (ientry < 0) break;
                            fChain->GetEntry(jentry);
                            nb = fChain->GetEntry(jentry);   nbytes += nb;
                            // if (Cut(ientry) < 0) continue;


                               // Jet ratio as function of (ALGORITHM, ALPHAS)

                               if ((R==R_value) &&(pT_cut ==0) && (Jet_algorithm==0) && (E_cut==E_cut_value[e]) && (alpha_S==alpha_S_value[a]))
                               {
                                  antikt_jetratio = Jet_ratio;
                                }

                                if ((R==R_value) &&(pT_cut ==0)&&(Jet_algorithm==algo)&&(E_cut==E_cut_value[e]) && (alpha_S==alpha_S_value[a]))
                                {
                                  other_jetratio = Jet_ratio;
                                }

                          }
                          double_jetratio = other_jetratio/antikt_jetratio;
                          cout << "ecut : " << E_cut_value[e] << ", antikt : " << antikt_jetratio << ", other_jetratio : " << other_jetratio << endl;
                          gr_alphaS_Ecut_double->SetPoint(point2, alpha_S_value[a],E_cut_value[e], double_jetratio);
                          point2++;

                          }
                        }



                            TCanvas *c2 = new TCanvas("c2", "c2", 800, 650);

                            if (algo==1) algorithm = "ee_genkt";
                            if (algo==2) algorithm = "kt";
                            if (algo==3) algorithm = "valencia";
                            if (algo==4) algorithm = "cambridge";

                            c2->cd();
                            gr_alphaS_Ecut_double->SetTitle(Form("R_{3/2} of %s / R_{3/2} of antikt; #alpha_{S}; E cut (GeV)",algorithm.c_str()));
                            gr_alphaS_Ecut_double->GetXaxis()->SetTitle("#alpha_{S}");
                            gr_alphaS_Ecut_double->GetYaxis()->SetTitle("E cut(BeV)");
                            gr_alphaS_Ecut_double->GetHistogram()->GetXaxis()->SetTitleOffset(1.7);
                            gr_alphaS_Ecut_double->GetHistogram()->GetXaxis()->SetTitleSize(0.035);
                            gr_alphaS_Ecut_double->GetHistogram()->GetYaxis()->SetTitleOffset(1.7);
                            c2 ->SetTheta(-21.);
                            c2 ->SetPhi(21.);
                            c2->Update();
                            gr_alphaS_Ecut_double->Draw("surf1");
                            c2->SaveAs(Form("jetratio_alphaS_Ecut_double_R%d_algo%d.pdf",R_value_int, algo));

                            gr_alphaS_Ecut_double->Write();
                }
                            f->Close();


      }
