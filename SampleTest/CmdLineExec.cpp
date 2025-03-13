#include "stdafx.h"

#include "risSystemCalls.h"
#include "CmdLineExec.h"
#include "Parms.h"
#include "TestOne.h"
#include "dspFilterAlphaOne.h"

#include "CmdLineExec.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
void CmdLineExec::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("RESET")) reset();

   if (aCmd->isCmd("RUN1"))     executeRun1(aCmd);
   if (aCmd->isCmd("RUN2"))     executeRun2(aCmd);
   if (aCmd->isCmd("RUN3"))     executeRun3(aCmd);

   if (aCmd->isCmd("TEST1"))    executeTest1(aCmd);
   if (aCmd->isCmd("TEST2"))    executeTest2(aCmd);
   if (aCmd->isCmd("TEST3"))    executeTest3(aCmd);
   if (aCmd->isCmd("PLOT"))     executePlot(aCmd);

   if (aCmd->isCmd("GO1"))   executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))   executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))   executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))   executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))   executeGo5(aCmd);
   if (aCmd->isCmd("Parms")) executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,"11");
   int tFilterSelect = aCmd->argInt(1);

   gParms.reset();
   gParms.readSection("default");
   switch(tFilterSelect)
   {
      case 11: gParms.readSection("AlphaOne11"); break;
      case 12: gParms.readSection("AlphaOne12"); break;
      case 13: gParms.readSection("AlphaOne13"); break;
      case 21: gParms.readSection("AlphaOne21"); break;
      case 22: gParms.readSection("AlphaOne22"); break;
      case 23: gParms.readSection("AlphaOne23"); break;
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
   aCmd->setArgDefault(1,"11");
   int tFilterSelect = aCmd->argInt(1);

   gParms.reset();
   gParms.readSection("default");
   switch(tFilterSelect)
   {
      case 11: gParms.readSection("AlphaTwo11"); break;
      case 12: gParms.readSection("AlphaTwo12"); break;
      case 13: gParms.readSection("AlphaTwo13"); break;
      case 21: gParms.readSection("AlphaTwo21"); break;
      case 22: gParms.readSection("AlphaTwo22"); break;
      case 23: gParms.readSection("AlphaTwo23"); break;
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
   aCmd->setArgDefault(1,"11");
   int tFilterSelect = aCmd->argInt(1);

   gParms.reset();
   gParms.readSection("default");
   switch(tFilterSelect)
   {
      case 11: gParms.readSection("AlphaThree11"); break;
      case 12: gParms.readSection("AlphaThree12"); break;
      case 13: gParms.readSection("AlphaThree13"); break;
      case 21: gParms.readSection("AlphaThree21"); break;
      case 22: gParms.readSection("AlphaThree22"); break;
      case 23: gParms.readSection("AlphaThree23"); break;
      default: printf("SECTION NOT FOUND\n");
   }

   TestOne tTestOne;
   tTestOne.doRun3();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTest1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,"0.1");
   double tAlpha = aCmd->argDouble(1);

   gParms.reset();
   gParms.readSection("default");

   gParms.readSection("AlphaOne11");
   gParms.mHistoryFilterParms1.mAlphaAlpha = tAlpha;

   TestOne tTestOne;
   tTestOne.doRun1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTest2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,"0.1");
   double tAlpha = aCmd->argDouble(1);

   gParms.reset();
   gParms.readSection("default");

   gParms.readSection("AlphaTwo11");
   gParms.mHistoryFilterParms1.mAlphaAlpha = tAlpha;

   TestOne tTestOne;
   tTestOne.doRun2();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTest3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,"0.1");
   double tAlpha = aCmd->argDouble(1);

   gParms.reset();
   gParms.readSection("default");

   gParms.readSection("AlphaThree11");
   gParms.mHistoryFilterParms1.mAlphaAlpha = tAlpha;

   TestOne tTestOne;
   tTestOne.doRun3();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executePlot(Ris::CmdLineCmd* aCmd)
{
   char* tPlotRun1 = "python C:/Prime/AAA_NexGen2/Python_Plots/Dsp/plot_sample_run1.py";
   char* tPlotRun2 = "python C:/Prime/AAA_NexGen2/Python_Plots/Dsp/plot_sample_run2.py";
   char* tPlotRun3 = "python C:/Prime/AAA_NexGen2/Python_Plots/Dsp/plot_sample_run3.py";

   aCmd->setArgDefault(1,"2");
   int tPlotSelect = aCmd->argInt(1);

   char* tPlotCmd = 0;
   switch(tPlotSelect)
   {
      case 1: tPlotCmd = tPlotRun1 ; break;
      case 2: tPlotCmd = tPlotRun2 ; break;
      case 3: tPlotCmd = tPlotRun3 ; break;
      default: printf("PLOT NOT FOUND\n");
   }

   int tRet = Ris::doSystemCommand(tPlotCmd);
   Prn::print(0, "PLOT %d %s", tRet, tPlotCmd);
}

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

