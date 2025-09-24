#pragma once

/*==============================================================================

Down counter. 

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class implements a one shot down counter. It starts at an initial
// value and decrements down to zero and stops. When it reaches zero it sets
// a trigger flag. If the initial count is zero then it sets the trigger flag
// the first time it is updated.

class DownCount
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Initial count.
   int mInitialCount;
   bool mFirstFlag;

   // Counter.
   int mCount;

   // Set true once when the counter reaches the zero.
   bool mTriggerFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   DownCount();
   void reset();

   // Load the count at an initial count.
   void load(int aInitialCount);
   // Reload the count at the initial count.
   void load();

   // Decrement down to zero and set the trigger flag.
   // If the initial count is zero then trigger immediately the first
   // time. If the initial count is not zero then decrement down to
   // zero and trigger when it reaches zero. Stop decrementing after
   // that.
   bool decrement();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

