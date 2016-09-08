#ifndef _DSPTIMESERIESTIME_H_
#define _DSPTIMESERIESTIME_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <random>
#include "dspFilterAlpha.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a signal source. It can be used to generate a time 
// series of samples.

class TimeSeriesTime
{
public:

   //--------------------------------------------------------------------------
   // Members.

   double* mT;            // Array of time samples

   double  mDuration;     // Time duration of signal
   int     mNumSamples;   // Number of samples in array

   double  mFs;           // Sampling frequency
   double  mTs;           // Sampling period

   //--------------------------------------------------------------------------
   // Constructor and initialization.
   // Create an new TimeSeriesTime, set some of the members, call initialize to 
   // set other members.

   TimeSeriesTime();
  ~TimeSeriesTime();
   void reset();
   void initialize();

   // Get noise from random distribution.
   double getNoise();

   //--------------------------------------------------------------------------
   // Generate the signal series history.

   void generate();

   //--------------------------------------------------------------------------
   // Support.

   void show();
};

//******************************************************************************
}//namespace

#endif

