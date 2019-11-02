#pragma once

/*==============================================================================
Dsp namespace: sixdofs that are measured by a computer vision based system.
Simulator synthetic image generator.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspFilterAlpha.h"

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
   Dsp::Filter::AlphaOne mFAFilter1BelowLo;
   Dsp::Filter::AlphaOne mFAFilter1AboveHi;

   // Update counter.
   int mCount;

   // Input value.
   double mValue;

   // Crisp boolean values updated at a fast rate.
   // True if the signal threshold comparion test is pass.
   bool   mFastCrisp1BelowLo;
   bool   mFastCrisp1AboveHi;

   // Previous values for the above.
   bool   mLastFastCrisp1BelowLo;
   bool   mLastFastCrisp1AboveHi;

   // Slow fuzzy boolean values slowed by alpha filters. These are based on 
   // the fast crisp boolean values 
   double mSlowFuzzy1BelowLo;
   double mSlowFuzzy1AboveHi;

   // Slow crisp boolean value obtained by thresholding the slow fuzzy 
   // boolean values.
   bool   mSlowCrisp1AboveHi;

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


