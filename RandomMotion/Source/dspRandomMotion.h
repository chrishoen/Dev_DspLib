#ifndef _DSPRANDOMMOTION_H_
#define _DSPRANDOMMOTION_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class MotionParms
{
public:

   //--------------------------------------------------------------------------
   // Parameters


   double  mDuration;     // Time duration of signal
   double  mFs;           // Sampling frequency
   double  mFp;           // Carrier frequency 

   double  mEX;           // Desired expectation
   double  mUX;           // Desired uncertainty

   double  mTs;           // Sampling period
   double  mTp;           // Carrier period
   int     mNumSamples;   // Number of samples in array

   double  mFc1;          // Carrier frequency 
   double  mFc2;          // Carrier frequency 
   double  mAc1;          // Carrier amplitude 
   double  mAc2;          // Carrier amplitude 
   double  mPc1;          // Carrier phase 
   double  mPc2;          // Carrier phase 
   double  mSigma;        // Random noise generator sigma


   
   //--------------------------------------------------------------------------
   // File names

   static const int cMaxStringSize=400;

   char mOutputFileName [cMaxStringSize];

   void setOutputFileName (char* aFileName);
   
   //--------------------------------------------------------------------------
   // Constructors

   MotionParms();
   void reset();
   void initialize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

class RandomMotion
{
public:
   RandomMotion();
   void initialize();


   // Tests
   void propagate1(MotionParms* aParms);
   void propagate2(MotionParms* aParms);
};

//******************************************************************************
}//namespace

#endif
