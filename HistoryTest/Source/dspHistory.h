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

   // Current write index.
   int     mWriteIndex;

   // Boundary indices and times.
   int    mBeginIndex;
   int    mEndIndex;
   double mBeginTime;
   double mEndTime;


   // The index and time of the last executed read operation.
   int    mReadIndex;
   double mReadTime;

   // If true then memory has been allocated.
   bool mMemoryFlag;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Constructor and initialization.

   // Constructor.
   History();
  ~History();
  void resetVariables();

   // Allocate memory.
   void initialize(int aMaxSamples);

   // Deallocate memory.
   void finalize();

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Write to the history.

   // Start writing a signal history. This resets member variables.
   void startWrite();

   // Finish writing a signal history.
   void finishWrite();
      
   // Write a sample to the signal history and advance the index.
   void writeSample(double aTime,double aValue);

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Read values from the signal history, based on index.

   // Read a sample at a particular index.
   bool readValueAtIndex  (int aIndex,double* aValue);
   bool readTimeAtIndex   (int aIndex,double* aTime);
   bool readSampleAtIndex (int aIndex,double* aTime,double* aValue);

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Read values from the signal history, based on time.
   // This is used in loops that process type2 signal histories. Samples are read
   // from the history at monotically increasing times. The read is advanced
   // through the history arrays and an interpolated value between array entries
   // is returned.

   // Start read.
   void startReadAtTime();

   // Read value at a specific time. This is called repeatedly in a loop where the
   // read time is monotonic increasing. An interpolated value between array
   // entries is returned.
   double readValueAtTime(double aReadTime);

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // More.

   void show();
};

//******************************************************************************
}//namespace

#endif

