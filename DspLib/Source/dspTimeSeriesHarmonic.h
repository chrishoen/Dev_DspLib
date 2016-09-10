#ifndef _DSPTIMESERIESHARMONIC_H_
#define _DSPTIMESERIESHARMONIC_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <random>
#include "dspFilterAlpha.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a signal source. It can be used to generate a time 
// series of samples.

class TimeSeriesHarmonic
{
public:

   //--------------------------------------------------------------------------
   // Members.

   double* mX;            // Array of samples

   double  mDuration;     // Time duration of signal
   double  mFs;           // Sampling frequency
   double  mEX;           // Desired expectation
   double  mUX;           // Desired uncertainty

   double  mFc1;          // Carrier frequency 
   double  mFc2;          // Carrier frequency 
   double  mAc1;          // Carrier amplitude 
   double  mAc2;          // Carrier amplitude 
   double  mPc1;          // Carrier phase 
   double  mPc2;          // Carrier phase 
   double  mSigma;        // Random noise generator sigma


   double  mTs;           // Sampling period
   int     mNumSamples;   // Number of samples in array

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Guassian noise

   bool mSigmaFlag;
   std::mt19937 mRandomGenerator;
   std::normal_distribution<double> mRandomDistribution;

   //--------------------------------------------------------------------------
   // Constructor and initialization.
   // Create an new TimeSeriesHarmonic, set some of the members, call initialize to 
   // set other members.

   TimeSeriesHarmonic();
  ~TimeSeriesHarmonic();
   void reset();
   void initialize();

    // Initialize random distribution.
   void initializeNoise();
   // Get noise from random distribution.
   double getNoise();

   //--------------------------------------------------------------------------
   // Generate the signal series history.

   void generate();

   //--------------------------------------------------------------------------
   // Support.

   void show();
};

//******************************************************************************
}//namespace

#endif

