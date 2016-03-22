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
#include "dspPulseGen.h"
#include "dspPdwSequence.h"


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

   if(aCmd->isCmd("S11"    ))  executeS11(aCmd);
   if(aCmd->isCmd("S21"    ))  executeS21(aCmd);
   if(aCmd->isCmd("S22"    ))  executeS22(aCmd);
   if(aCmd->isCmd("S31"    ))  executeS31(aCmd);
   if(aCmd->isCmd("S32"    ))  executeS32(aCmd);
   if(aCmd->isCmd("S33"    ))  executeS33(aCmd);
   if(aCmd->isCmd("S34"    ))  executeS34(aCmd);
   if(aCmd->isCmd("S41"    ))  executeS41(aCmd);
   if(aCmd->isCmd("S42"    ))  executeS42(aCmd);

   if(aCmd->isCmd("P11"    ))  executeP11(aCmd);
   if(aCmd->isCmd("P21"    ))  executeP21(aCmd);
   if(aCmd->isCmd("P22"    ))  executeP22(aCmd);

   if(aCmd->isCmd("F51"    ))  executeF51(aCmd);
   if(aCmd->isCmd("F52"    ))  executeF52(aCmd);
   if(aCmd->isCmd("F53"    ))  executeF53(aCmd);
   if(aCmd->isCmd("F54"    ))  executeF54(aCmd);
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

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeP11(Ris::CmdLineCmd* aCmd)
{
   PdwSequence* tPS = new PdwSequence();
   tPS->mFs       = 10000.0;
   tPS->mFm       =   100.0;
   tPS->mDuration =    10.0;
   tPS->setPdwFileName ("C:\\MyLib\\Data\\PulsePdw11.csv");
   tPS->setPlotFileName("C:\\MyLib\\Data\\PulsePlot11.csv");
   tPS->initialize();
   tPS->show();
   PulseGen::gen11(tPS);
   tPS->writeToTextFile();
   delete tPS;
}

//******************************************************************************

void CmdLineExec::executeP21(Ris::CmdLineCmd* aCmd)
{
   PdwSequence* tPS = new PdwSequence();
   tPS->mFs       = 10000.0;
   tPS->mFm       =   100.0;
   tPS->mDuration =    10.0;
   tPS->setPdwFileName ("C:\\MyLib\\Data\\PulsePdw21.csv");
   tPS->setPlotFileName("C:\\MyLib\\Data\\PulsePlo21.csv");
   tPS->initialize();
   tPS->show();
   PulseGen::gen21(tPS);
   tPS->writeToTextFile();
   delete tPS;
}

//******************************************************************************

void CmdLineExec::executeP22(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeS11(Ris::CmdLineCmd* aCmd)
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
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeS21(Ris::CmdLineCmd* aCmd)
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
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeS22(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs = 10000.0;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen22(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample22.csv");
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeS31(Ris::CmdLineCmd* aCmd)
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
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeS32(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =   10000.0;
   tSS->mFp  =     100.0;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen32(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample32.csv");
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeS33(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =   10000.0;
   tSS->mFp  =     100.0;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen33(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample33.csv");
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeS34(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =   10000.0;
   tSS->mFp  =     100.0;
   tSS->mDuration = 10.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen34(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample34.csv");
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeS41(Ris::CmdLineCmd* aCmd)
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
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeS42(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeF51(Ris::CmdLineCmd* aCmd)
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

void CmdLineExec::executeF52(Ris::CmdLineCmd* aCmd)
{
   Signal* tSS = new Signal();
   tSS->mFs  =   10000.0;
   tSS->mKev1 =     1000;
   tSS->mSigma    =  4.0;
   tSS->mOffset   =  0.0;
   tSS->mDuration =  1.0;
   tSS->initialize();
   tSS->show();
   SignalGen::gen52(tSS);
   tSS->writeToTextFile("C:\\MyLib\\Data\\Sample52.csv");
   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeF53(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeF54(Ris::CmdLineCmd* aCmd)
{
}

