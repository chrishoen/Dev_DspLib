#include "stdafx.h"

#include "CmdLineExec.h"
#include "Parms.h"
#include "TestOne.h"
#include "dspFilterAlphaOne.h"

#include "CmdLineExec.h"

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
   if (aCmd->isCmd("RESET")) reset();
   if (aCmd->isCmd("GO1"))   executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))   executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))   executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))   executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))   executeGo5(aCmd);
   if (aCmd->isCmd("Parms")) executeParms(aCmd);

   if (aCmd->isCmd("RUN1"))     executeRun1(aCmd);
   if (aCmd->isCmd("RUN2"))     executeRun2(aCmd);
   if (aCmd->isCmd("RUN3"))     executeRun3(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,"2");
   aCmd->setArgDefault(2,"1");
   int tGenSelect = aCmd->argInt(1);
   int tFilterSelect = aCmd->argInt(2);

   gParms.reset();
   gParms.readSection("default");
   switch(tGenSelect)
   {
      case 1: gParms.readSection("GenSin1"); break;
      case 2: gParms.readSection("GenSin2"); break;
      case 3: gParms.readSection("GenStep1"); break;
      case 4: gParms.readSection("GenStep2"); break;
      default: printf("SECTION NOT FOUND\n");
   }
   switch(tFilterSelect)
   {
      case 1: gParms.readSection("AlphaOne1"); break;
      case 2: gParms.readSection("AlphaOne2"); break;
      case 3: gParms.readSection("AlphaOne3"); break;
      default: printf("SECTION NOT FOUND\n");
   }
      

   TestOne tTestOne;
   tTestOne.doRun1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,"2");
   aCmd->setArgDefault(2,"1");
   int tGenSelect = aCmd->argInt(1);
   int tFilterSelect = aCmd->argInt(2);

   gParms.reset();
   gParms.readSection("default");
   switch(tGenSelect)
   {
      case 1: gParms.readSection("GenSin1"); break;
      case 2: gParms.readSection("GenSin2"); break;
      case 3: gParms.readSection("GenStep1"); break;
      case 4: gParms.readSection("GenStep2"); break;
      default: printf("SECTION NOT FOUND\n");
   }
   switch(tFilterSelect)
   {
      case 1: gParms.readSection("AlphaTwo1"); break;
      case 2: gParms.readSection("AlphaTwo2"); break;
      case 3: gParms.readSection("AlphaTwo3"); break;
      default: printf("SECTION NOT FOUND\n");
   }
      

   TestOne tTestOne;
   tTestOne.doRun2();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun3(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run3");

   TestOne tTestOne;
   tTestOne.doRun3();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 10);
   aCmd->setArgDefault(2, 0.9);
   double tTs = 1.0;
   double tStepTime = aCmd->argDouble(1);
   double tStepThresh = aCmd->argDouble(2);

   Dsp::Filter::AlphaOne<double> tFilter;
   tFilter.initializeFromStep(tTs, tStepTime, tStepThresh);

   Prn::print(0, "alpha %6.4f", tFilter.mAlpha);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}


//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
 
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0,"PARMS PARMS PARMS PARMS PARMS PARMS PARMS PARMS PARMS PARMS ");
   gParms.show();
}

