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
// This is a class that implments a slow thresholder. It addresses the problem
// of thresholding a noisy variable that varies over time.
// 
// It provides an initialization method that sets threshold and time constant
// parameters. It provides an update method that inputs a signal value and
// outputs a flag that indicates if the input is above or below threshold
// and it outputs a change flag.
// 
// It is based on the following logic:
//
// 1) Compare the input value to two different thresholds, a low threshold 
//    and a high threshold. Obtain two resulting boolean flags: the low flag
//    is true if the value is below the low threshold and the high flag is
//    true if the value is above the high threshold.
// 2) Feed the two flags into two alpha filters, one for low and one for high.
//    An alpha filter is a simple first order low pass filter that is used for
//    smoothing. The resulting smoothed threshold comparisons will then have
//    values that vary between 0.0 and 1.0. If the input value is below the
//    low hreshold for a long time, then the low alpha filter will output
//    a 1.0 and the high alpha filter will output a 0.0. If the input value
//    is above the high threshold for a long time, then the low  alpha filter
//    will output a 0.0 and the high alpha filter will output a 1.0. If the
//    input value is noisy and varies around the range of the thresholds then
//    the alpha filters will output values that are between 0.0 and 1.0.
// 3) Feed the outputs of the two alpha filters into two fuzzy logic variables:
//    one for below low threshold and one for above high threshold. Evaluate
//    the fuzzy logic variables to determine an output declaration of either
//    below threshold low, above threshold high, or no declaration. Also 
//    provide a change flag to signify if the output has changed.

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

   // Update counter.
   int mCount;

   // Input value.
   double mValue;

   // Threshold comparison variables. The low variable is true if the input
   // value is below the low threshold. The high variable is true if the
   // input value is above the high threshold.
   bool   mValueBelowLo;
   bool   mValueAboveHi;

   // Alpha filters. These are input the threshold comparison variables.
   // They output values bewteen 0.0 and 1.0.
   Dsp::Filter::AlphaOne mAlphaFilterBelowLo;
   Dsp::Filter::AlphaOne mAlphaFilterAboveHi;

   // Fuzzy boolean variables. These are set from the outputs of the alpha
   // filters. The low one maintains a fuzzy logic value that inidcates
   // if the input value is below the low threshold. The high one maintains
   // a fuzzy logic value that indicates if the input value is above the
   // high threshold.
   FuzzyBool mFuzzyBelowLo;
   FuzzyBool mFuzzyAboveHi;

   // Crisp boolean variables. These are set by thresholding the fuzzy
   // boolean variables. The low variable is true if it is declared that
   // the input value is below the low threshold. The high variable is
   // true if it is declared that the input value is above the high
   // threshold. 
   bool mCrispBelowLo;
   bool mCrispAboveHi;

   // True if the input value is declared to be above thrshold. False if 
   // it is declared to be below threshold. This does not change if neither
   // condition is declared.
   bool mAboveFlag;

   // Previous value of the above.
   bool mLastAboveFlag;

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
      double aValue,           // Input
      bool&  aAboveFlag,       // Output
      bool&  aChangeFlag);     // Output

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


