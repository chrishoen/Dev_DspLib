#pragma once
/*==============================================================================
Signal trial statistics.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides calculation of statistics for an input time series 
// signal. The input is the value of the signal. The outputs are expectation,
// uncertainty (the mean and the standard deviation) and minimum and maximum.
// The calculations are single pass. No history buffers are required. It does
// this for a trial experiment, for an
// arbitrary number of samples.
//
// google "standard deviation online algorithm".

class TrialStatistics
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.
  
   // Number of samples.
   unsigned long long mPutCount;

   // Input values.
   double   mX;            // Input value
   double   mXLimit;       // Input limit
   bool     mXLimitFlag;   // Input limit

   // Output values.
   double   mEX;           // expectation (mean)
   double   mUX;           // uncertainty (standard deviation)
   double   mMinX;         // minimum 
   double   mMaxX;         // maximum
   double   mMaxMaxX;      // maximum for all times
   double   mMean;         // expectation (mean)
   double   mStdDev;       // uncertainty (standard deviation)
   double   mVariance;     // variance

   // Intermediate values.
   double   mOLMean;       // Online algorithm
   double   mOLM2;         // Online algorithm
   double   mOLDelta;      // Online algorithm

   double   mXSum;         // Sum of X
   double   mXMean;        // expectation (mean)

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   TrialStatistics();

   // Start trial, optional outlier limit.
   void startTrial(double aXLimit=0.0);

   // Put input value.
   void put(double aX);

   // Finish trial, calculate variables.
   void finishTrial();

   // Show.
   void show(int aPF, char* aLabel);

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


