/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <math.h>
#include "my_functions.h"
#include "prnPrint.h"
#include "logFiles.h"

#include "dspGoldSearch.h"
#include "DelayStub.h"

#include "Parms.h"
#include "DelayOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void DelayOne::doDelay1()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Delay stub.

   DelayStub tDelayStub;
   tDelayStub.mXAinitial     = gParms.mXAInitial;
   tDelayStub.mXBinitial     = gParms.mXBInitial;
   tDelayStub.mTolerance     = gParms.mTolerance;
   tDelayStub.mMaxIterations = gParms.mMaxIterations;

   double tDelay = tDelayStub.search();
   Prn::print(0, "DelayOne::doDelay1 %10.4f",tDelay);
}
