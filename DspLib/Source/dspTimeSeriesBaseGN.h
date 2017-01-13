#ifndef _DSPTIMESERIESBASEGN_H_
#define _DSPTIMESERIESBASEGN_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <random>
#include "dspTimeSeriesBase.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a base class for time series signal generators.
// It extends the base class by adding a gaussian noise generator.

class TimeSeriesBaseGN : public TimeSeriesBase
{
public:
   typedef TimeSeriesBase BaseClass;

   //--------------------------------------------------------------------------
   // Input parameters.

   double  mNoiseSigma;   // Random noise generator sigma

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Gaussian noise

   bool mNoiseFlag;
   std::mt19937 mRandomGenerator;
   std::normal_distribution<double> mRandomDistribution;

   //--------------------------------------------------------------------------
   // Constructor and initialization.
   // Create an new TimeSeriesBaseGN, set some of the members, call initialize to 
   // set other members.

   TimeSeriesBaseGN();
   void reset();
   void initialize();

    // Initialize random distribution.
   void initializeNoise();
   // Get noise from random distribution.
   double getNoise();
};

//******************************************************************************
}//namespace

#endif

