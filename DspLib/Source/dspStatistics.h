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
// This class provides calculation of statistics for an input time series 
// signal. The input is the values of the signal. The outputs are expectation,
// uncertainty (the mean and the standard deviation) and minimum and maximum.
// The calculations are single pass. Not history buffers are required.
//
// google "standard deviation online algorithm".

class TrialStatistics
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Counters.
   unsigned long long mCount;     // Number of samples.
   unsigned long long mDropCount; // Number of samples that were dropped.

   // Input values
   double   mX;            // Input value
   double   mXLimit;       // Input limit, for ignoring outliers
   bool     mXLimitFlag;   // Input limit, for ignoring outliers

   // Output values
   double   mEX;           // Expectation (mean)
   double   mUX;           // Uncertainty (standard deviation)
   double   mMinX;         // Minimum 
   double   mMaxX;         // Maximum
   double   mExtX;         // Extremum
   double   mMean;         // Expectation (mean)
   double   mStdDev;       // Uncertainty (standard deviation)
   double   mVariance;     // Variance
   double   mSX;           // Mean - Extremum

   double   mTimeMinX;     // Time that minimum  was encountered 
   double   mTimeMaxX;     // Time that maximum  was encountered 
   double   mTimeExtX;     // Time that extremum was encountered 

   // Intermediate variables.
   double   mOLMean;       // Online algorithm
   double   mOLM2;         // Online algorithm
   double   mOLDelta;      // Online algorithm

   double   mXSum;         // Sum of X
   double   mXMean;        // expectation (mean)

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infastructure.

   TrialStatistics();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Initialize variables for trials
   void startTrial(double aXLimit=0.0);
   void finishTrial();

   // Put input value and calculate intermediate variables.
   void put(double aX);

   // Put input value with the time that it occured and calculate
   // intermediate variables
   void put(double aX,double aTime);

   // Indicate that a sample was dropped.
   void drop();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show 
   void show          (int aPrintFilter,char* aLabel);
   void showDeg       (int aPrintFilter,char* aLabel);

   void showEUMM      (int aPrintFilter,char* aLabel);
   void showDegEUMM   (int aPrintFilter,char* aLabel);
   void showCEUMM     (int aPrintFilter,char* aLabel);
   void showDegCEUMM  (int aPrintFilter,char* aLabel);

   void showEUX       (int aPrintFilter,char* aLabel);
   void showDegEUX    (int aPrintFilter,char* aLabel);
   void showCEUX      (int aPrintFilter,char* aLabel);
   void showDegCEUX   (int aPrintFilter,char* aLabel);

   void showMM        (int aPrintFilter,char* aLabel);
   void showDegMM     (int aPrintFilter,char* aLabel);
   void showEMM       (int aPrintFilter,char* aLabel);
   void showDegEMM    (int aPrintFilter,char* aLabel);
   void showCEMM      (int aPrintFilter,char* aLabel);
   void showDegCEMM   (int aPrintFilter,char* aLabel);

   void showEUS       (int aPrintFilter,char* aLabel);
   void showDegEUS    (int aPrintFilter,char* aLabel);
   void showCEUS      (int aPrintFilter,char* aLabel);
   void showDegCEUS   (int aPrintFilter,char* aLabel);

   void showTimeExt   (int aPrintFilter,char* aLabel);

   void showCount     (int aPrintFilter,char* aLabel);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Write to log file.
   void log          (int aLogNum,char* aLabel);
   void logDeg       (int aLogNum,char* aLabel);

   void logEUMM      (int aLogNum,char* aLabel);
   void logDegEUMM   (int aLogNum,char* aLabel);
   void logCEUMM     (int aLogNum,char* aLabel);
   void logDegCEUMM  (int aLogNum,char* aLabel);

   void logEUX       (int aLogNum,char* aLabel);
   void logDegEUX    (int aLogNum,char* aLabel);
   void logCEUX      (int aLogNum,char* aLabel);
   void logDegCEUX   (int aLogNum,char* aLabel);

   void logMM        (int aLogNum,char* aLabel);
   void logDegMM     (int aLogNum,char* aLabel);
   void logEMM       (int aLogNum,char* aLabel);
   void logDegEMM    (int aLogNum,char* aLabel);
   void logCEMM      (int aLogNum,char* aLabel);
   void logDegCEMM   (int aLogNum,char* aLabel);

   void logEUS       (int aLogNum,char* aLabel);
   void logDegEUS    (int aLogNum,char* aLabel);
   void logCEUS      (int aLogNum,char* aLabel);
   void logDegCEUS   (int aLogNum,char* aLabel);

   void logTimeExt   (int aLogNum,char* aLabel);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace




