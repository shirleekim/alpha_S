void macro_jetratio_valencia(){

    gROOT->ProcessLine(".L R5jetratio.C");
    gROOT->ProcessLine("R5jetratio m");
    gROOT->ProcessLine("m.Loop_valencia()");

  gROOT->ProcessLine(".L R3jetratio.C");
    gROOT->ProcessLine("R3jetratio a");
    gROOT->ProcessLine("a.Loop_valencia()");

  gROOT->ProcessLine(".L R4jetratio.C");
    gROOT->ProcessLine("R4jetratio b");
    gROOT->ProcessLine("b.Loop_valencia()");

  gROOT->ProcessLine(".L R6jetratio.C");
    gROOT->ProcessLine("R6jetratio c");
    gROOT->ProcessLine("c.Loop_valencia()");

  gROOT->ProcessLine(".L R7jetratio.C");
    gROOT->ProcessLine("R7jetratio d");
    gROOT->ProcessLine("d.Loop_valencia()");


}
