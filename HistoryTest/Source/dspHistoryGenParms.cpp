//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "my_functions.h"
#include "risCmdLineFile.h"
#include "risPortableCalls.h"

#include "dspHistoryGenParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

HistoryGenParms::HistoryGenParms()
{
   reset();
}

void HistoryGenParms::reset()
{
   BaseClass::reset();

   mDuration = 10.0;
   mFs = 1.0;
   mFc = 1.0;
   mEX = 0.0;
   mUX = 1.0;
   mFilterOrder = 4;

   mTs = 1.0 / mFs;
   mMaxSamples = (int)(mDuration * mFs);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void HistoryGenParms::show(char* aLabel)
{
   printf("HistoryGenParms ******** BEGIN %s\n", aLabel);

   printf("Duration           %10.4f\n", mDuration);
   printf("Fs                 %10.4f\n", mFs);
   printf("Fc                 %10.4f\n", mFc);
   printf("FilterOrder        %10d\n", mFilterOrder);
   printf("EX                 %10.4f\n", mEX);
   printf("UX                 %10.4f\n", mUX);

   printf("HistoryGenParms ******** END %s\n", aLabel);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void HistoryGenParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("Duration")) mDuration = aCmd->argDouble(1);
   if (aCmd->isCmd("Fs")) mFs = aCmd->argDouble(1);
   if (aCmd->isCmd("Fc")) mFc = aCmd->argDouble(1);
   if (aCmd->isCmd("EX")) mEX = aCmd->argDouble(1);
   if (aCmd->isCmd("UX")) mUX = aCmd->argDouble(1);

   if (aCmd->isCmd("FilterOrder")) mFilterOrder = aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void HistoryGenParms::expand()
{
   mTs = 1.0 / mFs;
   mMaxSamples = (int)(round(mDuration) * mFs);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace