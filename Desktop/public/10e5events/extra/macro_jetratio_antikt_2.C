//this macro creates txt files that contains jet ratios for R=0.5, antikt algorithm
void macro_jetratio_antikt_2(){


    gROOT->ProcessLine(".L alphaS111_jetratio.C");
    gROOT->ProcessLine("alphaS111_jetratio l");
    gROOT->ProcessLine("l.Loop()");

    gROOT->ProcessLine(".L alphaS112_jetratio.C");
    gROOT->ProcessLine("alphaS112_jetratio a");
    gROOT->ProcessLine("a.Loop()");

    gROOT->ProcessLine(".L alphaS113_jetratio.C");
    gROOT->ProcessLine("alphaS113_jetratio b");
    gROOT->ProcessLine("b.Loop()");

    gROOT->ProcessLine(".L alphaS127_jetratio.C");
    gROOT->ProcessLine("alphaS127_jetratio c");
    gROOT->ProcessLine("c.Loop()");

    gROOT->ProcessLine(".L alphaS128_jetratio.C");
    gROOT->ProcessLine("alphaS128_jetratio d");
    gROOT->ProcessLine("d.Loop()");

    gROOT->ProcessLine(".L alphaS129_jetratio.C");
    gROOT->ProcessLine("alphaS129_jetratio e");
    gROOT->ProcessLine("e.Loop()");

    gROOT->ProcessLine(".L alphaS130_jetratio.C");
    gROOT->ProcessLine("alphaS130_jetratio f");
    gROOT->ProcessLine("f.Loop()");

}
