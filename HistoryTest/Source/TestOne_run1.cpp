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

TestOne::TestOne()
{
   initialize();
}

void TestOne::initialize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun1()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistory;

   // Signal history generator.
   HistoryGenWiener tGen(gParms.mHistoryGenWiener);

   // Generate the history.
   tGen.generateHistory(tHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistory);
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

   // Loop through all of the samples in the history.
   do
   {
      int    tIndex = tClock.mCount;
      double tTime  = tClock.mTime;
      double tValue = 0.0;

      // Get a sample from the history.
      tValue = tHistory.readValueAtTime(tTime);

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tIndex,
         tTime,
         tValue);
   } while (tClock.advance());

   // Close the output file.
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "TestOne::doRun1 %d",tHistory.mMaxSamples);
}

