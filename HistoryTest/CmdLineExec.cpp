#include "stdafx.h"

#include "CmdLineExec.h"
#include "Parms.h"
#include "TestOne.h"
#include "DemoOne.h"
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
   if (aCmd->isCmd("RUN1DEG"))  executeRun1Deg(aCmd);
   if (aCmd->isCmd("RUN2"))     executeRun2(aCmd);
   if (aCmd->isCmd("RUN3"))     executeRun3(aCmd);
   if (aCmd->isCmd("RUN4"))     executeRun4(aCmd);
   if (aCmd->isCmd("RUN5"))     executeRun5(aCmd);
   if (aCmd->isCmd("RUN6"))     executeRun6(aCmd);
   if (aCmd->isCmd("RUN7"))     executeRun7(aCmd);
   if (aCmd->isCmd("RUN8"))     executeRun8(aCmd);
   if (aCmd->isCmd("MEM1"))     executeMem1(aCmd);

   if (aCmd->isCmd("Cas1"))   executeCausal1(aCmd);
   if (aCmd->isCmd("Cas12"))  executeCausal12(aCmd);

   if (aCmd->isCmd("Non1"))   executeNoncausal1(aCmd);
   if (aCmd->isCmd("Non12"))  executeNoncausal12(aCmd);

   if (aCmd->isCmd("Demo1"))  executeDemo1(aCmd);
   if (aCmd->isCmd("Demo2"))  executeDemo2(aCmd);
   if (aCmd->isCmd("Demo3"))  executeDemo3(aCmd);
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

   Dsp::Filter::AlphaOneT<double> tFilter;
   tFilter.initializeFromStep(tTs, tStepTime, tStepThresh);

   Prn::print(0, "alpha %6.4f", tFilter.mAlpha);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDemo1(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("Demo1");

   DemoOne tDemoOne;
   tDemoOne.doDemo1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDemo2(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("Demo2");

   DemoOne tDemoOne;
   tDemoOne.doDemo2();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDemo3(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("Demo3");

   DemoOne tDemoOne;
   tDemoOne.doDemo3();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeMem1(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run1");

   TestOne tTestOne;
   tTestOne.doMem1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeCausal1(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("causal1");

   TestOne tTestOne;
   tTestOne.doCausal1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeCausal12(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("causal1");

   TestOne tTestOne;
   tTestOne.doCausal12();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeNoncausal1(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("noncausal1");

   TestOne tTestOne;
   tTestOne.doCausal1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeNoncausal12(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("noncausal1");

   TestOne tTestOne;
   tTestOne.doCausal12();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun1(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run1");

   TestOne tTestOne;
   tTestOne.doRun1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun1Deg(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run1deg");

   TestOne tTestOne;
   tTestOne.doRun1Deg();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun2(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run2");

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

void CmdLineExec::executeRun4(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run4");

   TestOne tTestOne;
   tTestOne.doRun4();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun5(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run5");

   TestOne tTestOne;
   tTestOne.doRun5();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun6(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run6");

   TestOne tTestOne;
   tTestOne.doRun6();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun7(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run7");

   TestOne tTestOne;
   tTestOne.doRun7();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun8(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run8");

   TestOne tTestOne;
   tTestOne.doRun8();
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}


//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
 
}

//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0,"PARMS PARMS PARMS PARMS PARMS PARMS PARMS PARMS PARMS PARMS ");
   aCmd->setArgDefault(1,"demo1");
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection(aCmd->argString(1));
   gParms.show();
}

