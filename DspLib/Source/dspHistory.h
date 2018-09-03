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
// sample values and times of arrival in dynamically allocated arrays.//

class HistoryMemoryControl;

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
   // Memory management control pointer.
   HistoryMemoryControl* mMemoryControl;

   // Maximum number of samples in array.
   int     mMaxSamples;
   double  mMaxDuration;

   // Number of samples in array.
   int     mNumSamples;

   // True if write is enabled.
   bool    mWriteEnable;
   // Current write index.
   int     mWriteIndex;

   // Boundary indices and times.
   int     mBeginIndex;
   int     mEndIndex;
   double  mBeginTime;
   double  mEndTime;
   double  mDuration;

   // The index and time of the last executed read operation.
   int     mReadIndex;
   double  mReadTime;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor and initialization.

   // Initialize variables. Do not allocate memory.
   History();
   void reset();

   // Decrement the resource counter. If it is zero then deallocate memory.
  ~History();
  void resetVariables();

   // Initialize variables, allocate memory, and increment the resource
   // counter.
   void initialize(int aMaxSamples,double aMaxDuration=0.0);

   // If memory was allocated then deallocate it.
   void finalize();

   // Increment the resource counter.
   void incrementResourceCount();

   // Decrement the resource counter. If it is zero then deallocate memory.
   void decrementResourceCount();

   // Return true if memory has been allocated.
   bool isValid();
   // Return resource count. If memory has not been allocated return -1.
   int  getResourceCount();

   // Copy constructor and assignment operator. Copy variables and data
   // pointers. Do not copy data. This makes a copy of a history variable 
   // that points to the same allocated memory
   History(const History& aRhs); 
   History& operator= (const History& aRhs); 

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write to the history.

   // Start writing a signal history. This resets member variables.
   void startWrite();

   // Finish writing a signal history.
   void finishWrite();
      
   // Write a sample to the signal history and advance the index.
   // Return true if sample was written successfully. Return if not,
   // i.e. if the history is full.
   bool writeSample(double aTime,double aValue);

   // Return true if the last write that was started is finished.
   bool writeFinished();

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

   // Add a time delta to all times in the history and to all time member
   // variables.
   void subtractDeltaTime(double aDeltaTime);

   // Add gaussian noise to the values.
   void addNoise(double aSigma);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Helpers.

   // Clone this history into a new one that has the same size and time array,
   // but has a zero value array.
   void createTimeClone(History& aY);

   // Clone this history into a new one that has the same size and time array
   // and value array. This is a deep copy.
   void createClone(History& aY);

   // Clone this history into a new one that has the same size and time array
   // and value array. This is a deep copy. This is undersampled according to
   // a frequency divisor. For example, if the frequency is two then it clones
   // into a buffer that has half the number of samples and has every other
   // time and value.
   void createUnderSampledClone(History& aY,int aFsDivisor);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // More.

   void show1(int aPrintFilter,char* aLabel);
   void show2(int aPrintFilter,char* aLabel);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


