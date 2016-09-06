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
  mAlphaOneAP1   = 0.010866739550600640559;

  mAlphaTwoAP1   = 0.020688654537394208753;
  mAlphaTwoAP2   = 0.00021625305129201406;

  


}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTestAlphaOne(Ris::CmdLineCmd* aCmd)
{
   MotionParms* tParms = new MotionParms;
   tParms->mFs       = 20.0;
   tParms->mAp1      = mAlphaOneAP1;
   tParms->setInputFileName  ("C:\\Alpha\\Data\\SampleTest.csv");
   tParms->setOutputFileName ("C:\\Alpha\\Data\\FilterAlphaOne.csv");
   tParms->initialize();

   gRandomMotion.testAlphaOne(tParms);
   delete tParms;
}

//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);

   if(aCmd->isCmd("ALPHAONE"  ))  executeTestAlphaOne(aCmd);
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

