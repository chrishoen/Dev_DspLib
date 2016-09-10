#ifndef _DSPTIMESERIESLPGN_H_
#define _DSPTIMESERIESLPGN_H_

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

class TimeSeriesLPGN
{
public:

   //--------------------------------------------------------------------------
   // Members.

   double* mX;            // Array of samples

   double  mDuration;     // Time duration of signal
   double  mFs;           // Sampling frequency
   double  mFp;           // Carrier frequency 

   double  mEX;           // Desired expectation
   double  mUX;           // Desired uncertainty

   double  mTs;           // Sampling period
   double  mTp;           // Carrier period
   int     mNumSamples;   // Number of samples in array

   double  mNoiseSigma;   // Random noise generator sigma
   double  mAlphaOneAP1;  // Alpha filter constant

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

   bool mSigmaFlag;
   std::mt19937 mRandomGenerator;
   std::normal_distribution<double> mRandomDistribution;

   //--------------------------------------------------------------------------
   // Constructor and initialization.
   // Create an new TimeSeriesLPGN, set some of the members, call initialize to 
   // set other members.

   TimeSeriesLPGN();
  ~TimeSeriesLPGN();
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

