#ifndef _DSPPULSESTATISTICS_H_
#define _DSPPULSESTATISTICS_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspPdw.h"
#include "dspFilterFilters.h"
#include "dspStatistics2.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is used to store statistics on pulses that have arrived during the
// recent past, typically the last 100 milliseconds.

class PulseStatistics
{
public:
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------

   // Constructor.
   PulseStatistics();

   // Reset paramters to defaults.
   void reset();

   // Parameters
   double  mFs;               // Sampling frequency
   double  mTs;               // Sampling period
   double  mWindowTimeSize;   // Moving average time size
   int     mWindowNumSample;  // Moving average sample size

   // Initialize, using the parameters.
   void initialize();

   // Finalize
   void finalize();

   // Add/subtract a pdw to/from the statistics. Pdw values are extracted
   // and added or subtracted to the following sum statistics. These are 
   // called at the sample rate by the pulse analyzer front end when a pulse
   // arrives or when a pulse is removed from the sliding window pulse list.
   void addPdw      (Pdw* aPdw);
   void subtractPdw (Pdw* aPdw);

   // Pdw statistics, these are aperiodic.
   SumStatistics mAmplitude;
   SumStatistics mPulseWidth;
   int mCount;

   // Put pulse density to the statistics. This is called at the sample rate.
   void putPulseDensity(double aX);

   // Pulse statistics. These are periodic.
   Filter::MovingAverage mPulseDensity;
};

//******************************************************************************
}//namespace

#endif

#if 0

  999
         +---+
 1000    | 0 |     oldest, get, remove, head, top
         +---+
 1001    | 1 |
         +---+
 1002    | 2 |
         +---+
 1003    | 3 |     before
         +---+
 1004    | 4 |     after
         +---+
 1005    | 5 |
         +---+
 1006    | 6 |
         +---+
 1007    | 7 |     newest, put, add, tail, bottom
         +---+
 1008

 time
  |
  |
  v
 

#endif