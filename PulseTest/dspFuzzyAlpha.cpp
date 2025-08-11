/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspFuzzyAlpha.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

FuzzyAlpha::FuzzyAlpha()
{
   resetVars();
}

void FuzzyAlpha::resetVars()
{
   mCrispThresh = 0;
   mFuzzy.mX = 0;
   mConditionFlag = false;
}

void FuzzyAlpha::initialize(double aTs, double aStepTime, double aCrispThresh)
{
   resetVars();
   mAlphaFilter.initializeFromStep(aTs, aStepTime);
   mCrispThresh = (float)aCrispThresh;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update the state. The input is a boolean. It is input to the alpha 
// filter. The fuzzy variable is set from the output of the alpha filter.
// Return the crisp value of the fuzzy variable.
bool FuzzyAlpha::doUpdate(bool aValue)
{
   // Put the input to the filter and set the fuzzy variable from the output
   // of the filter.
   mFuzzy = mAlphaFilter.putBool(aValue);
   // Crispify the fuzzy variable into the flag.
   mConditionFlag = mFuzzy.crisp(mCrispThresh);
   // Return the crisped flag.
   return mConditionFlag;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace