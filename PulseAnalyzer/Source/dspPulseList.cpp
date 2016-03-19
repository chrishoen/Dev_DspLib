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
   reset();
}

void PulseList::reset()
{
   mMaxNumOfElements = 10000;
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

void PulseList::initialize()
{
   // If memory is already allocated then deallocate it.
   finalize();

   // Initialize queue
   mQueue.initialize(mMaxNumOfElements);

   // Window limits
   mWindowTimeLowerLimit = 0.0;
   mWindowTimeUpperLimit = 0.0;
   mWindowTimeSize       = 1.0;

}

//******************************************************************************
// Deallocate the queue memory.

void PulseList::finalize()
{
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
   Pdw* tRemovedPdw=0;
   if (!mQueue.isPut())
   {
      tRemovedPdw = removeOldestPdw();
   }

   // Put the pdw to the queue to add it to the list
   mQueue.put(aPdw);

   // Done
   return tRemovedPdw;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Remove the oldest pdw from the top of the list.

Pdw* PulseList::removeOldestPdw()
{
   // If the list is empty then return null.
   if (!mQueue.isGet())
   {
      return 0;
   }

   // Get queue element to remove the pdw from the list.
   Pdw* tRemovedPdw;
   mQueue.get(tRemovedPdw);

   // Done
   return tRemovedPdw;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update the list window lower and upper limits. If the oldest pdw in the
// list is older than the window lower limit then it has fallen outside of
// the window. In that case, remove and return it.

Pdw* PulseList::updateTime(double aTime)
{
   // Peek at the oldest element in the array, the top of the list, the element at 
   // the GetIndex.
   Pdw* tPdw = mQueue.elementToGet();

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
// Return the queue size.

int PulseList::size()
{
   return mQueue.size();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace