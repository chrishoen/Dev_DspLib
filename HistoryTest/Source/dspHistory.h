#ifndef _DSPHISTORY_H_
#define _DSPHISTORY_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

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
// sample values and times of arrival in dynamically allocated arrays.

class History
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
   int     mMaxSamples;
   int     mNumSamples;

   // Current index.
   int     mIndex;

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
   History();
  ~History();

   // Allocate memory.
   void initialize(int aMaxSamples);

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
      
   // Write a sample to the signal history and advance the index.
   void writeSample(double aTime,double aValue);

   // Set the index to zero.
   void rewind();

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Read values from the signal history.

   // Read a sample at a particular index.
   bool readValueAtIndex  (int aIndex,double* aValue);
   bool readTimeAtIndex   (int aIndex,double* aTime);
   bool readSampleAtIndex (int aIndex,double* aTime,double* aValue);

   // Read a sample value that is interpolated from a target time that is
   // calculated to be the time at an input index minus an input delta.
   // If the target time is not between the time at the input index and
   // the time of the previous index then a downward search is performed 
   // until it is found.
   bool readValueInterpolateBefore (
      int     aIndex, 
      double  aBeforeDeltaTime,
      double* aValue);

   // Read a sample value that is interpolated from a target time that is
   // calculated to be the time at an input index plus an input delta.
   // If the target time is not between the time at the input index and
   // the time of the next index then a upward search is performed 
   // until it is found.
   bool readValueInterpolateAfter (
      int     aIndex, 
      double  aBeforeDeltaTime,
      double* aValue);

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // More.

   void show();
};

//******************************************************************************
}//namespace

#endif

