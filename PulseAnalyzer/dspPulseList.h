#ifndef _DSPPULSELIST_H_
#define _DSPPULSELIST_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "ccValueQueue.h"
#include "dspPdw.h"
#include "dspSample.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This maintains a list of pdws (pulse descriptor words) for pulses that have
// recently arrived, typically during the last 100 milliseconds. It establishes
// a sliding window of pdws. The list is updated at the sample rate. If a pulse
// has arrived then it is added to the list. If the oldest pdw in the list
// falls outside of the window then it is removed from the list.

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

   // Reset paramters to defaults.
   void reset();

   // Parameters
   int mMaxNumOfElements;

   // Initialize, using the parameters. Allocate queue memory.
   void initialize();

   // Deallocate queue memory.
   void finalize();

   // Put a new pdw to the bottom of the list. If the list is full, then 
   // remove the oldest pdw from the top of  the list and return it. If it is 
   // not full, then return null. This is called by the pulse analyzer at the
   // sample rate, if a new pulse has been detected by the pulse detector.
   Pdw* addNewPdw(Pdw* aPdw);

   // Remove the oldest pdw from the top of the list.
   Pdw* removeOldestPdw();

   // Update the list window lower and upper limits. If the oldest pdw in the
   // list is older than the window lower limit then it has fallen outside of
   // the window. In that case, remove and return it. This is called at the
   // sample rate by the pulse analyzer front end.
   Pdw* updateTime(double aTime);

   // Return the current number of pdws in the list, which is the queue size.
   int size();

   // Return the current pulse density, which is the queue size divided by
   // the window size.
   double density();

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Queue of pdw pointers

   CC::ValueQueue<Pdw*> mQueue;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Members

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