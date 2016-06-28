#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "prnPrint.h"
#include "CmdLineExec.h"
#include "dspSignalSource.h"

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

   if(aCmd->isCmd("CONST"    ))  executeConstant(aCmd);
   if(aCmd->isCmd("SIN"      ))  executeSinusoid(aCmd);
}

//******************************************************************************
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
   aCmd->setArgDefault(1,100);
   int tCount = aCmd->argInt(1);

   SignalSource* tSS = new SignalSource();
   tSS->mFs         =     20.0;
   tSS->mFp         =      1.0;
   tSS->mSigma      =      1.0;
   tSS->mOffset     =      0.0;
   tSS->mAmplitude  =      0.0;
   tSS->initialize();
   tSS->show();

   for (int i = 0; i < tCount; i++)
   {
      tSS->advance();
      Prn::print(0,"%5d   %8.2f   %9.6f",i,tSS->mT,tSS->mX);
   }

   delete tSS;
}

//******************************************************************************

void CmdLineExec::executeSinusoid(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,100);
   int tCount = aCmd->argInt(1);

   SignalSource* tSS = new SignalSource();
   tSS->mFs         =     20.0;
   tSS->mFp         =      1.0;
   tSS->mSigma      =      0.0;
   tSS->mOffset     =      0.0;
   tSS->mAmplitude  =     10.0;
   tSS->initialize();
   tSS->show();

   for (int i = 0; i < tCount; i++)
   {
      tSS->advance();
      Prn::print(0,"%5d   %8.2f   %9.6f",i,tSS->mT,tSS->mX);
   }

   delete tSS;
}


