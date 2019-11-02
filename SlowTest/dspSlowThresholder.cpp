/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspSlowThresholder.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Infastruccture.

SlowThresholder::SlowThresholder()
{
   mP = 0;
}

SlowThresholder::~SlowThresholder()
{
}

SlowThresholder::SlowThresholder(SlowThresholderParms* aParms)
{
   initialize(aParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void SlowThresholder::initialize(SlowThresholderParms* aParms)
{
   // Store parms.
   mP = aParms;

   // Initialize filters.
   mAlphaFilterAboveHi.initializeFromTc(mP->mAlphaFilterTs, mP->mAlphaFilterTc);
   mAlphaFilterBelowLo.initializeFromTc(mP->mAlphaFilterTs, mP->mAlphaFilterTc);

   // Initialize variables.
   mCount = 0;
   mValue = 0.0;
   mFirstFlag = true;

   mValueBelowLo = false;
   mValueAboveHi = false;
   mCrispBelowLo = false;
   mCrispAboveHi = false;
   mAboveHiFlag = false;
   mLastAboveHiFlag = false;
   mChangeFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update the state.

void SlowThresholder::doUpdate(
   double aValue,           // Input
   bool&  aPass,            // Output
   bool&  aChangeFlag)      // Output
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Manage arguments.

   // Store the input.
   mValue = aValue;

   // Set default outputs.
   aPass = false;
   aChangeFlag = false;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Obtain thresholds.

   // Local threshold variables.
   double tSignalThreshLo = 0.0;
   double tSignalThreshHi = 0.0;

   // Test if first update.
   if (mFirstFlag)
   {
      // Do this first.
      mFirstFlag = false;

      // Calculate thresholds for first compare as the average of the
      // low and high signal thresholds.
      tSignalThreshLo = (mP->mSignalThreshHi + mP->mSignalThreshLo) / 2.0;
      tSignalThreshHi = tSignalThreshLo;
   }
   else
   {
      // Use thresholds from the parms.
      tSignalThreshLo = mP->mSignalThreshLo;
      tSignalThreshHi = mP->mSignalThreshHi;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Calculate.

   // Compare the input value with the thresholds.
   mValueBelowLo = aValue < tSignalThreshLo;
   mValueAboveHi = aValue >= tSignalThreshHi;

   // Put the threshold comparison results to the fuzzy alpha filters
   // and get the fuzzy variables from the resulting filtered values.
   mFuzzyBelowLo.mX = mAlphaFilterBelowLo.put(mValueBelowLo);
   mFuzzyAboveHi.mX = mAlphaFilterAboveHi.put(mValueAboveHi);

   mCrispBelowLo = (mFuzzyBelowLo & ~mFuzzyAboveHi).crisp(mP->mFuzzyToCrispThresh);
   mCrispAboveHi = (mFuzzyAboveHi & ~mFuzzyBelowLo).crisp(mP->mFuzzyToCrispThresh);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Set outputs.

   mCount++;
}
     

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SlowThresholder::show()
{
   Prn::print(Prn::View11, "%4d $ %8.4f $ %1d %1d $ %6.4f %6.4f $ %1d %1d",
      mCount,
      mValue,
      mValueBelowLo,
      mValueAboveHi,
      mFuzzyBelowLo.mX,
      mFuzzyAboveHi.mX,
      mCrispBelowLo,
      mCrispAboveHi);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace