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
}//namespace


