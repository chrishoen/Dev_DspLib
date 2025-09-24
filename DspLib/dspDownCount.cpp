/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspDownCount.h"


namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

DownCount::DownCount()
{
   mInitialCount = 0;
   reset();
}
void DownCount::reset()
{
   mFirstFlag = true;
   mCount = 0;
   mTriggerFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Load the count at an initial count.
void DownCount::load(int aInitialCount)
{
   reset();
   mInitialCount = aInitialCount;
   mCount = mInitialCount;
}

// Reload the count at the initial count.
void DownCount::load()
{
   reset();
   mCount = mInitialCount;
}

// Decrement down to zero and set the trigger flag.
// If the initial count is zero then trigger immediately the first
// time. If the initial count is not zero then decrement down to
// zero and trigger when it reaches zero. Stop decrementing after
// that. Return the trigger.
bool DownCount::decrement()
{
   mTriggerFlag = false;
   if (mInitialCount == 0)
   {
      if (mFirstFlag) mTriggerFlag = true;
   }
   else
   {
      if (mCount) if (--mCount == 0) mTriggerFlag = true;
   }
   mFirstFlag = false;
   return mTriggerFlag;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

