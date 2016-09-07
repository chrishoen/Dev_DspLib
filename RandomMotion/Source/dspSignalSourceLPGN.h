#ifndef _DSPSIGNALSOURCELPGN_H_
#define _DSPSIGNALSOURCELPGN_H_

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

class SignalSourceLPGN
{
public:

   //--------------------------------------------------------------------------
   // Members.

   double  mT;            // Time
   double  mX;            // Sample
   double  mEX;           // Sample estimate

   double  mFs;           // Sampling frequency
   double  mTs;           // Sampling period
   double  mFp;           // Carrier frequency 
   double  mTp;           // Carrier period

   double  mOffset;       // Offset
   double  mAmplitude;    // amplitude
   double  mSigma;        // Sigma

   double  mAlphaOneAP1;  // Alpha filter constant

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Low pass filter

   Filter::AlphaOne mAlphaOne;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Guassian noise

   bool mSigmaFlag;
   std::mt19937 mRandomGenerator;
   std::normal_distribution<double> mRandomDistribution;

   //--------------------------------------------------------------------------
   // Constructor and initialization.
   // Create an new SignalSourceLPGN, set some of the members, call initialize to 
   // set other members.

   SignalSourceLPGN();
   void reset();
   void initialize();

    // Initialize random distribution.
   void initializeNoise();
   // Get noise from random distribution.
   double getNoise();

   //--------------------------------------------------------------------------
   // Advance the signal for one time step, return the signal value.

   double advance(double tTime = -1.0);

   //--------------------------------------------------------------------------
   // Support.

   void show();
};

//******************************************************************************
}//namespace

#endif

