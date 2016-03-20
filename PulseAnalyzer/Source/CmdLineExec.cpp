#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "CmdLineExec.h"
#include "dspFrontEnd.h"

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

   if(aCmd->isCmd("A11"    ))  executeA11(aCmd);
   if(aCmd->isCmd("A12"    ))  executeA12(aCmd);
   if(aCmd->isCmd("D11"    ))  executeD11(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeD11(Ris::CmdLineCmd* aCmd)
{
   FrontEndParms* tParms = new FrontEndParms;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\Sample41.csv");
   tParms->setOutputFileName ("C:\\MyLib\\Data\\Pdw41.csv");

   gFrontEnd.detect1(tParms);
   delete tParms;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeA11(Ris::CmdLineCmd* aCmd)
{
   FrontEndParms* tParms = new FrontEndParms;
   tParms->mFs       = 10000.0;
   tParms->mDuration =    10.0;
   tParms->mListMaxNumOfElements = 10000;
   tParms->mListWindowTimeSize   = 0.100;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\PulsePdw11.csv");
   tParms->setOutputFileName ("C:\\MyLib\\Data\\Analyze11.csv");
   tParms->initialize();

   gFrontEnd.analyze11(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeA12(Ris::CmdLineCmd* aCmd)
{
   FrontEndParms* tParms = new FrontEndParms;
   tParms->mFs       = 10000.0;
   tParms->mDuration =    10.0;
   tParms->mListMaxNumOfElements = 10000;
   tParms->mListWindowTimeSize   = 0.100 + 0.00001;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\PulsePdw11.csv");
   tParms->setOutputFileName ("C:\\MyLib\\Data\\Analyze12.csv");
   tParms->initialize();

   gFrontEnd.analyze12(tParms);
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

