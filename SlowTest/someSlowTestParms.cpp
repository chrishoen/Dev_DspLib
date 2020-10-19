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
   mAlphaFilterStepTime = 0.0;
   mFuzzyToCrispThresh = 0.9f;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void SlowTestParms::expand()
{
   mTestThresholderParms.mAlphaFilterTs = mAlphaFilterTs;
   mTestThresholderParms.mAlphaFilterStepTime = mAlphaFilterStepTime;
   mTestThresholderParms.mFuzzyToCrispThresh = mFuzzyToCrispThresh;

   mThresholderParmsP2.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsP2.mAlphaFilterStepTime = mAlphaFilterStepTime;
   mThresholderParmsP1.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsP1.mAlphaFilterStepTime = mAlphaFilterStepTime;
   mThresholderParmsM1.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsM1.mAlphaFilterStepTime = mAlphaFilterStepTime;
   mThresholderParmsM2.mAlphaFilterTs = mAlphaFilterTs;
   mThresholderParmsM2.mAlphaFilterStepTime = mAlphaFilterStepTime;

   mThresholderParmsP2.mFuzzyToCrispThresh = mFuzzyToCrispThresh;
   mThresholderParmsP1.mFuzzyToCrispThresh = mFuzzyToCrispThresh;
   mThresholderParmsM1.mFuzzyToCrispThresh = mFuzzyToCrispThresh;
   mThresholderParmsM2.mFuzzyToCrispThresh = mFuzzyToCrispThresh;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace