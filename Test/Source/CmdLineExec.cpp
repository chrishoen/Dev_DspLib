#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <atomic>
#include <stdarg.h>

#include "risContainers2.h"
#include "risPortableCalls.h"

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
   char tFilePath[200];

   strcpy(tFilePath, Ris::portableGetCurrentWorkingDir());
   strcat(tFilePath, "..\\..\\Files\\RandomMotionSettings.txt");
   Prn::print(0, "%s",tFilePath);
   
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

int dsp_imin(int n, ...)
{
    va_list ap;
    int sum = 0;

    va_start(ap, n);
    for (int i=0; i<n; i++)
        sum += va_arg(ap, int);
    va_end(ap);
    return sum;
}

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   int sum = dsp_imin(3,1,2,3);
   Prn::print(0, " summate %d",sum);
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

