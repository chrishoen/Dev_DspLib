#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>
#include <stdarg.h>

#include "risContainers2.h"
#include "risPortableCalls.h"
#include "dsp_functions.h"

#include "prnPrint.h"
#include "CmdLineExec.h"

#include "dsp_math.h"

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

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,45.0);

   double tAdeg = aCmd->argDouble(1);
   double tArad = dsp_rad(tAdeg);


   Prn::print(0, "%8.7f %8.7f",tAdeg,tArad);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "dsp_imin  %d",dsp_imin_n(3, 1,2,3));
   Prn::print(0, "dsp_imax  %d",dsp_imax_n(3, 1,2,3));

   double tX1 = 1.1;
   double tX2 = 2.2;
   double tX3 = 3.3;

   Prn::print(0, "dsp_fmin  %10.2f",dsp_fmin_n(3, tX1,tX2,tX3));
   Prn::print(0, "dsp_fmax  %10.2f",dsp_fmax_n(3, tX1,tX2,tX3));

   Prn::print(0, "dsp_fmax  %10.2f",dsp_fmin_n(3, 1.11,2.22,3.33));
   Prn::print(0, "dsp_fmax  %10.2f",dsp_fmax_n(3, 1.11,2.22,3.33));
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

