/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspHistoryGenZero.h"
#include "dspHistoryGenStep.h"
#include "dspHistoryGenSinWave.h"
#include "dspHistoryGenRandWave.h"

#include "dspHistoryGenerator.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryGenerator::HistoryGenerator(HistoryGenParms& aParms)
{
   mParms = aParms;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryGenerator::show()
{
   mParms.show("HistoryGenerator");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate the signal history according to the parameters. This is a jump 
// table that selects one of the concrete history generators according to
// the generator type parameter and uses it to generate a history.

void HistoryGenerator::generateHistory(History& aHistory)
{
   switch (mParms.mGenType)
   {
   case HistoryGenParms::cGenZero :
   {
      HistoryGenZero tGen(mParms);
      tGen.generateHistory(aHistory);
   }
   break;
   case HistoryGenParms::cGenStep :
   {
      HistoryGenStep tGen(mParms);
      tGen.generateHistory(aHistory);
   }
   break;
   case HistoryGenParms::cGenSinWave :
   {
      HistoryGenSinWave tGen(mParms);
      tGen.generateHistory(aHistory);
   }
   break;
   case HistoryGenParms::cGenRandWave :
   {
      HistoryGenRandWave tGen(mParms);
      tGen.generateHistory(aHistory);
   }
   break;
   }
}

}//namespace