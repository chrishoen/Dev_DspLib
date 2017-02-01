#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "prnPrint.h"
#include "CmdLineExec.h"
#include "Parms.h"
#include "dspSignalGen.h"
#include "dsp_functions.h"
#include "TestOne.h"

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
   if (aCmd->isCmd("Parms")) executeParms(aCmd);
   if (aCmd->isCmd("Bin"))   executeBin(aCmd);

   if (aCmd->isCmd("RUN1"))  executeRun1(aCmd);
   if (aCmd->isCmd("RUN2"))  executeRun2(aCmd);
   if (aCmd->isCmd("RUN3"))  executeRun3(aCmd);
   if (aCmd->isCmd("RUN4"))  executeRun4(aCmd);
   if (aCmd->isCmd("RUN5"))  executeRun5(aCmd);
   if (aCmd->isCmd("RUN6"))  executeRun6(aCmd);
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

void CmdLineExec::executeRun2(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run1");

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
   gParms.readSection("run1");

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
   gParms.readSection("run1");

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
   gParms.readSection("run1");

   TestOne tTestOne;
   tTestOne.doRun5();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeRun6(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,10);
   aCmd->setArgDefault(2,7);
   int tP = aCmd->argInt(1);
   int tN = aCmd->argInt(2);
   int tM = (tN-1)/2;

   printf("P,N,M %3d %3d %3d\n\n",tP,tN,tN);

   for (int i = 0; i < tP; i++)
   {
      printf("%3d  $$ ", i);
      for (int k = 1; k <= tM; k++)
      {
         int iB = dsp_imax(i - k,0);
         int iF = dsp_imin(i + k,tP-1);
         printf("[%3d](%3d,%3d) ", k,iB,iF);
      }
      printf("\n");
   }

}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,4);
   int aN = aCmd->argInt(1);

   int tA = 2;
   for (int i=1;i<=aN-1;i++) tA *= 2;

   printf("%5d %5d\n",aN,tA);
 
}

//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("run1");
   gParms.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeBin(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,2);
   aCmd->setArgDefault(2,3);

   int tN = aCmd->argInt(1);
   int tK = aCmd->argInt(2);

   int tB = dsp_binomial(tN,tK);

   Prn::print(0,"Binomial N,K = %2d %2d $ %d",tN,tK,tB);


}


