#pragma once

/*==============================================================================

Bounded counter. 

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class implements a bounded counter. It can increment up to a
// maximum and decrement down to a minimum. It provides a flag that is
// set true when it reaches the maximum and is set false when it
// reaches the minimum.

class BoundCount
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Counter.
   int mCount;
   // Minimum.
   int mMin;
   // Maximum.
   int mMax;

   // Set true  when the counter reaches the maximum.
   // Set false when the counter reaches the minimum.
   bool mDetectFlag;
   // Rising and falling edges of detect flag.
   bool mDetectRise;
   bool mDetectFall;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   BoundCount();
   void reset();

   // If the count is less than the maximum, then increment it. If it
   // reaches the maximum, set the detect flag true and return true.
   bool increment();

   // If the count is greater than the minimum, then decrement it. If it
   // reaches the minimim, set the detect flag false and return true.
   bool decrement();

   // If the input is true then increment, else decrement.
   void update(bool aFlag);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

