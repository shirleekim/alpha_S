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
   Double_t alpha_S_value = 0.13;
    //algorithm 0: antikt, 1:ee_genkt, 2:kt, 3:valencia, 4:cambridge
   Int_t Jet_algorithm_value = 0;
   Double_t Jet_ratio_value ;

   Int_t R_value_int = R_value*10;

   Double_t error = 0.;
   Int_t thetacut = 0;

   TFile *f = new TFile("jetratio_all_histogram.root", "RECREATE");
  // TTree *tree = new TTree("jetratio", "3+/2+ R_{3/2} histogram with theta cut");


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


         // R_{3/2} as function of (ALGORITHM, ALPHAS)

         if ((pT_cut==pT_cut_value) && (R==R_value) &&(E_cut ==0))
         {
           gr_algo_alphaS_pT->SetPoint(point1, Jet_algorithm, alpha_S, Jet_ratio);
           point1++;
           cout << Jet_algorithm << " " << alpha_S << " " << Jet_ratio << endl;
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
      gr_algo_alphaS_pT->SetTitle(Form("R_{3/2} at pT cut %d, R=%.1f; Jet Algorithm; #alpha_S",pT_cut_value, R_value));
      gr_algo_alphaS_pT->GetXaxis()->SetTitle("Jet Algorithm");
      gr_algo_alphaS_pT->GetYaxis()->SetTitle("Initial alpha S");
      gr_algo_alphaS_pT->GetHistogram()->GetXaxis()->SetTitleOffset(2.5);
      gr_algo_alphaS_pT->GetHistogram()->GetYaxis()->SetTitleOffset(3);
      gr_algo_alphaS_pT->Draw("surf1");
      c1->Update();
      c1->SaveAs(Form("jetratio_algo_alphaS_pTcut%d_R%d.pdf",pT_cut_value, R_value_int));

      c2->cd();
      gr_algo_alphaS_E->SetTitle(Form("R_{3/2} at E cut %d, R=%.1f; Jet Algorithm; #alpha_S",E_cut_value, R_value));
      gr_algo_alphaS_E->GetXaxis()->SetTitle("Jet Algorithm");
      gr_algo_alphaS_E->GetYaxis()->SetTitle("Initial alpha S");
      gr_algo_alphaS_E->GetHistogram()->GetXaxis()->SetTitleOffset(2.5);
      gr_algo_alphaS_E->GetHistogram()->GetYaxis()->SetTitleOffset(3);
      gr_algo_alphaS_E->Draw("surf1");
      c2->Update();
      c2->SaveAs(Form("jetratio_algo_alphaS_Ecut%d_R%d.pdf",E_cut_value, R_value_int));


      gr_algo_alphaS_pT->Write();
      gr_algo_alphaS_E->Write();

    f->Close();


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
     Double_t alpha_S_array[5] = {0.11, 0.115, 0.12, 0.125, 0.13};
     Double_t Jet_algorithm_array[5] = {0,1,2,3,4};

     TFile *f = new TFile("jetratio_all_histogram.root", "UPDATE");
    // TTree *tree = new TTree("jetratio", "3+/2+ R_{3/2} histogram with theta cut");

    // TH2F* hist_algo_alphaS = new TH2F(Form("hist_algo_alphaS_pTcut%d",pT_cut_value), "R_{3/2} (algorithm,alphaS) at pT cut;",angle_nbin, 0.,50.,100,0.,3.2);

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


           // R_{3/2} as function of (ALGORITHM, ALPHAS)

           if ((Jet_algorithm==algo) && (R==R_value) && (E_cut==0))
           {
             gr_alphaS_pT->SetPoint(point1, alpha_S, pT_cut, Jet_ratio);
             point1++;
          //   cout << Jet_algorithm << " " << alpha_S << " " << Jet_ratio << endl;
           }





      }

        TCanvas *c1 = new TCanvas("c1", "c1", 800, 650);


        c1->cd();
        gr_alphaS_pT->SetTitle(Form("R_{3/2} with algorithm %d, R=%.1f; #alpha_S; pT cut",algo, R_value));
        gr_alphaS_pT->GetXaxis()->SetTitle("Initial alpha S");
        gr_alphaS_pT->GetYaxis()->SetTitle("pT cut");
        gr_alphaS_pT->GetHistogram()->GetXaxis()->SetTitleOffset(1.6);
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
       Double_t alpha_S_array[5] = {0.11, 0.115, 0.12, 0.125, 0.13};
       Double_t Jet_algorithm_array[5] = {0,1,2,3,4};

       TFile *f = new TFile("jetratio_all_histogram.root", "UPDATE");
      // TTree *tree = new TTree("jetratio", "3+/2+ R_{3/2} histogram with theta cut");

      // TH2F* hist_algo_alphaS = new TH2F(Form("hist_algo_alphaS_pTcut%d",pT_cut_value), "R_{3/2} (algorithm,alphaS) at pT cut;",angle_nbin, 0.,50.,100,0.,3.2);

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


             // R_{3/2} as function of (ALGORITHM, ALPHAS)

             if ((Jet_algorithm==algo) && (R==R_value) && (pT_cut ==0))
             {
               gr_alphaS_E->SetPoint(point1, alpha_S, E_cut, Jet_ratio);
               point1++;
            //   cout << Jet_algorithm << " " << alpha_S << " " << Jet_ratio << endl;
             }





        }

          TCanvas *c1 = new TCanvas("c1", "c1", 800, 650);


          c1->cd();
          gr_alphaS_E->SetTitle(Form("R_{3/2} with algorithm %d, R=%.1f; #alpha_S; E cut",algo, R_value));
          gr_alphaS_E->GetXaxis()->SetTitle("Initial alpha S");
          gr_alphaS_E->GetYaxis()->SetTitle("E cut");
          gr_alphaS_E->GetHistogram()->GetXaxis()->SetTitleOffset(1.6);
          gr_alphaS_E->GetHistogram()->GetYaxis()->SetTitleOffset(1.6);
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
         Double_t alpha_S_value = 0.13;
          //algorithm 0: antikt, 1:ee_genkt, 2:kt, 3:valencia, 4:cambridge
         Int_t Jet_algorithm_value = 0;
         Double_t Jet_ratio_value ;

         Int_t R_value_int = R_value*10;

         TFile *f = new TFile("jetratio_all_histogram.root", "UPDATE");
        // TTree *tree = new TTree("jetratio", "3+/2+ R_{3/2} histogram with theta cut");

        // TH2F* hist_algo_alphaS = new TH2F(Form("hist_algo_alphaS_pTcut%d",pT_cut_value), "R_{3/2} (algorithm,alphaS) at pT cut;",angle_nbin, 0.,50.,100,0.,3.2);
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


               // R_{3/2} as function of (ALGORITHM, ALPHAS)

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

            c1->cd();
            gr_alphaS_R_pT->SetTitle(Form("R_{3/2} at pT cut %d, algorithm %d; #alpha_S; R",pT_cut_value, algo));
            gr_alphaS_R_pT->GetXaxis()->SetTitle("Initial alpha S");
            gr_alphaS_R_pT->GetYaxis()->SetTitle("R");
            gr_alphaS_R_pT->GetHistogram()->GetXaxis()->SetTitleOffset(1.6);
            gr_alphaS_R_pT->GetHistogram()->GetYaxis()->SetTitleOffset(1.6);
            c1 ->SetTheta(-21.);
            c1 ->SetPhi(21.);
            c1->Update();
            gr_alphaS_R_pT->Draw("surf1");
            c1->SaveAs(Form("jetratio_alphaS_R_pTcut%d_algo%d.pdf",pT_cut_value, algo));

            c2->cd();
            gr_alphaS_R_E->SetTitle(Form("R_{3/2} at E cut %d,algorithm %d; #alpha_S; R",E_cut_value, algo));
            gr_alphaS_R_E->GetXaxis()->SetTitle("Initial alpha S");
            gr_alphaS_R_E->GetYaxis()->SetTitle("R");
            gr_alphaS_R_E->GetHistogram()->GetXaxis()->SetTitleOffset(1.6);
            gr_alphaS_R_E->GetHistogram()->GetYaxis()->SetTitleOffset(1.6);
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


void jetratio_all_graphs::Loop_alphaS_jetratio(){


       if (fChain == 0) return;

     Long64_t nentries = fChain->GetEntriesFast();

     Long64_t nbytes = 0, nb = 0;

     Int_t pT_cut_value = 10;
     Int_t E_cut_value = 10;
     Double_t R_value = 0.5;
     Double_t alpha_S_value = 0.13;
      //algorithm 0: antikt, 1:ee_genkt, 2:kt, 3:valencia, 4:cambridge
     Int_t Jet_algorithm_value = 0;
     Double_t Jet_ratio_value ;
     Int_t theta_cut_value = 0;

     Int_t R_value_int = R_value*10;

     Int_t algo = 0;

     Double_t error;

     TFile *f = new TFile("jetratio_all_histogram.root", "UPDATE");
    // TTree *tree = new TTree("jetratio", "3+/2+ R_{3/2} histogram with theta cut");

    // TH2F* hist_algo_alphaS = new TH2F(Form("hist_algo_alphaS_pTcut%d",pT_cut_value), "R_{3/2} (algorithm,alphaS) at pT cut;",angle_nbin, 0.,50.,100,0.,3.2);

    TGraph * gr1 = new TGraph ;
    TGraph * gr2 = new TGraph ;

    TGraphErrors* error_gr1 = new TGraphErrors();
    TGraphErrors* error_gr2 = new TGraphErrors();


  int point1 =0;
  int point2 = 0;

     for (Long64_t jentry=0; jentry<nentries;jentry++)
     {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        fChain->GetEntry(jentry);
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;


           // R_{3/2} as function of (ALGORITHM, ALPHAS)

/*
           if ((pT_cut==pT_cut_value) && (Jet_algorithm==algo) &&(E_cut ==0) && (theta_cut == theta_cut_value))
           {
             gr_pT->SetPoint(point1, alpha_S, R, Jet_ratio);
             point1++;
           }

*/

          //without theta cut
           if ((E_cut==E_cut_value) && (Jet_algorithm==algo)&&(pT_cut ==0)&&(theta_cut == 0))
           {
             gr1->SetPoint(point1, alpha_S, Jet_ratio);
             error_gr1->SetPointError(point1, error, 0);
             point1++;
           }

           //with theta cut
            if ((E_cut==E_cut_value) && (Jet_algorithm==algo)&&(pT_cut ==0)&&(theta_cut == 1))
            {
              gr2->SetPoint(point2, alpha_S, Jet_ratio);
              error_gr2->SetPointError(point2, error, 0);
              point2++;
            }




        TCanvas *c1 = new TCanvas("c1", "c1", 800, 650);
        TCanvas *c2 = new TCanvas("c2", "c2", 800, 650);

        c1->cd();
        gr1->SetTitle(Form("R_{3/2} at pT cut %d, algorithm %d;#alpha_S; R_{3/2} ",pT_cut_value, algo));
        gr1->GetXaxis()->SetTitle("Initial alpha S");
        gr1->GetYaxis()->SetTitle("R");
        gr1->GetHistogram()->GetYaxis()->SetTitleSize(0.025);
        c1->Update();
        gr1->SetMarkerStyle(21);
        gr1->Draw("P");
        error_gr1->Draw();
        c1->SaveAs(Form("jetratio_alphaS_R5_Ecut%d_algo%d_notheta.pdf",E_cut_value, algo));

        c2->cd();
        gr2->SetTitle(Form("R_{3/2} at E cut %d,algorithm %d; #alpha_S; R_{3/2}",E_cut_value, algo));
        gr2->GetXaxis()->SetTitle("Initial alpha S");
        gr2->GetYaxis()->SetTitle("R");
        gr2->GetHistogram()->GetXaxis()->SetTitleOffset(1.6);
        gr2->GetHistogram()->GetYaxis()->SetTitleOffset(1.6);
        gr2->SetMarkerStyle(21);
        c2->Update();
        gr2->Draw("P");
        error_gr2->Draw();
        c2->SaveAs(Form("jetratio_alphaS_R5_Ecut%d_algo%d_theta.pdf",E_cut_value, algo));


        gr1->Write();
        gr2->Write();
        error_gr1->Write();
        error_gr2->Write();
  }
        f->Close();









}
