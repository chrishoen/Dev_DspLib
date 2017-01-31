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
#include "dspHistoryGenTime.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryGenTimeParms::HistoryGenTimeParms()
{
   reset();
}

void HistoryGenTimeParms::reset()
{
   mDuration = 10.0;
   mFs = 1.0;
   mDuration = 10.0;
   mNumSamples = (int)(mDuration * mFs);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void HistoryGenTimeParms::show(char* aLabel)
{
   printf("\n");
   printf("%-23s BEGIN\n", aLabel);

   printf("mDuration          %10.4f\n",mDuration);
   printf("mFs                %10.4f\n",mFs);
   printf("mTs                %10.4f\n",mTs);

   printf("%-25s END\n", aLabel);
   printf("\n");
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute a command line in the section of the parms file that is specific
// to this object and set member variables accordingly. When an "End" is
// encountered, pop back out of the section and return control to its parent
// executive.

void HistoryGenTimeParms::execute(Ris::CmdLineCmd* aCmd)
{
   // Execute commands to read parameter members.
   if(aCmd->isCmd("Duration"          )) mDuration           = aCmd->argDouble(1);
   if(aCmd->isCmd("Fs"                )) mFs                 = aCmd->argDouble(1);

   // Pop back out at the end.
   if(aCmd->isCmd("End"  ))  nestedPop(aCmd);
   if(aCmd->isCmd("}"    ))  nestedPop(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void HistoryGenTimeParms::expand()
{
   mTs = 1.0 / mFs;
   mNumSamples = (int)(round(mDuration) * mFs);
}

}//namespace