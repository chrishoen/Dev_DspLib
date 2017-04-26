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

class TrialStatistics
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // 
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

   // Initialize
   void startTrial(double aXLimit=0.0);
   void finishTrial();

   // Put input value.
   void put(double aX);

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

   void showEMM       (int aPrintFilter,char* aLabel);
   void showDegEMM    (int aPrintFilter,char* aLabel);
   void showCEMM      (int aPrintFilter,char* aLabel);
   void showDegCEMM   (int aPrintFilter,char* aLabel);

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

   void logEMM       (int aLogNum,char* aLabel);
   void logDegEMM    (int aLogNum,char* aLabel);
   void logCEMM      (int aLogNum,char* aLabel);
   void logDegCEMM   (int aLogNum,char* aLabel);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace




