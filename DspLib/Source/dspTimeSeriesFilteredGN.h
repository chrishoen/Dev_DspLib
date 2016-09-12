#ifndef _DSPTIMESERIESFILTEREDGN_H_
#define _DSPTIMESERIESFILTEREDGN_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspTimeSeriesBaseGN.h"
#include "dspFilterFilters.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates time series signal generator.
// It is based on low pass filtering gaussian noise.
// The low pass filter is imlemented with two cascaded alpha filters.

class TimeSeriesFilteredGN : public TimeSeriesBaseGN
{
public:
   typedef TimeSeriesBaseGN BaseClass;

   //--------------------------------------------------------------------------
   // Input parameters.

   int     mBSize;
   int     mASize;
   double* mBArray;
   double* mAArray;
   
   //--------------------------------------------------------------------------
   // Extra parameters.

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Low pass filter

   // Bandpass filter centered at 4 hz with Fs of 4096 hz.
   Dsp::Filter::IIRFilter   mFilter;

   //--------------------------------------------------------------------------
   // Constructor and initialization.
   // Create an new TimeSeriesFilteredGN, set some of the members, call initialize to 
   // set other members.

   TimeSeriesFilteredGN();
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

