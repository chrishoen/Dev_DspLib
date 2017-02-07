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

#include "dspHistory.h"
#include "dspHistoryStatistics.h"
#include "dspHistoryLoopClock.h"
#include "dspHistoryTextFile.h"
#include "dspHistoryGenGen.h"
#include "dspHistoryFilterOperator.h"

#include "Parms.h"
#include "DelayOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void DelayOne::doDelay2()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate two signal histories.

   // Signal history.
   History tHistory1;
   History tHistory2;

   // Generate two of the same signal.
   HistoryGenGen tGen1(gParms.mHistoryGenParms);
   tGen1.generateHistory(tHistory1);
   tHistory1.createClone(tHistory2);

   // Add noise to both.
   tHistory1.addNoise(gParms.mTestSigma);
   tHistory2.addNoise(gParms.mTestSigma);

   // Add time offset to number two.
   tHistory2.addDeltaTime(gParms.mTestDelay);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistory1);
   tStatistics.show();

   tStatistics.collectValue(tHistory2);
   tStatistics.show();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistory(tHistory1,tHistory2);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "DelayOne::doDelay2 %d",tHistory1.mMaxSamples);
}

