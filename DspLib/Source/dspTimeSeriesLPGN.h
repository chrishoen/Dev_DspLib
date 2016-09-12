#ifndef _DSPTIMESERIESLPGN_H_
#define _DSPTIMESERIESLPGN_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <random>
#include "dspTimeSeriesBase.h"
#include "dspFilterAlpha.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates time series signal generator.
// It is based on low pass filtering gaussian noise.
// The low pass filter is imlemented with two cascaded alpha filters.

class TimeSeriesLPGN : public TimeSeriesBase
{
public:
   typedef TimeSeriesBase BaseClass;

   //--------------------------------------------------------------------------
   // Input parameters.

   double  mFp;           // Carrier frequency 
   double  mAlphaOneAP1;  // Alpha filter constant

   //--------------------------------------------------------------------------
   // Extra parameters.

   double  mTp;           // Carrier period
   double  mNoiseSigma;   // Random noise generator sigma

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Low pass filter

   Filter::AlphaOne mAlphaOne1;
   Filter::AlphaOne mAlphaOne2;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Guassian noise

   bool mNoiseFlag;
   std::mt19937 mRandomGenerator;
   std::normal_distribution<double> mRandomDistribution;

   //--------------------------------------------------------------------------
   // Constructor and initialization.
   // Create an new TimeSeriesLPGN, set some of the members, call initialize to 
   // set other members.

   TimeSeriesLPGN();
   void reset();
   void initialize();

    // Initialize random distribution.
   void initializeNoise();
   // Get noise from random distribution.
   double getNoise();

   //--------------------------------------------------------------------------
   // Generate the time series.

   void generate();

   //--------------------------------------------------------------------------
   // Support.

   void show();
};

//******************************************************************************
}//namespace

#endif

