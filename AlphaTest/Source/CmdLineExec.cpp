#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

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
}
//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);

   if(aCmd->isCmd("ALPHAONE"  ))  executeTestAlphaOne(aCmd);
   if(aCmd->isCmd("ALPHASTAT" ))  executeTestAlphaStatistics(aCmd);
   if(aCmd->isCmd("MOVAVG"    ))  executeTestMovingAverage(aCmd);
   if(aCmd->isCmd("TRIAL"     ))  executeTrialStatistics(aCmd);

   if(aCmd->isCmd("STEP"     ))  executeStep(aCmd);
   if(aCmd->isCmd("RAMP"     ))  executeRamp(aCmd);
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
   tParms->mFs       = 10000.0;
   tParms->mAp1 = 0.01;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\SampleStep.csv");
   tParms->setOutputFileName ("C:\\MyLib\\Data\\FilterAlphaOne.csv");
   tParms->initialize();

   gFilterTester.testAlphaOne(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeTestAlphaStatistics(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->mFs       = 10000.0;
   tParms->mAp1      =    0.01;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\SampleStep.csv");
   tParms->setOutputFileName ("C:\\MyLib\\Data\\FilterAlphaStatistics.csv");
   tParms->initialize();

   gFilterTester.testAlphaStatistics(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeTestMovingAverage(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->mFs              = 10000.0;
   tParms->mWindowSampleSize   = 1000;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\SampleStep.csv");
   tParms->setOutputFileName ("C:\\MyLib\\Data\\FilterMovingAverage.csv");
   tParms->initialize();

   gFilterTester.testMovingAverage(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeTrialStatistics(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\SampleStep.csv");
   tParms->initialize();

   gFilterTester.trial11(tParms);
   delete tParms;
}


//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeStep(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =       10000.0;
   tSS->mTime1 =       0.100;
   tSS->mSigma    =      0.0;
   tSS->mOffset   =      0.0;
   tSS->mDuration =      1.0;
   tSS->initialize();
   tSS->show();
   SignalGen::step(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\SampleStep.csv");
   delete tSS;
}


//******************************************************************************

void CmdLineExec::executeRamp(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =       10000.0;
   tSS->mTime1 =       0.100;
   tSS->mTime2 =       0.200;
   tSS->mSigma    =      0.0;
   tSS->mOffset   =      0.0;
   tSS->mDuration =      1.0;
   tSS->initialize();
   tSS->show();
   SignalGen::ramp(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\SampleRamp.csv");
   delete tSS;
}


