#include "stdafx.h"

#include <random>

#include "Parms.h"
#include "DelayOne.h"

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

   if (aCmd->isCmd("Del1"))  executeDelay1(aCmd);
   if (aCmd->isCmd("Del2"))  executeDelay2(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDelay1(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("Delay1");

   DelayOne tDelayOne;
   tDelayOne.doDelay1();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDelay2(Ris::CmdLineCmd* aCmd)
{
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection("Delay2");

   DelayOne tDelayOne;
   tDelayOne.doDelay2();
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
   aCmd->setArgDefault(1,10);
   int tP = aCmd->argInt(1);

   printf("Forward\n");
   for (int i = 0; i < tP; i++)
   {
      printf("%2d",i);
   }
   printf("\n\n");

   printf("Backward\n");
   for (int i = tP-1; i >= 0; i--)
   {
      printf("%2d",i);
   }
   printf("\n\n");
 
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

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
   aCmd->setArgDefault(1,"delay1");
   gParms.reset();
   gParms.readSection("default");
   gParms.readSection(aCmd->argString(1));
   gParms.show();
}

