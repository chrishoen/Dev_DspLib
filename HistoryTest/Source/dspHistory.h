#pragma once

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
// This class provides the history of a signal. It is used to store and process
// the samples of a periodic or aperiodic time series. It stores the signal
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

   // Current write index.
   int     mWriteIndex;

   // Boundary indices and times.
   int     mBeginIndex;
   int     mEndIndex;
   double  mBeginTime;
   double  mEndTime;

   // The index and time of the last executed read operation.
   int     mReadIndex;
   double  mReadTime;

   // If true then memory has been allocated.
   bool    mMemoryFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor and initialization.

   // Constructor.
   History();
  ~History();
  void resetVariables();

   // Allocate memory.
   void initialize(int aMaxSamples);

   // Deallocate memory.
   void finalize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write to the history.

   // Start writing a signal history. This resets member variables.
   void startWrite();

   // Finish writing a signal history.
   void finishWrite();
      
   // Write a sample to the signal history and advance the index.
   void writeSample(double aTime,double aValue);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read values from the signal history, based on index.

   // Read a sample at a particular index.
   bool readValueAtIndex  (int aIndex,double* aValue);
   bool readTimeAtIndex   (int aIndex,double* aTime);
   bool readSampleAtIndex (int aIndex,double* aTime,double* aValue);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read values from the signal history, based on time.
   // This is used in loops that process type2 signal histories. Samples are
   // read from the history at monotically increasing times. The read is
   // advanced through the history arrays and an interpolated value between
   // array entries is returned. The reads must occur in sequential access such
   // that the time of a read must be after the time of the previous read.

   // Start read.
   void startRead();

   // Read value at a specific time. This is called repeatedly in a loop where
   // the read time is monotonic increasing. An interpolated value between
   // array entries is returned. This allows a history to be approximated as a
   // continuous function of a real time variable.
   double readValueAtTime(double aReadTime);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Adjustments.

   // Add a time delta to all times in the history and to all time member
   // variables.
   void addDeltaTime(double aDeltaTime);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Helpers.

   // Clone this history into a new one that has the same size and time array,
   // but has a zero value array.
   void createTimeClone(History& aY);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // More.

   void show();
};

//******************************************************************************
}//namespace


