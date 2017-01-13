#ifndef _DSPHISTORYGENBASEGN_H_
#define _DSPHISTORYGENBASEGN_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <random>
#include "dspHistoryGenBase.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a base class for time series signal generators.
// It extends the base class by adding a gaussian noise generator.

class HistoryGenBaseGN : public HistoryGenBase
{
public:
   typedef HistoryGenBase BaseClass;

   //--------------------------------------------------------------------------
   // Input parameters.

   double  mNoiseSigma;   // Random noise generator sigma

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Guassian noise

   bool mNoiseFlag;
   std::mt19937 mRandomGenerator;
   std::normal_distribution<double> mRandomDistribution;

   //--------------------------------------------------------------------------
   // Constructor and initialization.

   HistoryGenBaseGN();
   void reset();
   virtual void initialize(History& aHistory);

    // Initialize random distribution.
   void initializeNoise();
   // Get noise from random distribution.
   double getNoise();
};

//******************************************************************************
}//namespace

#endif

