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
