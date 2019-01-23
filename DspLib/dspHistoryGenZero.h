#pragma once

/*==============================================================================
Signal history generator with a constant zero function.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspHistoryGenBase.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class for a signal history generators that generates a zero value
// signal.

class HistoryGenZero : public HistoryGenBase
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   typedef HistoryGenBase BaseClass;
   HistoryGenZero(HistoryGenParms& aParms);
   void show();

   // Generate the signal history according to the parameters.
   // Type1 is  periodic, with   regular intersample arrival times.
   // Type2 is aperiodic, with irregular intersample arrival times.
   void generateHistoryType1(History& aHistory) override; 
   void generateHistoryType2(History& aHistory) override;

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


