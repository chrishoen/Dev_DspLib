//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define  _SlowTESTPARMS_CPP_
#include "dspSlowTestParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SlowTestParms::SlowTestParms()
{
   reset();
}

void SlowTestParms::reset()
{
   BaseClass::reset();
   BaseClass::setFilePath_RelativeToBaseDir("files/SlowTest_Parms.txt");

   mTimerPeriod = 0;
   mAlphaFilterTs = 0.0;
   mAlphaFilterTc = 0.0;
   mFuzzyToCrispThreshLo = 0.0;
   mFuzzyToCrispThreshHi = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void SlowTestParms::expand()
{
   mTestThresholderParms.mAlphaFilterTs = mAlphaFilterTs;
   mTestThresholderParms.mAlphaFilterTc = mAlphaFilterTc;
   mTestThresholderParms.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   mTestThresholderParms.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;

   mThresholderParmsM2.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsM2.mAlphaFilterTc = mAlphaFilterTc;
   mThresholderParmsM1.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsM1.mAlphaFilterTc = mAlphaFilterTc;
   mThresholderParmsP1.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsP1.mAlphaFilterTc = mAlphaFilterTc;
   mThresholderParmsP2.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsP2.mAlphaFilterTc = mAlphaFilterTc;

   mThresholderParmsM2.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   mThresholderParmsM2.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
   mThresholderParmsM1.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   mThresholderParmsM1.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
   mThresholderParmsP1.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   mThresholderParmsP1.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
   mThresholderParmsP2.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   mThresholderParmsP2.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SlowTestParms::show()
{
   printf("\n");
   printf("SlowTestParms************************************************ %s\n", mTargetSection);
   printf("TimerPeriod            %10d\n", mTimerPeriod);

   printf("\n");
   mTestThresholderParms.show("Test");

   printf("\n");
   mThresholderParmsM2.show("M2");
   mThresholderParmsM1.show("M1");
   mThresholderParmsP1.show("P1");
   mThresholderParmsP2.show("P2");
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SlowTestParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TimerPeriod"))           mTimerPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("AlphaFilterTs"))         mAlphaFilterTs = aCmd->argDouble(1);
   if (aCmd->isCmd("AlphaFilterTc"))         mAlphaFilterTc = aCmd->argDouble(1);
   if (aCmd->isCmd("FuzzyToCrispThreshLo"))  mFuzzyToCrispThreshLo = aCmd->argDouble(1);
   if (aCmd->isCmd("FuzzyToCrispThreshHi"))  mFuzzyToCrispThreshHi = aCmd->argDouble(1);

   if (aCmd->isCmd("TestThresholder"))   nestedPush(aCmd, &mTestThresholderParms);

   if (aCmd->isCmd("ThresholderM2"))     nestedPush(aCmd, &mThresholderParmsM2);
   if (aCmd->isCmd("ThresholderM1"))     nestedPush(aCmd, &mThresholderParmsM1);
   if (aCmd->isCmd("ThresholderP1"))     nestedPush(aCmd, &mThresholderParmsP1);
   if (aCmd->isCmd("ThresholderP2"))     nestedPush(aCmd, &mThresholderParmsP2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace