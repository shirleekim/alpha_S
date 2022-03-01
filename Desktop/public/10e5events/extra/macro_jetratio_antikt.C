//this macro creates txt files that contains jet ratios for R=0.5, antikt algorithm
void macro_jetratio_antikt(){


    gROOT->ProcessLine(".L alphaS114_jetratio.C");
    gROOT->ProcessLine("alphaS114_jetratio l");
    gROOT->ProcessLine("l.Loop()");

    gROOT->ProcessLine(".L alphaS115_jetratio.C");
    gROOT->ProcessLine("alphaS115_jetratio a");
    gROOT->ProcessLine("a.Loop()");

    gROOT->ProcessLine(".L alphaS116_jetratio.C");
    gROOT->ProcessLine("alphaS116_jetratio b");
    gROOT->ProcessLine("b.Loop()");

    gROOT->ProcessLine(".L alphaS117_jetratio.C");
    gROOT->ProcessLine("alphaS117_jetratio c");
    gROOT->ProcessLine("c.Loop()");

    gROOT->ProcessLine(".L alphaS118_jetratio.C");
    gROOT->ProcessLine("alphaS118_jetratio d");
    gROOT->ProcessLine("d.Loop()");

    gROOT->ProcessLine(".L alphaS119_jetratio.C");
    gROOT->ProcessLine("alphaS119_jetratio e");
    gROOT->ProcessLine("e.Loop()");

    gROOT->ProcessLine(".L alphaS12_jetratio.C");
    gROOT->ProcessLine("alphaS12_jetratio f");
    gROOT->ProcessLine("f.Loop()");

    gROOT->ProcessLine(".L alphaS121_jetratio.C");
    gROOT->ProcessLine("alphaS121_jetratio g");
    gROOT->ProcessLine("g.Loop()");

    gROOT->ProcessLine(".L alphaS122_jetratio.C");
    gROOT->ProcessLine("alphaS122_jetratio h");
    gROOT->ProcessLine("h.Loop()");


    gROOT->ProcessLine(".L alphaS123_jetratio.C");
    gROOT->ProcessLine("alphaS123_jetratio i");
    gROOT->ProcessLine("i.Loop()");

    gROOT->ProcessLine(".L alphaS124_jetratio.C");
    gROOT->ProcessLine("alphaS124_jetratio j");
    gROOT->ProcessLine("j.Loop()");

    gROOT->ProcessLine(".L alphaS125_jetratio.C");
    gROOT->ProcessLine("alphaS125_jetratio k");
    gROOT->ProcessLine("k.Loop()");

    gROOT->ProcessLine(".L alphaS126_jetratio.C");
    gROOT->ProcessLine("alphaS126_jetratio m");
    gROOT->ProcessLine("m.Loop()");


}
