#ifndef _DSPTIMESERIESLPGN_H_
#define _DSPTIMESERIESLPGN_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspTimeSeriesBaseGN.h"
#include "dspFilterButterworth.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates time series signal generator.
// It is based on low pass filtering gaussian noise.
// The low pass filter is a butterworth.

class TimeSeriesLPGN : public TimeSeriesBaseGN
{
public:
   typedef TimeSeriesBaseGN BaseClass;

   //--------------------------------------------------------------------------
   // Input parameters.

   int    mN;
   double mFc; 

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Low pass filter

   Filter::ButterworthLP mFilter;

   //--------------------------------------------------------------------------
   // Constructor and initialization.
   // Create an new TimeSeriesLPGN, set some of the members, call initialize to 
   // set other members.

   TimeSeriesLPGN();
   void reset();
   void initialize();

   //--------------------------------------------------------------------------
   // Generate the time series.

   void generate();

   //--------------------------------------------------------------------------
   // Support.

   void show();
};

//******************************************************************************
}//namespace

#endif

