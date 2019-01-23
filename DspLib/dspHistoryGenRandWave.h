#pragma once

/*==============================================================================
Signal history generator with a random wave.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"

#include "dspHistoryGenParms.h"
#include "dspHistoryGenBase.h"
#include "dspHistoryGaussNoise.h"
#include "dspFilterButterworth.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a generator for a signal history that evolves according
// to an integrated wiener process. The signal history is implemented by low
// pass filtering gaussian noise with a butterworth filter with a specified
// cutoff frequency. The history is then normalized to have a specified
// expectation and uncertainty. This generates a random wave.
 
class HistoryGenRandWave : public HistoryGenBase
{
public:
   typedef HistoryGenBase BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Low pass butterworth filter.
   HistoryGaussNoise mNoise;

   // Low pass butterworth filter.
   Filter::ButterworthLP mFilter;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HistoryGenRandWave(HistoryGenParms& aParms);
   void show();

   // Generate the signal history according to the parameters.
   // Type1 is  periodic, with   regular intersample arrival times.
   // Type2 is aperiodic, with irregular intersample arrival times.
   void generateHistoryType1(History& aHistory) override;
   void generateHistoryType2(History& aHistory) override;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


