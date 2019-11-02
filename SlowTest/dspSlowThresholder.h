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
   bool   mValueBelowLo;
   bool   mValueAboveHi;

   // Fuzzy boolean values slowed by alpha filters that are input  
   // the fast crisp boolean values 
   FuzzyBool mFuzzyBelowLo;
   FuzzyBool mFuzzyAboveHi;

   // Crisp boolean values updated at a fast rate.
   // True if the fuzzy boolean values are above a fuzzy threshold.
   bool mCrispBelowLo;
   bool mCrispAboveHi;

   // True if the input value is declared to be above thrshold. False if 
   // it is declared to be below threshold. This does not change if neither
   // condition is declared.
   bool mAboveHiFlag;

   // Previous value of the above.
   bool mLastAboveHiFlag;

   // True if the above flag has changed after an update.
   bool mChangeFlag;

   // True if first update after initialization.
   bool mFirstFlag;

   // Error counter.
   int mErrorCount;

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


