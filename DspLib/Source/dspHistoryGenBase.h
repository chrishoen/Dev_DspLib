#pragma once

/*==============================================================================
Base class for signal history generators, used to generate artificial histories.
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
// This is a base class for signal history generators, which are used to 
// generate artificial histories. Different inheritors generate different kinds
// of signals. Sampling times for histories can be one of two types:
// Type1 is  periodic, with   regular intersample arrival times.
// Type2 is aperiodic, with irregular intersample arrival times.

class HistoryGenBase
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Parameters. These are read from a parms file.

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
   void initializeHistoryType1(History& aHistory);
   void initializeHistoryType2(History& aHistory);

   // Abstract method, generate the history with an artificial signal.
   // Type1 is  periodic, with   regular intersample arrival times.
   // Type2 is aperiodic, with irregular intersample arrival times.
   virtual void generateHistoryType1(History& aHistory)=0;
   virtual void generateHistoryType2(History& aHistory)=0;

   // Based on the parms, this calls one of the above, Type1 or Type2.
   void generateHistory(History& aHistory);

   // Add gaussian noise to the history sample values.
   void addNoise(History& aHistory);

   // Normalize the signal history to have the desired expectation and
   // uncertainty.
   void normalizeHistory(History& aHistory);

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


