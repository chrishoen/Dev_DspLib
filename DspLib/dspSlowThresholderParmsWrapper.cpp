//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspSlowThresholderParmsWrapper.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SlowThresholderParmsWrapper::SlowThresholderParmsWrapper()
{
   mP = 0;
}

SlowThresholderParmsWrapper::SlowThresholderParmsWrapper(SlowThresholderParms* aParms)
{
   initialize(aParms);
}

void SlowThresholderParmsWrapper::initialize(SlowThresholderParms* aParms)
{
   mP = aParms;
   reset();
}

void SlowThresholderParmsWrapper::reset()
{
   mP->reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set expanded member variables. This is called after the entire
// section of the command file has been processed.

void SlowThresholderParmsWrapper::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SlowThresholderParmsWrapper::show(const char* aLabel)
{
   printf("\n");
   printf("SlowThresholderParmsWrapper************************************* %s\n",aLabel);

   printf("\n");
   printf("AlphaFilterTs             %10.4f\n", mP->mAlphaFilterTs);
   printf("AlphaFilterTc             %10.4f\n", mP->mAlphaFilterTc);
   printf("FuzzyToCrispThresh        %10.4f\n", mP->mFuzzyToCrispThresh);
   printf("ValueThreshLo             %10.4f\n", mP->mValueThreshLo);
   printf("ValueThreshHi             %10.4f\n", mP->mValueThreshHi);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SlowThresholderParmsWrapper::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("AlphaFilterTs"))     mP->mAlphaFilterTs = aCmd->argFloat(1);
   if (aCmd->isCmd("AlphaFilterTc"))     mP->mAlphaFilterTc = aCmd->argFloat(1);

   if (aCmd->isCmd("FuzzyToCrispThresh"))    mP->mFuzzyToCrispThresh = aCmd->argFloat(1);
   if (aCmd->isCmd("ValueThreshLo"))         mP->mValueThreshLo = aCmd->argFloat(1);
   if (aCmd->isCmd("ValueThreshHi"))         mP->mValueThreshHi = aCmd->argFloat(1);

   // Pop back out at the end.
   if (aCmd->isCmd("}"))  nestedPop(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace