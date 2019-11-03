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
   mAlphaFilterTs = 0.0;
   mAlphaFilterTc = 0.0;
   mFuzzyToCrispThreshLo = 0.0;
   mFuzzyToCrispThreshHi = 0.0;
   mValueThreshLo = 0.0;
   mValueThreshHi = 0.0;
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

void SlowThresholderParms::show(const char* aLabel)
{
   printf("\n");
   printf("SlowThresholderParms************************************* %s\n",aLabel);

   printf("\n");
   printf("AlphaFilterTs             %10.4f\n", mAlphaFilterTs);
   printf("AlphaFilterTc             %10.4f\n", mAlphaFilterTc);
   printf("FuzzyToCrispThreshLo      %10.4f\n", mFuzzyToCrispThreshLo);
   printf("FuzzyToCrispThreshHi      %10.4f\n", mFuzzyToCrispThreshHi);
   printf("ValueThreshLo             %10.4f\n", mValueThreshLo);
   printf("ValueThreshHi             %10.4f\n", mValueThreshHi);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SlowThresholderParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("AlphaFilterTs"))     mAlphaFilterTs = aCmd->argDouble(1);
   if (aCmd->isCmd("AlphaFilterTc"))     mAlphaFilterTc = aCmd->argDouble(1);

   if (aCmd->isCmd("FuzzyToCrispThreshLo"))  mFuzzyToCrispThreshLo = aCmd->argDouble(1);
   if (aCmd->isCmd("FuzzyToCrispThreshHi"))  mFuzzyToCrispThreshHi = aCmd->argDouble(1);
   if (aCmd->isCmd("ValueThreshLo"))         mValueThreshLo = aCmd->argDouble(1);
   if (aCmd->isCmd("ValueThreshHi"))         mValueThreshHi = aCmd->argDouble(1);

   // Pop back out at the end.
   if (aCmd->isCmd("}"))  nestedPop(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace