#ifndef _DSPSIGNALHISTORY_H_
#define _DSPSIGNALHISTORY_H_

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
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a history of a signal. It is used for periodic or
// aperiodic time series of the samples of a signal. It stores the signal
// sample values and times of arrival.

class SignalHistory
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Arrays of signal sample values and times of arrival.
   double* mX;
   double* mT;

   // Number of samples in array.
   int     mMaxNumSamples;
   int     mNumSamples;

   // Current index.
   int     mK;

   // Mean of inter arrival times, the mean delta time.  If the sample time
   // series is periodic then this is the sampling period.
   double  mMeanDeltaT;

   // Sum used to calcaulte the mean delta time.
   double  mSumDeltaT;

   // If true then memory has been allocated.
   bool mMemoryFlag;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Constructor and initialization.

   // Constructor.
   SignalHistory();
  ~SignalHistory();

   // Allocate memory.
   void initialize(int aMaxNumSamples);

   // Deallocate memory.
   void finalize();

   // Start recording a signal history. This resets member variables.
   void startHistory();

   // Finish recording a signal history.
   void finishHistory();
      
   // Put a sample to the signal history.
   void putSample(double aTime,double aValue);


   void show();
};

//******************************************************************************
}//namespace

#endif

