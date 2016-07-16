#ifndef _DSPSIGNALSOURCE_H_
#define _DSPSIGNALSOURCE_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <random>

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a signal source. It can be used to generate a time 
// series of samples.

class SignalSource
{
public:

   //--------------------------------------------------------------------------
   // Members.

   double  mT;            // Time
   double  mX;            // Sample

   double  mFs;           // Sampling frequency
   double  mTs;           // Sampling period
   double  mFp;           // Carrier frequency 
   double  mTp;           // Carrier period

   double  mOffset;       // Offset
   double  mAmplitude;    // amplitude
   double  mSigma;        // Sigma

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Guassian noise

   bool mSigmaFlag;
   std::mt19937 mRandomGenerator;
   std::normal_distribution<double> mRandomDistribution;

   //--------------------------------------------------------------------------
   // Constructor and initialization.
   // Create an new SignalSource, set some of the members, call initialize to 
   // set other members.

   SignalSource();
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
