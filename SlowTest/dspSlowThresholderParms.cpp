//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspSlowThresholderParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SlowThresholderParms::SlowThresholderParms()
{
   reset();
}

void SlowThresholderParms::reset()
{
   mMode = 0;

   mAlphaFilterTs = 0.0;
   mAlphaFilterTc = 0.0;
   mFuzzyToCrispThresh = 0.0;
   mSignalThreshLo = 0.0;
   mSignalThreshHi = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set expanded member variables. This is called after the entire
// section of the command file has been processed.

void SlowThresholderParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SlowThresholderParms::show()
{
   printf("\n");
   printf("SlowThresholderParms*************************************BEGIN\n");

   printf("\n");
   printf("Mode                      %10d\n", mMode);
   printf("\n");

   printf("\n");
   printf("AlphaFilterTs             %10.4f\n", mAlphaFilterTs);
   printf("AlphaFilterTc             %10.4f\n", mAlphaFilterTc);
   printf("\n");

   printf("FuzzyToCrispThresh        %10.4f\n", mFuzzyToCrispThresh);
   printf("SignalThreshLo            %10.4f\n", mSignalThreshLo);
   printf("SignalThreshHi            %10.4f\n", mSignalThreshHi);

   printf("\n");
   printf("SlowThresholderParms*************************************END\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SlowThresholderParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("Mode"))              mMode = aCmd->argInt(1);

   if (aCmd->isCmd("AlphaFilterTs"))     mAlphaFilterTs = aCmd->argDouble(1);
   if (aCmd->isCmd("AlphaFilterTc"))     mAlphaFilterTc = aCmd->argDouble(1);

   if (aCmd->isCmd("FuzzyToCrispThresh"))    mFuzzyToCrispThresh = aCmd->argDouble(1);
   if (aCmd->isCmd("SignalThreshLo"))        mSignalThreshLo = aCmd->argDouble(1);
   if (aCmd->isCmd("SignalThreshHi"))        mSignalThreshHi = aCmd->argDouble(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace