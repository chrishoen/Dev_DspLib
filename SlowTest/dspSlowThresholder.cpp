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
   mFAFilter1AboveHi.initializeFromTc(mP->mFAFTs, mP->mFAFTc);
   mFAFilter1BelowLo.initializeFromTc(mP->mFAFTs, mP->mFAFTc);

   // Initialize variables.
   mCount = 0;
   mValue = 0.0;
   mFirstFlag = true;

   mFastCrisp1BelowLo = false;
   mFastCrisp1AboveHi = false;

   mLastFastCrisp1BelowLo = false;
   mLastFastCrisp1AboveHi = false;

   mSlowFuzzy1BelowLo = 0.0;
   mSlowFuzzy1AboveHi = 0.0;

   mSlowCrisp1AboveHi = false;
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
   double tSignalThresh1Lo = 0.0;
   double tSignalThresh1Hi = 0.0;

   // Test if first update.
   if (mFirstFlag)
   {
      // Do this first.
      mFirstFlag = false;

      // Calculate thresholds for first compare as the average of the
      // low and high signal thresholds.
      tSignalThresh1Lo = (mP->mSignalThresh1Hi + mP->mSignalThresh1Lo) / 2.0;
      tSignalThresh1Hi = tSignalThresh1Lo;
   }
   else
   {
      // Use thresholds from the parms.
      tSignalThresh1Lo = mP->mSignalThresh1Lo;
      tSignalThresh1Hi = mP->mSignalThresh1Hi;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Calculate.

   // Set the fast crisp variables according to the thresholds.
   mFastCrisp1BelowLo = aValue < tSignalThresh1Lo;
   mFastCrisp1AboveHi = aValue >= tSignalThresh1Hi;

   // Put the fast crisp variables to the fuzzy alpha filters and get
   // the slow fuzzy variables from the resulting filtered values.
   mSlowFuzzy1BelowLo = mFAFilter1BelowLo.put(mFastCrisp1BelowLo);
   mSlowFuzzy1AboveHi = mFAFilter1AboveHi.put(mFastCrisp1AboveHi);

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
   Prn::print(Prn::View11, "%4d $ %8.4f $ %1d %1d $ %6.4f %6.4f",
      mCount,
      mValue,
      mFastCrisp1BelowLo,
      mFastCrisp1AboveHi,
      mSlowFuzzy1BelowLo,
      mSlowFuzzy1AboveHi);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace