#pragma once

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineFile.h"
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

class HistoryGenTime
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Input parameters.

   HistoryGenParms mParms;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Methods.

   // Constructor.
   HistoryGenTime(HistoryGenParms& aParms);
   void show();

   // Initialize the history memory for the correct number of samples. Set the
   // history value array to zero and the time array to linearly increasing. This 
   // has constant intersample arrival times.
   void initializeLinearTime(History& aHistory);

   // Initialize the history memory for the correct number of samples. Set the
   // history value array to zero and the time array to linearly increasing. This
   // has random intersample arrival times, based on an exponential random
   // distribution.
   void initializeRandomTime(History& aHistory);

};

//******************************************************************************
}//namespace


