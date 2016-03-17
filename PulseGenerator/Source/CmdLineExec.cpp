#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>
#include <random>

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
   if(aCmd->isCmd("T32"    ))  executeT32(aCmd);
   if(aCmd->isCmd("T33"    ))  executeT33(aCmd);
   if(aCmd->isCmd("T34"    ))  executeT34(aCmd);
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
   std::random_device tRandomDevice;
   std::mt19937 tRandomGenerator(tRandomDevice());
   std::geometric_distribution<int> tRandomDistribution(1/100.0);

   for (int k = 0; k < 100; k++)
   {
      int kevent = tRandomDistribution(tRandomGenerator);
      Prn::print(0, "%5d %5d",k,kevent);
   }
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
   SignalGen::gen11(tSS);
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
   Signal* tSS = new Signal();
   tSS->mFs  =   10000.0;
   tSS->mFp  =    1000.0;
   tSS->mFm  =      10.0;
   tSS->mDCm =       0.2;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen31(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample31.csv");
}

//******************************************************************************

void CmdLineExec::executeT32(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =   10000.0;
   tSS->mFp  =     100.0;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen32(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample32.csv");
}

//******************************************************************************

void CmdLineExec::executeT33(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =   10000.0;
   tSS->mFp  =     100.0;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen33(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample33.csv");
}

//******************************************************************************

void CmdLineExec::executeT34(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =   10000.0;
   tSS->mFp  =     100.0;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen34(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample34.csv");
}

//******************************************************************************

void CmdLineExec::executeT41(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =   10000.0;
   tSS->mFp  =    1000.0;
   tSS->mFm  =      10.0;
   tSS->mDCm =       0.2;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen41(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample41.csv");
}

//******************************************************************************

void CmdLineExec::executeT42(Ris::CmdLineCmd* aCmd)
{
}

