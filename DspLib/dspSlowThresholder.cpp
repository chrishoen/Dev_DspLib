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
   mMode = 0;
   mP = 0;
}

SlowThresholder::SlowThresholder(SlowThresholderParms* aParms)
{
   mMode = 0;
   initialize(aParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void SlowThresholder::initializeForSym(SlowThresholderParms* aParms)
{
   mMode = cMode_Sym;
   initialize(aParms);
}

void SlowThresholder::initializeForASymHi(SlowThresholderParms* aParms)
{
   mMode = cMode_ASymHi;
   initialize(aParms);
}

void SlowThresholder::initializeForASymLo(SlowThresholderParms* aParms)
{
   mMode = cMode_ASymLo;
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
   mAlphaFilterAboveHi.initializeFromStep(
      mP->mAlphaFilterTs, 
      mP->mAlphaFilterStepTime,
      mP->mFuzzyToCrispThresh);
   mAlphaFilterBelowLo.initializeFromStep(
      mP->mAlphaFilterTs,
      mP->mAlphaFilterStepTime,
      mP->mFuzzyToCrispThresh);


   // Initialize variables.
   mCount = 0;
   mValue = 0.0;
   mFirstFlag = true;

   mValueAboveHi = false;
   mValueBelowLo = false;
   mCrispAboveHi = false;
   mCrispBelowLo = false;
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
   float  aValue,           // Input
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

   // Test the first update flag.
   if (mFirstFlag)
   {
      mFirstFlag = false;
      mAboveFlag = aValue >= mP->mThresh;
   }

   // Calculate thresholds.
   switch (mMode)
   {
   case cMode_Sym:
      if (mAboveFlag)
      {
         mThreshHi = mP->mThresh;
         mThreshLo = mP->mThresh - mP->mThreshDelta;
      }
      else
      {
         mThreshHi = mP->mThresh + mP->mThreshDelta;
         mThreshLo = mP->mThresh;
      }
      break;
   case cMode_ASymHi:
      mThreshHi = mP->mThresh;
      mThreshLo = mP->mThresh - mP->mThreshDelta;
      break;
   case cMode_ASymLo:
      mThreshHi = mP->mThresh + mP->mThreshDelta;
      mThreshLo = mP->mThresh;
      break;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Calculate the logic variables.

   // Threshold the input value.
   mValueAboveHi = aValue >= mThreshHi;
   mValueBelowLo = aValue <  mThreshLo;

   // Put the threshold comparison results to the fuzzy alpha filters
   // and set the fuzzy variables according to the resulting filtered values.
   mFuzzyAboveHi.mX = mAlphaFilterAboveHi.put(mValueAboveHi);
   mFuzzyBelowLo.mX = mAlphaFilterBelowLo.put(mValueBelowLo);

   // Obtain the threshold comparison confidence.
   mFuzzyConfidence = mFuzzyBelowLo || mFuzzyAboveHi;

   // Obtain crisp values from the fuzzy variables by thresholding them.
   mCrispAboveHi = (mFuzzyAboveHi && !mFuzzyBelowLo).crisp(mP->mFuzzyToCrispThresh);
   mCrispBelowLo = (mFuzzyBelowLo && !mFuzzyAboveHi).crisp(mP->mFuzzyToCrispThresh);

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

   sprintf(aBuffer, "\
%4d  \
V %8.3f  \
T %6.3f %6.3f  \
A %1d %1d  \
F %6.3f %6.3f  \
C %1d %1d  \
R %s",
      mCount,
      mValue,
      mThreshHi,
      mThreshLo,
      mValueAboveHi,
      mValueBelowLo,
      mFuzzyAboveHi.mX,
      mFuzzyBelowLo.mX,
      mCrispAboveHi,
      mCrispBelowLo,
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