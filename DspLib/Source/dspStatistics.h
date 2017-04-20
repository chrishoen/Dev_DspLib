#ifndef _DSPSTATISTICS_H_
#define _DSPSTATISTICS_H_
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
// uncertainties of the signal. It does this for a running sum, for use
// in a moving window.

class SumStatistics
{
public:
   // Constructor
   SumStatistics();
   void reset();

   // Add/Subtract sample to/from sums
   void add      (double aX);
   void subtract (double aX);

   // Calculate statistics on sums
   void calculate();

   // Calculate output values
   double  mX;            // Input value
   double  mEX;           // Expectation (mean)
   double  mUX;           // Uncertainty (standard deviation)
   double  mMean;         // Expectation (mean)
   double  mStdDev;       // Uncertainty (standard deviation)

   double  mEXSquare;     // expectation of X squared
   double  mVariance;     // variance

   // Sums for expectation and uncertainty
   double  mXSum;         // Sum of X
   double  mXSquareSum;   // Sum of X squared
   int     mCount;        // Count of samples in sums

   // Support
   void show();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This filter characterizes an input signal by calculating expectations and
// uncertainties of the signal. It does this on a periodic basis, given a fixed
// window size. For example, given a fixed window size of 1000, and an update
// rate of 1000 khz, this will produce new statisics once a second.

class PeriodicStatistics
{
public:
   // Initialize
   void initialize(int aSize);
   void show();

   // Put input value
   void put(double aX);

   // Members
   int mSize;
   bool mFirstFlag;

   // Output values
   bool    mEndOfPeriod;  // True at the end of a period
   double  mX;            // Input value
   double  mEX;           // expectation (mean)
   double  mUX;           // uncertainty (standard deviation)
   double  mMinX;         // minimum 
   double  mMaxX;         // maximum
   double  mMean;         // expectation (mean)
   double  mStdDev;       // uncertainty (standard deviation)


   double  mEXSquare;     // expectation of X squared
   double  mVariance;     // variance

   // Sums for expectation and uncertainty
   double  mXSum;         // Sum of X
   double  mXSquareSum;   // Sum of X squared
   int     mPutCount;     // Put count

   // Current min and max
   double  mCurrentMinX;  // minimum
   double  mCurrentMaxX;  // maximum

   // Members
   int mK;
};

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
#endif


