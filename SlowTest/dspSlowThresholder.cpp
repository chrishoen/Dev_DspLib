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
   mAboveFlag = false;
   mLastAboveFlag = false;
   mChangeFlag = false;
   mErrorCount = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update the state.

void SlowThresholder::doUpdate(
   double aValue,           // Input
   bool&  aAboveFlag,       // Output
   bool&  aChangeFlag)      // Output
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Manage arguments.

   // Do this first.
   mCount++;

   // Store the input.
   mValue = aValue;

   // Set default outputs.
   aAboveFlag = false;
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
   // Calculate the logic variables.

   // Threshold the input value.
   mValueBelowLo = aValue <  tSignalThreshLo;
   mValueAboveHi = aValue >= tSignalThreshHi;

   // Put the threshold comparison results to the fuzzy alpha filters
   // and set the fuzzy variables according to the resulting filtered values.
   mFuzzyBelowLo.mX = mAlphaFilterBelowLo.put(mValueBelowLo);
   mFuzzyAboveHi.mX = mAlphaFilterAboveHi.put(mValueAboveHi);

   // Obtain crisp values from the fuzzy variables by thresholding them.
   mCrispBelowLo = (mFuzzyBelowLo & ~mFuzzyAboveHi).crisp(mP->mFuzzyToCrispThresh);
   mCrispAboveHi = (mFuzzyAboveHi & ~mFuzzyBelowLo).crisp(mP->mFuzzyToCrispThresh);

   // Guard. This condition should not happen.
   if (mCrispBelowLo && mCrispAboveHi)
   {
      
      mErrorCount++;
      Prn::print(Prn::View11, "ERROR101 %4d", mErrorCount);
      return;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Calculate the output variables.

   // Set the previous value of the above flag.
   mLastAboveFlag = mAboveFlag;

   // If the value is below then set the above flag false.
   if (mCrispBelowLo)
   {
      mAboveFlag = false;
   }

   // If the value is above then set the above flag true.
   if (mCrispAboveHi)
   {
      mAboveFlag = true;
   }

   // Set the change flag.
   mChangeFlag = mLastAboveFlag != mAboveFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write to the output variables.

}
     

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SlowThresholder::show()
{
   char tResult[20];
   if (mAboveFlag) strcpy(tResult, "above");
   else            strcpy(tResult, "below");

   char tString[200];
   sprintf(tString, "%4d $ %8.4f $ %1d %1d $ %6.4f %6.4f $ %1d %1d $ %s",
      mCount,
      mValue,
      mValueBelowLo,
      mValueAboveHi,
      mFuzzyBelowLo.mX,
      mFuzzyAboveHi.mX,
      mCrispBelowLo,
      mCrispAboveHi,
      tResult);

   if (mChangeFlag)
   {
      strcat(tString, " CHANGE");
   }
   
   Prn::print(Prn::View11, "%s", tString);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace