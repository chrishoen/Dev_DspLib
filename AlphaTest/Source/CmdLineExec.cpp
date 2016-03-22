#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "CmdLineExec.h"
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

   if(aCmd->isCmd("F11"    ))  executeF11(aCmd);
   if(aCmd->isCmd("F12"    ))  executeF12(aCmd);
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

void CmdLineExec::executeF11(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->mFs       = 10000.0;
   tParms->mDuration =     1.0;
   tParms->mAp1 = 0.01;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\Sample52.csv");
   tParms->setOutputFileName ("C:\\MyLib\\Data\\Filter11.csv");
   tParms->initialize();

   gFilterTester.filter11(tParms);
   delete tParms;
}

//******************************************************************************

void CmdLineExec::executeF12(Ris::CmdLineCmd* aCmd)
{
   FilterParms* tParms = new FilterParms;
   tParms->mFs       = 10000.0;
   tParms->mDuration =     1.0;
   tParms->mAp1      =   0.001;
   tParms->setInputFileName  ("C:\\MyLib\\Data\\Sample52.csv");
   tParms->setOutputFileName ("C:\\MyLib\\Data\\Filter12.csv");
   tParms->initialize();

   gFilterTester.filter12(tParms);
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

