#ifndef _DSPPULSELIST_H_
#define _DSPPULSELIST_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspPdw.h"
#include "dspSample.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class PulseList
{
public:
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Interface

   // Constructor.
   PulseList();
  ~PulseList();

   // Allocate and initialize the queue memory.
   void initialize(int aMaxNumOfElements);
   // Deallocate the queue memory.
   void finalize();

   // Put a new pdw to the bottom of the list. If the list is full, then
   // remove the oldest pdw from the top of  the list and return it. If it
   // is not full, then it return null.
   Pdw* addNewPdw(Pdw* aPdw);

   // Remove the oldest pdw from the top of the list.
   Pdw* removeOldestPdw();

   // Update the list window lower and upper limits. If the oldest pdw in the
   // list is older than the window lower limit then it has fallen outside of
   // the window. In that case, remove and return it.
   Pdw* updateTime(double aTime);

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Queue methods

   // Return true if put operations are enabled, not full.
   bool isPut();
   // Return true if get operations are enabled, not empty.
   bool isGet();

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Members

   int mAllocate;
   int mPutIndex;
   int mGetIndex;

   Pdw** mArray;
   
   //---------------------------------------------------------------------------
   // Window time limits

   double mWindowTimeLowerLimit;
   double mWindowTimeUpperLimit;
   double mWindowTimeSize;

};

//******************************************************************************
}//namespace

#endif

#if 0

  999
         +---+
 1000    | 0 |     oldest, get, remove, head, top
         +---+
 1001    | 1 |
         +---+
 1002    | 2 |
         +---+
 1003    | 3 |     before
         +---+
 1004    | 4 |     after
         +---+
 1005    | 5 |
         +---+
 1006    | 6 |
         +---+
 1007    | 7 |     newest, put, add, tail, bottom
         +---+
 1008

 time
  |
  |
  v
 

#endif