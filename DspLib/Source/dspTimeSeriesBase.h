#ifndef _DSPTIMESERIESBASE_H_
#define _DSPTIMESERIESBASE_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <random>

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a base class for time series signal generators.

class TimeSeriesBase
{
public:

   //--------------------------------------------------------------------------
   // Input parameters.

   double  mDuration;     // Time duration of signal
   double  mFs;           // Sampling frequency

   double  mEX;           // Desired expectation
   double  mUX;           // Desired uncertainty

   //--------------------------------------------------------------------------
   // Generated time series.

   double* mX;            // Array of samples

   //--------------------------------------------------------------------------
   // Extra parameters.

   double  mTs;           // Sampling period
   int     mNumSamples;   // Number of samples in array

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Constructor and initialization.
   // Create an new TimeSeriesBase, set some of the members, call initialize to 
   // set other members.

   TimeSeriesBase();
  ~TimeSeriesBase();
   virtual void reset();
   virtual void initialize();

   //--------------------------------------------------------------------------
   // Generate the time series.

   virtual void generate()=0;

   //--------------------------------------------------------------------------
   // Generate the time series.

   void normalize();

   //--------------------------------------------------------------------------
   // Support.

   virtual void show();
};

//******************************************************************************
}//namespace

#endif

