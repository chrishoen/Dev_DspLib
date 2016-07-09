#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "prnPrint.h"
#include "CmdLineExec.h"
#include "dspSignalGen.h"
#include "dspFilterTester.h"

using namespace Dsp;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
void CmdLineExec::reset()
{
  mAlphaOneAP1   = 0.010866739550600640559;

  mAlphaTwoAP1   = 0.20119821919842973;
  mAlphaTwoAP2   = 0.022575101181443902;

  mAlphaThreeAP1 = 0.20119821919842973;
  mAlphaThreeAP2 = 0.022575101181443902;
  mAlphaThreeAP3 = 0.0012665002587567815;

  
  Prn::print(0,"mAlphaOneAP1    %10.8f",mAlphaOneAP1);
  Prn::print(0,"mAlphaTwoAP1    %10.8f",mAlphaTwoAP1);
  Prn::print(0,"mAlphaTwoAP2    %10.8f",mAlphaTwoAP2);
  Prn::print(0,"mAlphaThreeAP1  %10.8f",mAlphaThreeAP1);
  Prn::print(0,"mAlphaThreeAP2  %10.8f",mAlphaThreeAP2);
  Prn::print(0,"mAlphaThreeAP3  %10.8f",mAlphaThreeAP3);
}

//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);

   if(aCmd->isCmd("ALPHAONE"  ))  executeTestAlphaOne(aCmd);
   if(aCmd->isCmd("ALPHATWO"  ))  executeTestAlphaTwo(aCmd);
   if(aCmd->isCmd("ALPHATHREE"))  executeTestAlphaThree(aCmd);
   if(aCmd->isCmd("ALPHASTAT" ))  executeTestAlphaStatistics(aCmd);
   if(aCmd->isCmd("MOVAVG"    ))  executeTestMovingAverage(aCmd);
   if(aCmd->isCmd("TRIAL"     ))  executeTrialStatistics(aCmd);

   if(aCmd->isCmd("CONST"    ))  executeConstant(aCmd);
   if(aCmd->isCmd("IMPULSE"  ))  executeImpulse(aCmd);
   if(aCmd->isCmd("STEP"     ))  executeStep(aCmd);
   if(aCmd->isCmd("RAMP"     ))  executeRamp(aCmd);
   if(aCmd->isCmd("SIN"      ))  executeSinusoid(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTestAlphaOne(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->mFs       = 20.0;
   tParms->mAp1      = mAlphaOneAP1;
   tParms->setInputFileName  ("C:\\Alpha\\Data\\SampleTest.csv");
   tParms->setOutputFileName ("C:\\Alpha\\Data\\FilterAlphaOne.csv");
   tParms->initialize();

   gFilterTester.testAlphaOne(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeTestAlphaTwo(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->mFs       = 20.0;
   tParms->mAp1      = mAlphaTwoAP1;
   tParms->mAp2      = mAlphaTwoAP2;
   tParms->setInputFileName  ("C:\\Alpha\\Data\\SampleTest.csv");
   tParms->setOutputFileName ("C:\\Alpha\\Data\\FilterAlphaTwo.csv");
   tParms->initialize();

   gFilterTester.testAlphaTwo(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeTestAlphaThree(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->mFs       = 20.0;
   tParms->mAp1      = mAlphaThreeAP1;
   tParms->mAp2      = mAlphaThreeAP2;
   tParms->mAp3      = mAlphaThreeAP3;
   tParms->setInputFileName  ("C:\\Alpha\\Data\\SampleTest.csv");
   tParms->setOutputFileName ("C:\\Alpha\\Data\\FilterAlphaThree.csv");
   tParms->initialize();

   gFilterTester.testAlphaThree(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeTestAlphaStatistics(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->mFs       = 20.0;
   tParms->mAp1      = mAlphaOneAP1;
   tParms->setInputFileName  ("C:\\Alpha\\Data\\SampleTest.csv");
   tParms->setOutputFileName ("C:\\Alpha\\Data\\FilterAlphaStatistics.csv");
   tParms->initialize();

   gFilterTester.testAlphaStatistics(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeTestMovingAverage(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->mFs              = 10000.0;
   tParms->mWindowTimeSize    = 0.100;
   tParms->setInputFileName  ("C:\\Alpha\\Data\\SampleTest.csv");
   tParms->setOutputFileName ("C:\\Alpha\\Data\\FilterMovingAverage.csv");

   gFilterTester.testMovingAverage(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeTrialStatistics(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->setInputFileName  ("C:\\Alpha\\Data\\SampleTest.csv");
   tParms->initialize();

   gFilterTester.trial11(tParms);
   delete tParms;
}


//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::normal_distribution<double> tRandomDistribution(0.0, 1.0);
   std::normal_distribution<double>::param_type parm = tRandomDistribution.param();
   parm._Sigma = 2.0;
   tRandomDistribution.param();
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::normal_distribution<double>::param_type parm;

   parm._Init(0.0,2.0);
   std::normal_distribution<double> tRandomDistribution(parm);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeConstant(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =          20.0;
   tSS->mSigma    =      1.0;
   tSS->mOffset   =      0.0;
   tSS->mDuration =    100.0;
   tSS->initialize();
   tSS->show();
   SignalGen::constant(tSS);
   tSS->writeToTextFile("C:\\Alpha\\Data\\SampleTest.csv");
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeImpulse(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =          20.0;
   tSS->mTime1 =        10.0;
   tSS->mSigma    =      0.0;
   tSS->mScale    =      1.0;
   tSS->mOffset   =      0.0;
   tSS->mDuration =    100.0;
   tSS->initialize();
   tSS->show();
   SignalGen::impulse(tSS);
   tSS->writeToTextFile("C:\\Alpha\\Data\\SampleTest.csv");
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeStep(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =          20.0;
   tSS->mTime1 =        10.0;
   tSS->mSigma    =      0.0;
   tSS->mScale    =      1.0;
   tSS->mOffset   =      0.0;
   tSS->mDuration =    100.0;
   tSS->initialize();
   tSS->show();
   SignalGen::step(tSS);
   tSS->writeToTextFile("C:\\Alpha\\Data\\SampleTest.csv");
   delete tSS;
}


//******************************************************************************

void CmdLineExec::executeRamp(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =          20.0;
   tSS->mTime1 =         1.0;
   tSS->mTime2 =         6.0;
   tSS->mSigma    =      0.0;
   tSS->mScale    =      5.0;
   tSS->mOffset   =      0.0;
   tSS->mDuration =     10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::ramp(tSS);
   tSS->writeToTextFile("C:\\Alpha\\Data\\SampleTest.csv");
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeSinusoid(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =          20.0;
   tSS->mFp  =           0.2;
   tSS->mSigma    =      1.0;
   tSS->mScale    =      5.0;
   tSS->mOffset   =      0.0;
   tSS->mDuration =     10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::sinusoid(tSS);
   tSS->writeToTextFile("C:\\Alpha\\Data\\SampleTest.csv");
   delete tSS;
}


