#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "prnPrint.h"
#include "CmdLineExec.h"
#include "Parms.h"
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

   if(aCmd->isCmd("RUN1"   ))  executeRun1(aCmd);
   if(aCmd->isCmd("RUN2"   ))  executeRun2(aCmd);
   if(aCmd->isCmd("RUN3"   ))  executeRun3(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun1(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run1");

   RandomMotion tRandomMotion;
   tRandomMotion.propagate1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,"run21");
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection(aCmd->argString(1));

   RandomMotion tRandomMotion;
   tRandomMotion.propagate2();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun3(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run3");

   RandomMotion tRandomMotion;
   tRandomMotion.propagate3();
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
   std::uniform_real_distribution<double>::param_type parm;

   parm._Init(0.0,2.0);
   std::uniform_real_distribution<double> tRandomDistribution(parm);
   std::uniform_real_distribution<double> tRandomDistribution2(0.0,2.0);
}

//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

