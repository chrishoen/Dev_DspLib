#pragma once

/*==============================================================================
Signal history statistics.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspHistory.h"
#include "dspStatistics.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is used to collect statistics on a signal history.

class HistoryStatistics : public Dsp::TrialStatistics
{
public:

   typedef Dsp::TrialStatistics BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Collect trial statistics on the value array of a signal history.
   void addValue(History& aHistory);

   // Collect trial statistics on the value array of a signal history.
   // Exclude values that are not within a region of interest defined
   // from begin time + exclusion to end time - exclusion.
   void addValue(History& aHistory, double aTimeExclusion);

   // Same as add value, but does a start and finish.
   void collectValue(History& aHistory);

   // Same as add value, but does a start and finish.
   void collectValue(History& aHistory, double aTimeExclusion);

   // Collect trial statistics on the time array of a signal history.
   void collectTime(History& aHistory);

};

//******************************************************************************
}//namespace


