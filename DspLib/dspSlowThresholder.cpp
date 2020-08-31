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
// Constructor.

SlowThresholder::SlowThresholder()
{
   mP = 0;
}

SlowThresholder::SlowThresholder(SlowThresholderParms* aParms)
{
   initialize(aParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

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
// Update the state. The input is the value that is to be thresholded.
// The output above flag is true if the input has been declared to be
// above threshold and it is false if it has been declared to be below
// threshold. The change flag is true if the output above flag is different
// from its previous value.

void SlowThresholder::doUpdate(
   float aValue,           // Input
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
   float tValueThreshLo = 0.0;
   float tValueThreshHi = 0.0;

   // Test the first update flag.
   if (mFirstFlag)
   {
      // This is the first update.

      // Calculate thresholds for first compare as the average of the
      // low and high signal thresholds.
      tValueThreshLo = (mP->mValueThreshHi + mP->mValueThreshLo) / 2.0f;
      tValueThreshHi = tValueThreshLo;
   }
   else
   {
      // This is not the first update.

      // Use thresholds from the parms.
      tValueThreshLo = mP->mValueThreshLo;
      tValueThreshHi = mP->mValueThreshHi;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Calculate the logic variables.

   // Threshold the input value.
   mValueBelowLo = aValue <  tValueThreshLo;
   mValueAboveHi = aValue >= tValueThreshHi;

   // Put the threshold comparison results to the fuzzy alpha filters
   // and set the fuzzy variables according to the resulting filtered values.
   mFuzzyBelowLo.mX = mAlphaFilterBelowLo.put(mValueBelowLo);
   mFuzzyAboveHi.mX = mAlphaFilterAboveHi.put(mValueAboveHi);
   
   // Obtain the threshold comparison confidence.
   mFuzzyConfidence = mFuzzyBelowLo || mFuzzyAboveHi;

   // Obtain crisp values from the fuzzy variables by thresholding them.
   mCrispBelowLo = (mFuzzyBelowLo && !mFuzzyAboveHi).crisp(mP->mFuzzyToCrispThreshLo);
   mCrispAboveHi = (mFuzzyAboveHi && !mFuzzyBelowLo).crisp(mP->mFuzzyToCrispThreshHi);

   // Guard. This condition should not happen.
   if (mCrispBelowLo && mCrispAboveHi)
   {
      mErrorCount++;
      printf("ERROR101 %4d\n", mErrorCount);
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
   mChangeFlag = (mLastAboveFlag != mAboveFlag) || mFirstFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write to the output variables.

   // Do this last.
   mFirstFlag = false;

   // Done.
   aAboveFlag = mAboveFlag;
   aChangeFlag = mChangeFlag;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return a string that can be used for a show.

char* SlowThresholder::asShowString(char* aBuffer)
{
   char tResult[20];
   if (mAboveFlag) strcpy(tResult, "above");
   else            strcpy(tResult, "below");

   sprintf(aBuffer, "%4d $ %8.4f $ %1d %1d $ %6.4f %6.4f $ %1d %1d $ %s",
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
      strcat(aBuffer, " CHANGE");
   }
  
   return aBuffer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace