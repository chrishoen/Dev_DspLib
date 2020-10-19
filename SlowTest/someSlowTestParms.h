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
   Dsp::SlowThresholderParms  mThresholderParmsP2;
   Dsp::SlowThresholderParms  mThresholderParmsP1;
   Dsp::SlowThresholderParms  mThresholderParmsM1;
   Dsp::SlowThresholderParms  mThresholderParmsM2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. These are used int expand.

   // Fuzzy alpha filter sampling period and step response time, seconds.
   float mAlphaFilterTs;
   float mAlphaFilterStepTime;

   // Fuzzy to crisp threshold.
   float mFuzzyToCrispThresh;

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