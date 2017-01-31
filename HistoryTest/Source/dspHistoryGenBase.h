#ifndef _DSPHISTORYGENBASE_H_
#define _DSPHISTORYGENBASE_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspHistory.h"
#include "dspHistoryGenParms.h"

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
   // Parameters.

   HistoryGenParms mParms;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Methods.

   // Constructor.
   HistoryGenBase();
   virtual void reset();
   virtual void show();

   // Initialize member variables. Allocate the history memory for the correct
   // number of samples, according to the parameters. Set the history value array
   // to zero and the time array to linearly increasing.
   // Type1 is  periodic, with   regular intersample arrival times.
   // Type2 is aperiodic, with irregular intersample arrival times.
   virtual void initializeHistoryType1(History& aHistory);
   virtual void initializeHistoryType2(History& aHistory);

   // Abstract method, generate the signal history.
   // Type1 is  periodic, with   regular intersample arrival times.
   // Type2 is aperiodic, with irregular intersample arrival times.
   virtual void generateHistoryType1(History& aHistory)=0;
   virtual void generateHistoryType2(History& aHistory)=0;

   // Normalize the signal history to have the desired expectation and
   // uncertainty.
   void normalizeHistory(History& aHistory);

};

//******************************************************************************
}//namespace

#endif

