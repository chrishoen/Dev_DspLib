/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspBoundCount.h"


namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

BoundCount::BoundCount()
{
   mCount = 0;
   mMin = 0;
   mMax = 0;
   mDetectFlag = false;
}
void BoundCount::reset()
{
   mCount = 0;
   mDetectFlag = false;
   mDetectRise = false;
   mDetectFall = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// If the count is less than the maximum, then increment it. If it
// reaches the maximum, set the detect flag true and return true.

bool BoundCount::increment()
{
   mDetectRise = false;
   mDetectFall = false;

   if (mCount < mMax)
   {
      if (++mCount == mMax)
      {
         mDetectFlag = true;
         mDetectRise = true;
         return true;
      }
   }
   return false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// If the count is greater than the minimum, then decrement it. If it
// reaches the minimim, set the detect flag false and return true.

bool BoundCount::decrement()
{
   mDetectRise = false;
   mDetectFall = false;

   if (mCount > mMin)
   {
      if (--mCount == mMin)
      {
         mDetectFlag = false;
         mDetectFall = true;
         return true;
      }
   }
   return false;
}

// If the input is true then increment, else decrement.
void BoundCount::update(bool aFlag)
{
   if (aFlag) increment();
   else       decrement();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

