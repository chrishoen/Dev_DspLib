/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include "my_functions.h"
#include "prnPrint.h"
#include "dspPdwFreeList.h"
#include "dspPulseList.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This initializes the queue to a fixed size. It initializes member variables
// and allocates heap storage for the queue array. The queue has a specified 
// maximum number of elements and it allocates memory for the maximum number
// of elements plus one, there is an extra element allocated.

PulseList::PulseList()
{
   // All null
   mAllocate = 0;
   mPutIndex = 0;
   mGetIndex = 0;
   mArray  = 0;
}

//******************************************************************************
// Destructor, deallocate the queue array

PulseList::~PulseList()
{
   finalize();
}

//******************************************************************************
// Initialize the queue to a fixed size. Initializes member variables
// and allocate heap storage for the queue array. The queue has a specified 
// maximum number of elements and it allocates memory for the maximum number
// of elements plus one, there is an extra element allocated.

void PulseList::initialize(int aMaxNumOfElements)
{
   // If memory is already allocated then deallocate it.
   finalize();

   // Initialize variables
   mPutIndex = 0;
   mGetIndex = 0;
   // Allocate memory for the array to have an extra element
   mAllocate = aMaxNumOfElements + 1;

   // Allocate memory for the array
   mArray = new Pdw*[mAllocate];

   // Window limits
   mWindowTimeLowerLimit = 0.0;
   mWindowTimeUpperLimit = 0.0;
   mWindowTimeSize       = 1.0;

}

//******************************************************************************
// Deallocate the queue memory.

void PulseList::finalize()
{
   if (mArray)
   {
      delete mArray;
      mArray = 0;
   }
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This returns true if put operations are allowed. Puts are allowed if the 
// current size is less than or equal to Allocate - 2. If the size is equal to 
// Allocate - 2 then the next put operation would put the size to Allocate - 1, 
// which is the max number of elements. This is the same as "is not full".

bool PulseList::isPut ()
{
   int tSize = mPutIndex - mGetIndex;
   if (tSize < 0) tSize = mAllocate + tSize;
   return tSize <= mAllocate - 2;
}
   
//******************************************************************************
// This returns true if get operations are allowed. Gets are allowed if the 
// current size is greater than zero. This is the same as "is not empty".

bool PulseList::isGet ()
{
   int tSize = mPutIndex - mGetIndex;
   if (tSize < 0) tSize = mAllocate + tSize;
   return tSize > 0;
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put a new pdw to the bottom of the list. If the list is full, then
// remove the oldest pdw from the top of the list and return it. If it
// is not full, then it return null.

Pdw* PulseList::addNewPdw(Pdw* aPdw)
{
   // If the list is full then remove the oldest pdw from the top.
   Pdw* tPdw=0;
   if (!isPut())
   {
      tPdw = removeOldestPdw();
   }

   // Update the window limits.
   mWindowTimeUpperLimit = aPdw->mToa;
   mWindowTimeLowerLimit = mWindowTimeUpperLimit - mWindowTimeSize;

   // Local put index.
   int tPutIndex = mPutIndex;
   // Copy the source element into the element at the queue put index.
   mArray[tPutIndex] = aPdw;
   // Advance the put index.
   if(++tPutIndex == mAllocate) tPutIndex = 0;
   mPutIndex = tPutIndex;

   // Done
   return tPdw;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Remove the oldest pdw from the top of the list.

Pdw* PulseList::removeOldestPdw()
{
   // If the list is empty then return null.
   if (!isGet())
   {
      return 0;
   }

   // Local element.
   Pdw* tPdw;
   // Local index.
   int tGetIndex = mGetIndex;
   // Copy the queue array element at the get index into the destination element.
   tPdw = mArray[tGetIndex];
   // Advance the get index.
   if(++tGetIndex == mAllocate) tGetIndex = 0;
   mGetIndex = tGetIndex;
   // Done
   return tPdw;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update the list window lower and upper limits. If the oldest pdw in the
// list is older than the window lower limit then it has fallen outside of
// the window. In that case, remove and return it.

Pdw* PulseList::updateTime(double aTime)
{
   // The oldest element in the array, the top of the list, the element at 
   // the GetIndex.
   Pdw* tPdw = mArray[mGetIndex];

   // If the toa of the pdw is earlier than the window lower limit then it
   // has fallen outside of the window, so remove it.
   if (tPdw->mToa < mWindowTimeLowerLimit)
   {
      return removeOldestPdw();
   }
   // Else return null.
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace