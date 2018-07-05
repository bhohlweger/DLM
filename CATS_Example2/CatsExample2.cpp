#include <cstdio>

#include "CatsExample2.h"
#include "CATS.h"
#include "DLM_Potentials.h"
#include "DLM_Source.h"

void ExampleFunction1(){
	printf(" ExampleFunction1...\n");
	
///---------- SOME GENERAL VARIABLES ----------
    unsigned NumMomBins = 25;
    double kMin = 0;
    double kMax = 125;

    double MassProton = 938.272;
    double MassLambda = 1115.683;

///---------- NEXT WE CREATE THE CATS OBJECT ----------
    //ALL UNITS ARE IN fm and MeV
    CATS Kitty;

    //(#NumberOfMomBins, minMom, maxMom)
    Kitty.SetMomBins(NumMomBins,kMin,kMax);

///---------- First let us look at pp correlations --------
    //charge1 x charge2, for pp it is +1
    Kitty.SetQ1Q2(1);
    Kitty.SetPdgId(2212, 2212);
    //the reduced mass of the particle pair
    Kitty.SetRedMass((MassProton*MassProton)/(MassProton+MassProton));

    //true = use analytic source; false = take the source from a transport model
    Kitty.SetUseAnalyticSource(true);
    //first 3 parameters - dummies, do not set them
    //all other parametres you can pass to your source function
    //in this example we use a Gauss source, which takes only 1 parameter as input (the size)
    double SourcePars[4] = {0,0,0,1.3};
    Kitty.SetAnaSource(GaussSource, SourcePars);
    //!you can use a transport model for the source, by giving as an input an OSCAR1997A file:
    //Kitty.SetUseAnalyticSource(false);
    //Kitty.SetInputFileName(CHAR_FILENAME);

    //the number of different channels to be taken into account.
    Kitty.SetNumChannels(2);
    //the number of partial waves for the 0th channel
    Kitty.SetNumPW(0,1);//(#WhichChannel, #how many partial waves)
    //the number of partial waves for the 1th channel
    Kitty.SetNumPW(1,1);
    //! N.B. the channel number should have the same oddness as the spin
    //important for the wave-function symmetrization of identical particles

    //the weight with which each channel contributes to the final wave function
    //for pp we have two channels -> 1S0 and 3PX, i.e. we treat those as a singlet and as a triplet
    //=> the ratio between them should be 1:3
    Kitty.SetChannelWeight(0, 0.25);//(#WhichChannel, #what weight)
    Kitty.SetChannelWeight(1, 0.75);
    Kitty.SetSpin(0,0);//0th channel: S=0 channel
    Kitty.SetSpin(1,1);//1th channel: S=1 channel

    //you can define any potential function you want and pass it any set of parameters you want.
    //the trick is to leave the first 2 parameters as placeholders (used internally by CATS)
    //in this example the potential function does not get any parameters.
    //N.B. the array you pass to CATS should always have a min. size of 2, else you might get memory issues.
    double PotPars1S0[10]={0,0,NN_AV18,v18_Coupled3P2,1,1,1,0,0,0};
    //the 0,0 means that we set the 0th channel, l=0 (1S0)
    Kitty.SetShortRangePotential(0,0,fDlmPot,PotPars1S0);

    //this is where the magic happens - we run CATS and all relevant parameters are computed
    Kitty.KillTheCat();

    //GetMomentum gives us the center of the bin, GetCorrFun gives us the corresponding value of C(k)
    printf("1) Result for pp:\n");
    for(unsigned uBin=0; uBin<NumMomBins; uBin++){
        printf("   C(%6.2f)=%.2f  ", Kitty.GetMomentum(uBin), Kitty.GetCorrFun(uBin));
        if( (uBin+1)%5==0 && uBin!=(NumMomBins-1) ) printf("\n");
    }
    printf("\n\n");


///---------- Let us try what happens for pLambda --------
//! One can reuse the same CATS object by changing all settings,
//  we will leave the source the same, i.e. it is not needed to set it up again
//  we want to use 2 channels again (1S0 and 3S1)
    Kitty.SetQ1Q2(0);
    Kitty.SetPdgId(2212, 3122);
    //the reduced mass of the particle pair
    Kitty.SetRedMass((MassProton*MassLambda)/(MassProton+MassLambda));

    //#,#,POT_ID,POT_FLAG,t_tot,t1,t2,s,l,j
    double pLamPotPars1S0[10]={0,0,pL_UsmaniOli,0,0,0,0,0,0,0};
    double pLamPotPars3S1[10]={0,0,pL_UsmaniOli,0,0,0,0,1,0,1};
    //the 0,0 means that we set the 0th channel, l=0 (1S0)
    Kitty.SetShortRangePotential(0,0,fDlmPot,pLamPotPars1S0);
    //the 1,0 means that we set the 1st channel, l=0 (3S1)
    Kitty.SetShortRangePotential(1,0,fDlmPot,pLamPotPars3S1);

    //this is where the magic happens - we run CATS and all relevant parameters are computed
    Kitty.KillTheCat(CATS::kPotentialChanged);

    printf("2) Result for pΛ:\n");
    for(unsigned uBin=0; uBin<NumMomBins; uBin++){
        printf("   C(%6.2f)=%.2f  ", Kitty.GetMomentum(uBin), Kitty.GetCorrFun(uBin));
        if( (uBin+1)%5==0 && uBin!=(NumMomBins-1) ) printf("\n");
    }
    printf("\n\n");

///---------- Let us increase source size by 30% --------
    SourcePars[3] *= 1.3;

    //!if you want to customize the output CATS gives you, you can choose between:
    //CATS::nSilent (no output), CATS::nErrors (only errors),
    //CATS::nWarning (errors and warning), CATS::nAll (full output -> the default option)
    Kitty.SetNotifications(CATS::nWarning);

    //!we run CATS again, however do note that if we change the parameters of our source or potential,
    //!CATS cannot know that, and to maximize performance assumes no change has been done!
    //!thus the user has to specify that by using  kSourceChanged, kPotentialChanged or kAllChanged
    Kitty.KillTheCat(CATS::kSourceChanged);

    printf("3) Result for pΛ (+30%% source size):\n");
    for(unsigned uBin=0; uBin<NumMomBins; uBin++){
        printf("   C(%6.2f)=%.2f  ", Kitty.GetMomentum(uBin), Kitty.GetCorrFun(uBin));
        if( (uBin+1)%5==0 && uBin!=(NumMomBins-1) ) printf("\n");
    }
    printf("\n\n");

}
