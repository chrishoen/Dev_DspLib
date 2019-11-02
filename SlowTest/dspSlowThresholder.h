#pragma once

/*==============================================================================
Dsp library: slow thresholder.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspFilterAlpha.h"

#include "dspFuzzyBool.h"
#include "dspSlowThresholderParms.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a simulator synthetic image generator.

class SlowThresholder
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Parameters.
   SlowThresholderParms* mP;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Fuzzy alpha filters.
   Dsp::Filter::AlphaOne mAlphaFilterBelowLo;
   Dsp::Filter::AlphaOne mAlphaFilterAboveHi;

   // Update counter.
   int mCount;

   // Input value.
   double mValue;

   // Crisp boolean values updated at a fast rate.
   // True if the signal threshold comparion test is pass.
   bool   mFastCrispBelowLo;
   bool   mFastCrispAboveHi;

   // Previous values for the above.
   bool   mLastFastCrispBelowLo;
   bool   mLastFastCrispAboveHi;

   // Fuzzy boolean values slowed by alpha filters that are input  
   // the fast crisp boolean values 
   FuzzyBool mSlowFuzzyBelowLo;
   FuzzyBool mSlowFuzzyAboveHi;

   // Slow crisp boolean value obtained by thresholding the slow fuzzy 
   // boolean values.
   bool   mSlowCrispAboveHi;

   // If true then first update.
   bool mFirstFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SlowThresholder();
  ~SlowThresholder();
   SlowThresholder(SlowThresholderParms* aParms);
   void initialize(SlowThresholderParms* aParms);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Update the state.
   void doUpdate(
      double   aValue,           // Input
      bool&    aPass,            // Output
      bool&    aChangeFlag);     // Output

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show.
   void show();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


