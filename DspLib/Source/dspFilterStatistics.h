#ifndef _DSPFILTERSTATISTICS_H_
#define _DSPFILTERSTATISTICS_H_
/*==============================================================================

filters
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspFilterAlpha.h"
#include "dspFilterFilters.h"

namespace Dsp
{
namespace Filter
{

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // This filter characterizes an input signal by calculating expectations and
   // uncertainties of the signal. It does this with a set of alpha filters.

   class AlphaStatistics
   {
   public:
      // Constructor
      AlphaStatistics();

      // Initialize
      void initialize(double aAlpha);

      // Put input value
      void put(double aX);

      // Output values
      double mX;          // Input value
      double mEX;         // Expectation (mean)
      double mUX;         // Uncertainty (standard deviation)
      double mVariance;   // Variance
      double mMean;       // Expectation (mean)
      double mStdDev;     // Uncertainty (standard deviation)

      // Alpha filters for expectation and uncertainty
      AlphaOne    mXAlpha;        // Alpha filter for input X
      AlphaOne    mXSquareAlpha;  // Alpha filter for input X squared

      // Helpers
      int  mK;
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
      void put(float aX);

      // Members
      int mSize;
      bool mFirstFlag;

      // Output values
      bool   mEndOfPeriod;  // True at the end of a period
      float  mX;            // Input value
      float  mEX;           // expectation (mean)
      float  mUX;           // uncertainty (standard deviation)
      float  mMinX;         // minimum 
      float  mMaxX;         // maximum
      float  mMean;         // expectation (mean)
      float  mStdDev;       // uncertainty (standard deviation)


      float  mEXSquare;     // expectation of X squared
      float  mVariance;     // variance

      // Sums for expectation and uncertainty
      float  mXSum;         // Sum of X
      float  mXSquareSum;   // Sum of X squared
      int    mPutCount;     // Put count

      // Current min and max
      float  mCurrentMinX;  // minimum
      float  mCurrentMaxX;  // maximum


      // Members
      int mK;
   };

}//namespace
}//namespace
#endif


