#pragma once

/*==============================================================================
Signal history loop clock
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a loop clock, an object that advances forward through
// time. It is used to provide a periodic time for sample processing loops.

class HistoryLoopClock
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   double  mDuration;     // Input time duration.
   double  mFs;           // Input sampling frequency

   double  mTime;         // Output advanced time.
   int     mCount;        // Output advanced count.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Intermediate Members.

   int     mMaxCount;     // Max count allowed.
   double  mTs;           // Sampling period.

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Constructor and parameter initialization.

   // Constructor.
   HistoryLoopClock(
      double aDuration, 
      double aFs);

   HistoryLoopClock(
      double aBeginTime, 
      double aEndTime, 
      double aFs);

   // Advance forward through time, updating the time and count variables.
   // Return false if the time duration has been reached. 
   bool advance();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



