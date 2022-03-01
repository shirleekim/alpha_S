void macro_cut_valencia(){
    gROOT->ProcessLine(".L R5cut.C");
    gROOT->ProcessLine("R5cut m");
    gROOT->ProcessLine("m.Loop_valencia()");

  gROOT->ProcessLine(".L R3cut.C");
    gROOT->ProcessLine("R3cut a");
    gROOT->ProcessLine("a.Loop_valencia()");

  gROOT->ProcessLine(".L R4cut.C");
    gROOT->ProcessLine("R4cut b");
    gROOT->ProcessLine("b.Loop_valencia()");

  gROOT->ProcessLine(".L R6cut.C");
    gROOT->ProcessLine("R6cut c");
    gROOT->ProcessLine("c.Loop_valencia()");

  gROOT->ProcessLine(".L R7cut.C");
    gROOT->ProcessLine("R7cut d");
    gROOT->ProcessLine("d.Loop_valencia()");


}
