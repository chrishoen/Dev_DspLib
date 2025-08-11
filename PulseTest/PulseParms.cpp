//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnPaths.h"

#define  _PULSEPARMS_CPP_
#include "PulseParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

PulseParms::PulseParms()
{
   resetVars();
}

void PulseParms::reset()
{
   BaseClass::reset();
   BaseClass::setFilePath(Cmn::get_files_filepath("Pulse_Parms.txt"));
   resetVars();
}

void PulseParms::resetVars()
{
   mFilterDT = 0;
   mFuzzyStepTime = 0;
   mFuzzyCrisp = 0;

   // Sliding sum parameters.
   mBoundCountMax = 0;
   mBoundCountMin = 0;
   mSlidingSumHigh = 0;
   mSlidingSumLow = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void PulseParms::show()
{
   printf("\n");
   printf("PulseParms************************************************ %s\n", mTargetSection);

   printf("\n");

   printf("FilterDT                     %-10.4f\n",  mFilterDT);
   printf("FuzzyStepTime                %-10.4f\n",  mFuzzyStepTime);
   printf("FuzzyCrisp                   %-10.4f\n",  mFuzzyCrisp);
   printf("BoundCountMax                %-10d\n",    mBoundCountMax);
   printf("BoundCountMin                %-10d\n",    mBoundCountMin);
   printf("SlidingSumHigh               %-10d\n",    mSlidingSumHigh);
   printf("SlidingSumLow                %-10d\n",    mSlidingSumLow);
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void PulseParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("FilterDT"))             mFilterDT = aCmd->argDouble(1);
   if (aCmd->isCmd("FuzzyStepTime"))        mFuzzyStepTime = aCmd->argDouble(1);
   if (aCmd->isCmd("FuzzyCrisp"))           mFuzzyCrisp = aCmd->argDouble(1);

   if (aCmd->isCmd("BoundCountMax"))        mBoundCountMax = aCmd->argInt(1);
   if (aCmd->isCmd("BoundCountMin"))        mBoundCountMin = aCmd->argInt(1);
   if (aCmd->isCmd("SlidingSumHigh"))       mSlidingSumHigh = aCmd->argInt(1);
   if (aCmd->isCmd("SlidingSumLow"))        mSlidingSumLow = aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void PulseParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
