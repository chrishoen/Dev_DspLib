/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <random>

#include "dsp_math.h"
#include "dspStatistics.h"
#include "dspHistoryGenZero.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryGenZero::HistoryGenZero(HistoryGenParms& aParms)
{
   HistoryGenBase::mParms = aParms;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryGenZero::show()
{
   BaseClass::show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the signal history according to the parameters.

void HistoryGenZero::generateHistoryType1(History& aHistory)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize.

   // Initialize base class variables according to the parameters and 
   // initialize the history for the correct sample size with a zero value
   // array and a lineary increasing time array.
   BaseClass::initializeHistoryType1(aHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Add gaussian noise to the history sample array.

    BaseClass::addNoise(aHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Normalize the history to get the desired expectation and uncertainty.

   BaseClass::normalizeHistory(aHistory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the signal history according to the parameters.

void HistoryGenZero::generateHistoryType2(History& aHistory)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the history with Type2 sample timing. Random intersample
   // arrival times, zero values.

   BaseClass::initializeHistoryType2(aHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Add gaussian noise to the history sample array.

    BaseClass::addNoise(aHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Normalize the history to get the desired expectation and uncertainty.

   BaseClass::normalizeHistory(aHistory);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace