#pragma once

/*==============================================================================
Signal history generator with a sin wave.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"

#include "dspHistoryGenParms.h"
#include "dspHistoryGenBase.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a generator for a signal history that evolves according
// to a sin wave.
 
class HistoryGenSinWave : public HistoryGenBase
{
public:
   typedef HistoryGenBase BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HistoryGenSinWave(HistoryGenParms& aParms);
   void show();

   // Generate the signal history according to the parameters.
   // Type1 is  periodic, with   regular intersample arrival times.
   // Type2 is aperiodic, with irregular intersample arrival times.
   void generateHistoryType1(History& aHistory) override;   
   void generateHistoryType2(History& aHistory) override;
};

//******************************************************************************
}//namespace


