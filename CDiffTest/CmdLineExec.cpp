#include "stdafx.h"

#include <windows.h>
#include "risSystemCalls.h"
#include "CmdLineExec.h"
#include "Parms.h"
#include "TestOne.h"
#include "dspFIRCDiffCoeff.h"
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

   if (aCmd->isCmd("ALPHA"))    executeAlpha(aCmd);
   if (aCmd->isCmd("CDIFF"))    executeCDiff(aCmd);

   if (aCmd->isCmd("TEST1"))    executeTest1(aCmd);
   if (aCmd->isCmd("TEST2"))    executeTest2(aCmd);
   if (aCmd->isCmd("TEST3"))    executeTest3(aCmd);
   if (aCmd->isCmd("PLOT"))     executePlotA(aCmd);

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

void CmdLineExec::executeAlpha(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,"4");
   aCmd->setArgDefault(2,"3");
   int tFilterSelect = aCmd->argInt(1);
   int tGenSelect = aCmd->argInt(2);

   gParms.reset();
   gParms.readSection("default");
   switch(tFilterSelect)
   {
      case 1: gParms.readSection("AlphaOne1"); break;
      case 2: gParms.readSection("AlphaTwo1"); break;
      case 3: gParms.readSection("AlphaThree1"); break;
      case 4: gParms.readSection("AlphaAlpha1"); break;
      default: printf("SECTION NOT FOUND\n");
   }
   switch(tGenSelect)
   {
      case 1: gParms.readSection("GenSin1"); break;
      case 2: gParms.readSection("GenSin2"); break;
      case 3: gParms.readSection("GenStep1"); break;
      case 4: gParms.readSection("GenStep2"); break;
      default: printf("SECTION NOT FOUND\n");
   }

   TestOne tTestOne;
   tTestOne.doRun1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeCDiff(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,"1");
   aCmd->setArgDefault(2,"3");
   int tFilterSelect = aCmd->argInt(1);
   int tGenSelect = aCmd->argInt(2);

   gParms.reset();
   gParms.readSection("default");
   switch(tFilterSelect)
   {
      case 1: gParms.readSection("FIRCDiff1"); break;
      default: printf("SECTION NOT FOUND\n");
   }
   switch(tGenSelect)
   {
      case 1: gParms.readSection("GenSin1"); break;
      case 2: gParms.readSection("GenSin2"); break;
      case 3: gParms.readSection("GenStep1"); break;
      case 4: gParms.readSection("GenStep2"); break;
      default: printf("SECTION NOT FOUND\n");
   }

   TestOne tTestOne;
   tTestOne.doRun1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTest1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,"0.1");
   aCmd->setArgDefault(2,"2");
   double tAlpha = aCmd->argDouble(1);
   int tGenSelect = aCmd->argInt(2);

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

   gParms.readSection("AlphaOne1");
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
   aCmd->setArgDefault(2,"2");
   double tAlpha = aCmd->argDouble(1);
   int tGenSelect = aCmd->argInt(2);

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
   aCmd->setArgDefault(2,"2");
   double tAlpha = aCmd->argDouble(1);
   int tGenSelect = aCmd->argInt(2);

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

   gParms.readSection("AlphaThree11");
   gParms.mHistoryFilterParms1.mAlphaAlpha = tAlpha;

   TestOne tTestOne;
   tTestOne.doRun3();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executePlotA
(Ris::CmdLineCmd* aCmd)
{
   char* tPlotRun1 = "python C:/Prime/AAA_LinuxWriter/Python_Plots/Dsp/plot_alpha_alpha1.py";
   char* tPlotRun2 = "python C:/Prime/AAA_LinuxWriter/Python_Plots/Dsp/plot_alpha_alpha2.py";
   char* tPlotRun3 = "python C:/Prime/AAA_LinuxWriter/Python_Plots/Dsp/plot_alpha_alpha3.py";

   aCmd->setArgDefault(1,"1");
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
   Sleep(1000);
   SetForegroundWindow(GetConsoleWindow());
   Prn::print(0, "PLOT %d %s", tRet, tPlotCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 3);
   int tN = aCmd->argInt(1);
   int tM = (tN-1)/2;
   double tH = 1;
   double tC[100];
   double tB[100];
   for (int i = 0; i < 100; i++)
   {
      tC[i] = 99;
      tB[i] = 99;
   }

   Dsp::doCalcCoeffFirstDerivative_Holob(tN, tH, tC, tB);

   Prn::print(0, "C");
   for (int i = 0; i <= tM; i++)
   {
      Prn::print(0, "%2d %6.4f", i, tC[i]);
   }

   Prn::print(0, "B");
   for (int i = 0; i < tN; i++)
   {
      Prn::print(0, "%2d %6.4f", i, tB[i]);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   mCDiff.initialize(1);
   int tN = mCDiff.cN;
   int tM = mCDiff.cM;
   
   Prn::print(0, "C");
   for (int i = 0; i <= tM; i++)
   {
      Prn::print(0, "%2d %6.4f", i, mCDiff.mCArray[i]);
   }

   Prn::print(0, "B");
   for (int i = 0; i < tN; i++)
   {
      Prn::print(0, "%2d %6.4f", i, mCDiff.mB[i]);
   }
}


//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   mCDiff.initialize(1);
   for (int i = 0; i < aCmd->argInt(1); i++) 
   {
      mCDiff.put(1.2f);
   }
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

