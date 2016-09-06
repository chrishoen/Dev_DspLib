#ifndef _DSPRANDOMMOTION_H_
#define _DSPRANDOMMOTION_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "dspTextFile.h"
#include "dspStatistics.h"
#include "dspFilterAlpha.h"
#include "dspFilterFilters.h"
#include "dspFilterStatistics.h"

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

   double  mFs;           // Sampling frequency
   double  mTs;           // Sampling period
   double  mDuration;     // Time duration of signal
   int     mNumSamples;   // Number of samples in array
   
   double mAp1;
   double mAp2;
   double mAp3;

   double mWindowTimeSize;
   int    mWindowSampleSize;

   //--------------------------------------------------------------------------
   // File names

   static const int cMaxStringSize=400;

   char mInputFileName  [cMaxStringSize];
   char mOutputFileName [cMaxStringSize];

   void setInputFileName  (char* aFileName);
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

   // Filters
   Filter::AlphaOne        mAlphaOne;
   Filter::AlphaTwo        mAlphaTwo;
   Filter::AlphaThree      mAlphaThree;
   Filter::AlphaStatistics mAlphaStatistics;
   Filter::MovingAverage   mMovingAverage;

   // Statistics
   TrialStatistics         mTrialStatistics;

   // Tests
   void testAlphaOne         (MotionParms* aParms);
   void testAlphaTwo         (MotionParms* aParms);
   void testAlphaThree       (MotionParms* aParms);
   void testAlphaStatistics  (MotionParms* aParms);
   void testMovingAverage    (MotionParms* aParms);

   // Read from sample file, run trial statistics
   void trial11  (MotionParms* aParms);
};

//******************************************************************************
// Global instance

#ifdef _DSPRANDOMMOTION_CPP_
          RandomMotion gRandomMotion;
#else
   extern RandomMotion gRandomMotion;
#endif

//******************************************************************************
}//namespace

#endif
