#pragma once

/*==============================================================================
Dsp library: fuzzy alpha filter.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspFilterAlphaOne.h"
#include "dspFuzzyBool.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that implements a alpha filter for a fuzzy boolean 
// variable. It addresses the problem of taking moving averages of a
// boolean variable and thresholding it. It uses an alpha filter that
// maintains a state variable that is between zero and one. This is
// transferred to a fuzzy boolean variable that is then crispified.
//

class FuzzyAlphaFilter
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Fuzzy crisp threshold. This is used to crispify the 
   float mCrispThresh;

   // Alpha filters. This is input a crisp boolean. It outputs values
   // bewteen 0.0 and 1.0.
   Dsp::Filter::AlphaOne<float> mAlphaFilter;

   // Fuzzy boolean variable. This set from the outputs of the alpha
   // filter.
   FuzzyBool<float> mFuzzy;

   // Crisp value of the fuzzy boolean. 
   bool mConditionFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   FuzzyAlphaFilter();
   void resetVars();
   void initialize(double aTs, double aStepTime, double aCrispThresh);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Update the state. The input is a boolean. It is input to the alpha 
   // filter. The fuzzy variable is set from the output of the alpha filter.
   // The output is the crisp value of the fuzzy variable.
   void doUpdate(
      bool  aValue,           // Input
      bool* aConditionFlag);  // Output
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


