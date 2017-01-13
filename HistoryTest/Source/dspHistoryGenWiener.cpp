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

HistoryGenWiener::HistoryGenWiener()
{
   reset();
}

void HistoryGenWiener::reset()
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

// Execute each command in the 

void HistoryGenWiener::execute(Ris::CmdLineCmd* aCmd)
{
   // Execute commands to read parameter members.
   if(aCmd->isCmd("Duration"          )) mDuration           = aCmd->argDouble(1);
   if(aCmd->isCmd("Fs"                )) mFs                 = aCmd->argDouble(1);
   if(aCmd->isCmd("Fc"                )) mFc                 = aCmd->argDouble(1);
   if(aCmd->isCmd("EX"                )) mEX                 = aCmd->argDouble(1);
   if(aCmd->isCmd("UX"                )) mUX                 = aCmd->argDouble(1);

   // Pop back out at the end.
   if(aCmd->isCmd("End"  ))  nestedPop(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the signal history according to the parameters.

void HistoryGenWiener::generate(History& aHistory)
{
}
   
}//namespace