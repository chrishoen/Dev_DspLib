#pragma once
/*==============================================================================

mean,stdev,min,max

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This filter characterizes an input signal by calculating expectations and
// uncertainties of the signal. It does this for a trial experiment, for an
// arbitrary number of samples.

class TrialStatistics
{
public:
   TrialStatistics();

   // Initialize
   void startTrial(double aXLimit=0.0);
   void finishTrial();

   // Show 
   void show        (int aPrintFilter,char* aLabel);
   void showDeg     (int aPrintFilter,char* aLabel);
   void showEUMM    (int aPrintFilter,char* aLabel);
   void showDegEUMM (int aPrintFilter,char* aLabel);
   void showEUX     (int aPrintFilter,char* aLabel);
   void showDegEUX  (int aPrintFilter,char* aLabel);
   void showEMM     (int aPrintFilter,char* aLabel);
   void showDegEMM  (int aPrintFilter,char* aLabel);

   // Write to log file 
   void log         (int aLogNum,char* aLabel);
   void logDeg      (int aLogNum,char* aLabel);
   void logEUMM     (int aLogNum,char* aLabel);
   void logDegEUMM  (int aLogNum,char* aLabel);
   void logEUX      (int aLogNum,char* aLabel);
   void logDegEUX   (int aLogNum,char* aLabel);
   void logUX       (int aLogNum);
   void logDegUX    (int aLogNum);

   // Put input value
   void put(double aX);

   // Members
   unsigned long long mCount;    // Number of samples

   // Input values
   double   mX;            // Input value
   double   mXLimit;       // Input limit, for ignoring outliers
   bool     mXLimitFlag;   // Input limit, for ignoring outliers
   // Output values
   double   mEX;           // expectation (mean)
   double   mUX;           // uncertainty (standard deviation)
   double   mMinX;         // minimum 
   double   mMaxX;         // maximum
   double   mExtX;         // extremum
   double   mMean;         // expectation (mean)
   double   mStdDev;       // uncertainty (standard deviation)
   double   mVariance;     // variance


   double   mOLMean;       // Online algorithm
   double   mOLM2;         // Online algorithm
   double   mOLDelta;      // Online algorithm

   double   mXSum;         // Sum of X
   double   mXMean;        // expectation (mean)
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace




