#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "prnPrint.h"
#include "CmdLineExec.h"
#include "dspSignalGen.h"
#include "dspRandomMotion.h"

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

   if(aCmd->isCmd("MOVE1"  ))  executeMove1(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeMove1(Ris::CmdLineCmd* aCmd)
{
   RandomMotion tRandomMotion;
   MotionParms* tParms = new MotionParms;
   tParms->mDuration   =     10.0;
   tParms->mFs         =    100.0;
   tParms->mFp         =      1.0;
   tParms->mSigma      =      1.0;
   tParms->mOffset     =      0.0;
   tParms->mAmplitude  =     10.0;

   tParms->setOutputFileName ("C:\\Alpha\\Data\\RandomMotion.csv");
   tParms->initialize();

   tRandomMotion.propagate(tParms);
   delete tParms;
}

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

