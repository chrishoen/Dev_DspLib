/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"
#include "logFiles.h"

#include "dspHistory.h"
#include "dspHistoryStatistics.h"
#include "dspHistoryCsvFileWriter.h"
#include "dspHistoryGenerator.h"
#include "dspHistoryFilterOperator.h"
#include "dspHistoryDelayEstimator.h"

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
   HistoryGenerator tGen1(gParms.mHistoryGenParms);
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
   tStatistics.show(0,"X1  ");

   tStatistics.collectValue(tHistory2);
   tStatistics.show(0,"X2  ");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write the histories to the output file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistory(tHistory1,tHistory2);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Estimate the delay between the two histories.
   Prn::print(0, "");

   HistoryDelayEstimator tDelayEstimator;

   double tEstimatedDelay = tDelayEstimator.search(
      &tHistory1,
      &tHistory2,
      gParms.mDelayEstimatorFs,
      gParms.mDelayEstimatorSearchDelay,
      gParms.mDelayEstimatorTolerance,
      gParms.mDelayEstimatorMaxIterations);


   Prn::print(0, "");
   Prn::print(0, "Test      Delay           %10.6f",gParms.mTestDelay);
   Prn::print(0, "Estimated Delay           %10.6f",tEstimatedDelay);
   Prn::print(0, "Error                     %10.6f",gParms.mTestDelay - tEstimatedDelay);
   Prn::print(0, "");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "DelayOne::doDelay2 %d",tHistory1.mMaxSamples);
}

