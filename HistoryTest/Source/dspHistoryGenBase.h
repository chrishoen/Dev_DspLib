#ifndef _DSPHISTORYGENBASE_H_
#define _DSPHISTORYGENBASE_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspHistory.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a base class for signal history generators.

class HistoryGenBase
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Input parameters.

   double  mDuration;     // Time duration of signal
   double  mFs;           // Sampling frequency

   double  mEX;           // Desired expectation
   double  mUX;           // Desired uncertainty

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Extra parameters.

   double  mTs;           // Sampling period
   int     mNumSamples;   // Number of samples in array

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Methods.

   // Constructor.
   HistoryGenBase();
   virtual void reset();
   virtual void show();

   // Initialize member variables. Initialize the history memory for the correct
   // number of samples. Set the history value array to zero and the time array
   // to linearly increasing.
   virtual void initializeHistory(History& aHistory);

   // Normalize the signal history to have the desired expectation and
   // uncertainty.
   void normalizeHistory(History& aHistory);

   // Abstract method, generate the signal history.
   // Type1 is  periodic, with   regular intersample arrival times.
   // Type2 is aperiodic, with irregular intersample arrival times.

   virtual void generateHistoryType1(History& aHistory)=0;
   virtual void generateHistoryType2(History& aHistory)=0;

};

//******************************************************************************
}//namespace

#endif

