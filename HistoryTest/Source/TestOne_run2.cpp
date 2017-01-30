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

#include "dspSample.h"
#include "dspTextFile.h"
#include "dspStatistics.h"
#include "dspTimeSeriesTime.h"
#include "dspTimeSeriesLPGN.h"
#include "dspHistory.h"
#include "dspHistoryOps.h"
#include "dspHistoryGenWiener.h"
#include "dspHistoryStatistics.h"
#include "dspHistoryLoopClock.h"

#include "Parms.h"
#include "TestOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun2()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistory1;

   // Signal history generator.
   HistoryGenWiener tGen(gParms.mHistoryGenWiener);

   // Generate the history.
   tGen.generateHistory(tHistory1);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistory2;

   // Generate the history.
   historyCopyWithDelay(
      tHistory1,
      gParms.mHistoryDeltaT,
      tHistory2);

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
   CsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);

   // Loop clock.
   HistoryLoopClock tClock(
      gParms.mHistoryGenWiener.mDuration,
      gParms.mHistoryGenWiener.mFs);

   // Start read.
   tHistory1.startReadAtTime();
   tHistory2.startReadAtTime();

   // Loop through all of the samples in the history.
   do
   {
      int    tIndex = tClock.mCount;
      double tTime  = tClock.mTime;
      double tValue1 = 0.0;
      double tValue2 = 0.0;

      // Get a sample from the history.
      tValue1 = tHistory1.readValueAtTime(tTime);
      tValue2 = tHistory2.readValueAtTime(tTime);

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tIndex,
         tTime,
         tValue1,
         tValue2);
   } while (tClock.advance());

   // Close the output file.
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "TestOne::doRun2 %d",tHistory1.mMaxSamples);
}

