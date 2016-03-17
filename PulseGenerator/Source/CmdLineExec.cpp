#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "prnPrint.h"
#include "CmdLineExec.h"

#include "dspSignalGen.h"
#include "dspSignal.h"


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

   if(aCmd->isCmd("T11"    ))  executeT11(aCmd);
   if(aCmd->isCmd("T21"    ))  executeT21(aCmd);
   if(aCmd->isCmd("T22"    ))  executeT22(aCmd);
   if(aCmd->isCmd("T31"    ))  executeT31(aCmd);
   if(aCmd->isCmd("T41"    ))  executeT41(aCmd);
   if(aCmd->isCmd("T42"    ))  executeT42(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeT11(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs = 10000.0;
   tSS->mFp =   100.0;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen1(tSS);
   tSS->normalize();
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample11.csv");
}

//******************************************************************************

void CmdLineExec::executeT21(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs = 10000.0;
   tSS->mFp =   100.0;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen21(tSS);
   tSS->normalize();
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample21.csv");
}

//******************************************************************************

void CmdLineExec::executeT22(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs = 10000.0;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen22(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample22.csv");
}

//******************************************************************************

void CmdLineExec::executeT31(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeT41(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeT42(Ris::CmdLineCmd* aCmd)
{
}

