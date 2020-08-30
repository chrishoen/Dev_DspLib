//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "someSlowTestParms.h"

#define  _SOMESLOWTESTPARMSFILE_CPP_
#include "someSlowTestParmsFile.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SlowTestParmsFile::SlowTestParmsFile()
{
   reset();
}

void SlowTestParmsFile::reset()
{
   BaseClass::reset();

   BaseClass::reset();
   if (Ris::portableIsWindows())
   {
      BaseClass::setFilePath("C:/aaa_prime/SlowTest/SlowTest_Parms.txt");
   }
   else
   {
      BaseClass::setFilePath_RelativeToBaseDir("files/SlowTest_Parms.txt");
   }

   mTestThresholderParmsWrapper.initialize(&gSlowTestParms.mTestThresholderParms);
   mThresholderParmsM2Wrapper.initialize(&gSlowTestParms.mThresholderParmsM2);
   mThresholderParmsM1Wrapper.initialize(&gSlowTestParms.mThresholderParmsM1);
   mThresholderParmsP1Wrapper.initialize(&gSlowTestParms.mThresholderParmsP1);
   mThresholderParmsP2Wrapper.initialize(&gSlowTestParms.mThresholderParmsP2);

   mTimerPeriod = 0;
   mTestMode = 0;
   mInitialValue = 0.0;
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

void SlowTestParmsFile::expand()
{
#if 0
   mTestThresholderParms.mAlphaFilterTs = mAlphaFilterTs;
   mTestThresholderParms.mAlphaFilterTc = mAlphaFilterTc;
   if (mTestThresholderParms.mFuzzyToCrispThreshLo == 0.0) mTestThresholderParms.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   if (mTestThresholderParms.mFuzzyToCrispThreshHi == 0.0) mTestThresholderParms.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;

   mThresholderParmsM2.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsM2.mAlphaFilterTc = mAlphaFilterTc;
   mThresholderParmsM1.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsM1.mAlphaFilterTc = mAlphaFilterTc;
   mThresholderParmsP1.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsP1.mAlphaFilterTc = mAlphaFilterTc;
   mThresholderParmsP2.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsP2.mAlphaFilterTc = mAlphaFilterTc;

   if (mThresholderParmsM2.mFuzzyToCrispThreshLo == 0.0) mThresholderParmsM2.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   if (mThresholderParmsM2.mFuzzyToCrispThreshHi == 0.0) mThresholderParmsM2.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
   if (mThresholderParmsM1.mFuzzyToCrispThreshLo == 0.0) mThresholderParmsM1.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   if (mThresholderParmsM1.mFuzzyToCrispThreshHi == 0.0) mThresholderParmsM1.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
   if (mThresholderParmsP1.mFuzzyToCrispThreshLo == 0.0) mThresholderParmsP1.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   if (mThresholderParmsP1.mFuzzyToCrispThreshHi == 0.0) mThresholderParmsP1.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
   if (mThresholderParmsP2.mFuzzyToCrispThreshLo == 0.0) mThresholderParmsP2.mFuzzyToCrispThreshLo = mFuzzyToCrispThreshLo;
   if (mThresholderParmsP2.mFuzzyToCrispThreshHi == 0.0) mThresholderParmsP2.mFuzzyToCrispThreshHi = mFuzzyToCrispThreshHi;
#endif
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SlowTestParmsFile::show()
{
   printf("\n");
   printf("SlowTestParmsFile************************************************ %s\n", mTargetSection);
   printf("TimerPeriod            %10d\n", mTimerPeriod);
   printf("TestMode               %10d\n", mTestMode);
   printf("InitialValue           %10.4f\n", mInitialValue);

   printf("\n");
   mTestThresholderParmsWrapper.show("Test");

   printf("\n");
   mThresholderParmsM2Wrapper.show("M2");
   mThresholderParmsM1Wrapper.show("M1");
   mThresholderParmsP1Wrapper.show("P1");
   mThresholderParmsP2Wrapper.show("P2");
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SlowTestParmsFile::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TimerPeriod"))           mTimerPeriod = aCmd->argInt(1);
   if (aCmd->isCmd("TestMode"))              mTestMode = aCmd->argInt(1);
   if (aCmd->isCmd("InitialValue"))          mInitialValue = aCmd->argDouble(1);

   if (aCmd->isCmd("AlphaFilterTs"))         mAlphaFilterTs = aCmd->argDouble(1);
   if (aCmd->isCmd("AlphaFilterTc"))         mAlphaFilterTc = aCmd->argDouble(1);
   if (aCmd->isCmd("FuzzyToCrispThreshLo"))  mFuzzyToCrispThreshLo = aCmd->argDouble(1);
   if (aCmd->isCmd("FuzzyToCrispThreshHi"))  mFuzzyToCrispThreshHi = aCmd->argDouble(1);

   if (aCmd->isCmd("TestThresholder"))   nestedPush(aCmd, &mTestThresholderParmsWrapper);

   if (aCmd->isCmd("ThresholderM2"))     nestedPush(aCmd, &mThresholderParmsM2Wrapper);
   if (aCmd->isCmd("ThresholderM1"))     nestedPush(aCmd, &mThresholderParmsM1Wrapper);
   if (aCmd->isCmd("ThresholderP1"))     nestedPush(aCmd, &mThresholderParmsP1Wrapper);
   if (aCmd->isCmd("ThresholderP2"))     nestedPush(aCmd, &mThresholderParmsP2Wrapper);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace