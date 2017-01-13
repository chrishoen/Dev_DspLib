/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dsp_math.h"
#include "dspStatistics.h"
#include "dspHistoryGenWiener.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryGenWienerParms::HistoryGenWienerParms()
{
   reset();
}

void HistoryGenWienerParms::reset()
{
   mDuration = 10.0;
   mFs = 1.0;
   mFc = 1.0;
   mEX = 0.0;
   mUX = 1.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute a command line in the section of the parms file that is specific
// to this object and set member variables accordingly. When an "End" is
// encountered, pop back out of the section and return control to its parent
// executive.

void HistoryGenWienerParms::execute(Ris::CmdLineCmd* aCmd)
{
   // Execute commands to read parameter members.
   if(aCmd->isCmd("Duration"          )) mDuration           = aCmd->argDouble(1);
   if(aCmd->isCmd("Fs"                )) mFs                 = aCmd->argDouble(1);
   if(aCmd->isCmd("Fc"                )) mFc                 = aCmd->argDouble(1);
   if(aCmd->isCmd("FilterOrder"       )) mFilterOrder        = aCmd->argInt(1);
   if(aCmd->isCmd("EX"                )) mEX                 = aCmd->argDouble(1);
   if(aCmd->isCmd("UX"                )) mUX                 = aCmd->argDouble(1);

   // Pop back out at the end.
   if(aCmd->isCmd("End"  ))  nestedPop(aCmd);
   if(aCmd->isCmd("}"    ))  nestedPop(aCmd);
}

void HistoryGenWienerParms::show(char* aLabel)
{
   printf("\n");
   printf("%-23s BEGIN\n", aLabel);

   printf("mDuration          %10.4f\n",mDuration);
   printf("mFs                %10.4f\n",mFs);
   printf("mFc                %10.4f\n",mFc);
   printf("mFilterOrder       %10d\n",  mFilterOrder);
   printf("mEX                %10.4f\n",mEX);
   printf("mUX                %10.4f\n",mUX);

   printf("%-25s END\n", aLabel);
   printf("\n");
}
   
}//namespace