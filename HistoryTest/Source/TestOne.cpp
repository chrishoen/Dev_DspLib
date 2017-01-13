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

   // Loop through all of the samples in the history.
   for (int k = 0; k < tHistory.mMaxSamples; k++)
   {
      double tTime  = 0.0;
      double tValue = 0.0;

      // Get a sample from the history.
      tHistory.readSampleAtIndex(k,&tTime,&tValue);

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         k,
         tTime,
         tValue);
   }

   // Close the output file.
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "TestOne::doRun1 %d",tHistory.mMaxSamples);
}

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
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistory1);
   tStatistics.show();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Another signal history.

   History tHistory2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Transfer the signal history1 to signal history2, with a delay.

   historyCopyWithDelay(
      tHistory1,
      gParms.mHistoryDeltaT,
      tHistory2);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal histories to the output file.

   CsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);

   // Loop through all of the samples in the time series.
   for (int k = 0; k < gParms.mHistoryMaxSamples; k++)
   {
      double tTime1  = 0.0;
      double tTime2  = 0.0;
      double tValue1 = 0.0;
      double tValue2 = 0.0;

      // Get the samples from both histories.
      tHistory1.readSampleAtIndex(k,&tTime1,&tValue1);
      tHistory2.readSampleAtIndex(k,&tTime2,&tValue2);

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         k,
         tTime1,
         tValue1,
         tValue2);
   }

   // Close the output file.
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "TestOne::doRun2 %d",gParms.mHistoryMaxSamples);

}

