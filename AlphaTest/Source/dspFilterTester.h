#ifndef _DSPFILTERTESTER_H_
#define _DSPFILTERTESTER_H_

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

class FilterParms
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

   FilterParms();
   void reset();
   void initialize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

class FilterTester
{
public:
   FilterTester();
   void initialize();

   // Filters
   Filter::AlphaOne        mAlphaOne;
   Filter::AlphaTwo        mAlphaTwo;
   Filter::AlphaStatistics mAlphaStatistics;
   Filter::MovingAverage   mMovingAverage;

   // Statistics
   TrialStatistics         mTrialStatistics;

   // Tests
   void testAlphaOne         (FilterParms* aParms);
   void testAlphaTwo         (FilterParms* aParms);
   void testAlphaStatistics  (FilterParms* aParms);
   void testMovingAverage    (FilterParms* aParms);

   // Read from sample file, run trial statistics
   void trial11  (FilterParms* aParms);
};

//******************************************************************************
// Global instance

#ifdef _DSPFILTERTESTER_CPP_
          FilterTester gFilterTester;
#else
   extern FilterTester gFilterTester;
#endif

//******************************************************************************
}//namespace

#endif
