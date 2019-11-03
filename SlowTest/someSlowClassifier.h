#pragma once

/*==============================================================================
Slow classifier example class
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspSlowThresholder.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that implments a slow classifier. It addresses the problem
// of threshold classification of a noisy variable that varies over time.
// 
//

class SlowClassifier
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Input value.
   double mValue;

   // Output value. Class. This is one of -2,-1,0,1,2.
   int mClass;

   // Previous value of the class.
   int mLastClass;

   // Slow thresholders.
   Dsp::SlowThresholder mThresholderM2;
   Dsp::SlowThresholder mThresholderM1;
   Dsp::SlowThresholder mThresholderP1;
   Dsp::SlowThresholder mThresholderP2;

   // True if the input value is declared to be above thrshold. False if 
   // it is declared to be below threshold. This does not change if neither
   // condition is declared.
   bool mAboveFlagM2;
   bool mAboveFlagM1;
   bool mAboveFlagP1;
   bool mAboveFlagP2;

   // True if the above flag has changed after an update.
   bool mChangeFlagM2;
   bool mChangeFlagM1;
   bool mChangeFlagP1;
   bool mChangeFlagP2;
   bool mChangeFlag;

   // True if first update after initialization.
   bool mFirstFlag;

   // Update counter.
   int mCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SlowClassifier();
   void initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Classify the input variable according to the thresholder bank.
   // The change flag is true if the output above flag is different
   // from its previous value.
   void doClassify(
      double aValue,           // Input
      int&   aClass,           // Output
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


