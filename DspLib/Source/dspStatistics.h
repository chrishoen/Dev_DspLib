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

}//namespace
#endif


