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

   if(aCmd->isCmd("FILTER11" ))  executeFilter11(aCmd);
   if(aCmd->isCmd("FILTER12" ))  executeFilter12(aCmd);
   if(aCmd->isCmd("TRIAL11"  ))  executeTrial11(aCmd);

   if(aCmd->isCmd("GEN51"    ))  executeGen51(aCmd);
   if(aCmd->isCmd("GEN52"    ))  executeGen52(aCmd);
   if(aCmd->isCmd("GEN53"    ))  executeGen53(aCmd);
   if(aCmd->isCmd("GEN54"    ))  executeGen54(aCmd);
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

void CmdLineExec::executeFilter11(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->mFs       = 10000.0;
   tParms->mAp1 = 0.01;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\Sample52.csv");
   tParms->setOutputFileName ("C:\\MyLib\\Data\\Filter11.csv");
   tParms->initialize();

   gFilterTester.filter11(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeFilter12(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->mFs       = 10000.0;
   tParms->mAp1      =   0.001;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\Sample52.csv");
   tParms->setOutputFileName ("C:\\MyLib\\Data\\Filter12.csv");
   tParms->initialize();

   gFilterTester.filter12(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeTrial11(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\Sample52.csv");
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

void CmdLineExec::executeGen51(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =   10000.0;
   tSS->mKev1 =     1000;
   tSS->mDuration =  1.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen51(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample51.csv");
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeGen52(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =       10000.0;
   tSS->mKev1 =         1000;
   tSS->mSigma    =      1.0;
   tSS->mOffset   =      0.0;
   tSS->mDuration =     10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen52(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample52.csv");
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeGen53(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGen54(Ris::CmdLineCmd* aCmd)
{
}


