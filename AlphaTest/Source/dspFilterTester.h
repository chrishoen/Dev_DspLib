#ifndef _DSPFILTERTESTER_H_
#define _DSPFILTERTESTER_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "dspTextFile.h"
#include "dspFilterAlpha.h"
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
   Filter::AlphaStatistics mAlphaStatistics;

   // Read from sample file, detect pulses, write to pdw file
   void filter11  (FilterParms* aParms);
   void filter12  (FilterParms* aParms);
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
