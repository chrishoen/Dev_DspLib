//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define  _SOMESLOWTESTPARMS_CPP_
#include "someSlowTestParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
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
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace