#pragma once

/*==============================================================================
Slow thresholder test parms
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspSlowThresholderParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that contains parameter member variables. The values of
// the parameters are set by reading a text file that contains command lines.
// Each command line is of the form "command argument1 argument2 ...".

class SlowTestParms
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Slow thresholder parameters.
   Dsp::SlowThresholderParms  mTestThresholderParms;

   // Slow classifier thresholder parameters.
   Dsp::SlowThresholderParms  mThresholderParmsM2;
   Dsp::SlowThresholderParms  mThresholderParmsM1;
   Dsp::SlowThresholderParms  mThresholderParmsP1;
   Dsp::SlowThresholderParms  mThresholderParmsP2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. These are used int expand.

   // Fuzzy alpha filter sampling period and time constant, seconds.
   double mAlphaFilterTs;
   double mAlphaFilterTc;

   // Fuzzy to crisp threshold.
   double mFuzzyToCrispThreshLo;
   double mFuzzyToCrispThreshHi;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor,
   SlowTestParms();
   void reset();

   // Simulate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _SOMESLOWTESTPARMS_CPP_
   SlowTestParms gSlowTestParms;
#else
   extern SlowTestParms gSlowTestParms;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace