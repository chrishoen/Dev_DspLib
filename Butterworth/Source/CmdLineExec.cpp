#include "stdafx.h"

#include "dspButterworthCo.h"

#include "CmdLineExec.h"

using namespace Dsp;

//******************************************************************************
// change101
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
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   int tN = 4;
   double tFs = 100.0;
   double tFc =   0.1;

   int tNa=0;
   int tNb=0;
   double tB[10];
   double tA[10];

   butterworthCoLP(tN,tFs,tFc,&tNb,&tNa,tB,tA);

    printf("Bco %d\n", tNb );
    for (int i = 0; i < tNb; i++)
    {
       printf("%1.15lf\n", tB[i]);
    }

    printf("Aco %d\n", tNa );
    for (int i = 0; i < tNa; i++)
    {
       printf("%1.15lf\n", tA[i]);
    }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   int tN = 4;
   double tFs = 100.0;
   double tFc1 =   0.25;
   double tFc2 =   1.00;

   int tNa=0;
   int tNb=0;
   double tB[10];
   double tA[10];

   butterworthCoBP(tN,tFs,tFc1,tFc2,&tNb,&tNa,tB,tA);

    printf("Bco %d\n", tNb );
    for (int i = 0; i < tNb; i++)
    {
       printf("%1.15lf\n", tB[i]);
    }

    printf("Aco %d\n", tNa );
    for (int i = 0; i < tNa; i++)
    {
       printf("%1.15lf\n", tA[i]);
    }
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

