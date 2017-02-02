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
   if (aCmd->isCmd("GO3"))   executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))   executeGo4(aCmd);
   if (aCmd->isCmd("GO5"))   executeGo5(aCmd);
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
   aCmd->setArgDefault(1,11);
   int N = aCmd->argInt(1);
   int m = (N-3)/2;

   double tT = pow(2.0,double(2*m+1));

   printf("N,m %3d %3d $$ %10.6f\n",N,m,tT);
 
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

long long my_factorial(long long aN)
{
   // Guard.
   if (aN<=0) return 1; 

   long long tA = 1;

   for (long long i = 1; i <= aN; i++)
   {
      tA *= i;
   }
   return tA;
}

long long my_binomial2(long long aN, long long aK)
{
   // Guard.
   if (aK >  aN) return 0; 
   if (aK < 0) return 0; 
   if (aN < 0) return 0; 

   long long tA = 1;
   long long tF = 1;

   for (long long i = 1; i <= aK; i++)
   {
      tA *= (aN + 1 - i);
      tF *= i;
   }
   return tA/tF;
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,11);

   int N = aCmd->argInt(1);

   int m = (N-3)/2;
   int M = (N-1)/2;

   for (int k = 1; k <= M; k++)
   {

      long long tB1 = my_binomial2(2 * m, m - k + 1);
      long long tB2 = my_binomial2(2 * m, m - k - 1);

      printf("N,k,m %3d %3d %3d  $$ %lld $$ %3d %3d %3d\n",
         N, k, m, tB1- tB2,
         2*m,
         m-k+1,
         m-k-1);
   }
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,5);


   int tN = aCmd->argInt(1);

   long long tB = my_factorial(tN);

   printf("%5d $$ %lld\n",tN,tB);
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
   aCmd->setArgDefault(1,"run2");
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection(aCmd->argString(1));
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

   long long tB = dsp_binomial(tN,tK);

   Prn::print(0,"Binomial N,K = %2d %2d $ %lld",tN,tK,tB);


}


