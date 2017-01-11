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
   double* mValue;
   double* mTime;

   // Number of samples in array.
   int     mMaxNumSamples;
   int     mNumSamples;

   // Current index.
   int     mK;

   // Mean of inter arrival times, the mean delta time.  If the sample time
   // series is periodic then this is the sampling period.
   double  mMeanDeltaTime;

   // Sum used to calcaulte the mean delta time.
   double  mSumDeltaTime;

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

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Add to the history.

   // Start recording a signal history. This resets member variables.
   void startHistory();

   // Finish recording a signal history.
   void finishHistory();
      
   // Put a sample to the signal history.
   void putSample(double aTime,double aValue);

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Get from the history.

   // Get a sample at a particular index.
   bool getValueAtIndex  (int aIndex,double* aValue);
   bool getTimeAtIndex   (int aIndex,double* aTime);
   bool getSampleAtIndex (int aIndex,double* aTime,double* aValue);

   // Get a sample value that is closest to a particular time.
   bool getValueAtTime(double aTime,double* aValue);

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // More.

   void show();
};

//******************************************************************************
}//namespace

#endif

