#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>

#include "risContainers2.h"

#include "prnPrint.h"
#include "dspIntegrate.h"
#include "CmdLineExec.h"

using namespace std;

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

double function1(double aX1)
{
   return aX1*aX1;
}

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   double tY = Dsp::integrate1(function1,100000,0.0,4.0);
   Prn::print(0, "%8.6f", tY);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

double function2(double aX1,double aX2)
{
   return 4.0*aX1*aX1 + 5.0*aX2*aX2*aX2;
}

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   double tY = Dsp::integrate2(function2,1000,1.0,4.0,2.0,6.0);
   Prn::print(0, "%8.6f", tY);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,0.99);

   double tC = aCmd->argDouble(1);
   double tX = (1.0 + tC)/2.0;

   Prn::print(0, "%8.7f %8.7f",tC,tX);
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

