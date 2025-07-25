#pragma once

/*==============================================================================
Dsp library: slow thresholder.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspFilterAlphaOne.h"
#include "dspFuzzyBool.h"
#include "dspSlowThresholderParms.h"

namespace Dsp
{

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
// 4) For the first update after initialization: calculate an initial
//    threshold as the average of the low theshold and the high threshold.
//    Compare the first input value with the initial threshold and declare
//    either below threshold or above threshold and set all variables 
//    accordingly.
//

class SlowThresholder
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // Modes.
   static const int cMode_Sym    = 0;   // symmetrical 
   static const int cMode_ASymHi = 2;   // asymmetrical high
   static const int cMode_ASymLo = 1;   // asymmetrical low

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Parameters.
   SlowThresholderParms mParms;
   SlowThresholderParms* mP;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Mode.
   int mMode;

   // Input value.
   float mValue;

   // Threshold variables.
   float mThreshHi;
   float mThreshLo;

   // Threshold comparison variables. The low variable is true if the input
   // value is below the low threshold. The high variable is true if the
   // input value is above the high threshold.
   bool mValueAboveHi;
   bool mValueBelowLo;

   // Alpha filters. These are input the threshold comparison variables.
   // They output values bewteen 0.0 and 1.0.
   Dsp::Filter::AlphaOne<float> mAlphaFilterAboveHi;
   Dsp::Filter::AlphaOne<float> mAlphaFilterBelowLo;

   // Fuzzy boolean variables. These are set from the outputs of the alpha
   // filters. The low one has a fuzzy logic value that indicates if the
   // input value is below the low threshold. The high one has a fuzzy
   // logic value that indicates if the input value is above the high 
   // threshold.
   FuzzyBool<float> mFuzzyAboveHi;
   FuzzyBool<float> mFuzzyBelowLo;

   // Fuzzy boolean variable. this is the OR of the fuzzy below low and
   // above high variables. It gives an indication of the confidence of
   // the measurements.
   FuzzyBool<float> mFuzzyConfidence;

   // Crisp boolean variables. These are set by thresholding the fuzzy
   // boolean variables. The threshold that is used is the fuzzy logic
   // threshold, not the signal low and high thresholds. It is usually at
   // 0.90. The low variable is true if it is declared that the input value
   // is below the low threshold. The high variable is true if it is declared
   // that the input value is above the high threshold. 
   bool mCrispAboveHi;
   bool mCrispBelowLo;

   // True if the input value is declared to be above thrshold. False if 
   // it is declared to be below threshold. This does not change if neither
   // condition is declared.
   bool mAboveFlag;

   // Previous value of the above flag.
   bool mLastAboveFlag;

   // True if the above flag has changed after an update.
   bool mChangeFlag;

   // True if first update after initialization.
   bool mFirstFlag;

   // Update counter.
   int mCount;

   // Error counter.
   int mErrorCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SlowThresholder();
   SlowThresholder(SlowThresholderParms* aParms);
   void initializeForSym(SlowThresholderParms* aParms);
   void initializeForASymHi(SlowThresholderParms* aParms);
   void initializeForASymLo(SlowThresholderParms* aParms);

   void initialize(SlowThresholderParms* aParms);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Update the state. The input is the value that is to be thresholded.
   // The output above flag is true if the input has been declared to be
   // above threshold and it is false if it has been declared to be below
   // threshold. The change flag is true if the output above flag is different
   // from its previous value.
   void doUpdate(
      float aValue,           // Input
      bool* aAboveFlag,       // Output
      bool* aChangeFlag);     // Output

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Return a string that can be used for a show.
   char* asShowString(char* aBuffer);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


