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
   // Generated signal history.

   // Signal history.
   History tHistory;

   // Signal history generator.
   HistoryGenWiener tGen;
   // Set parameters.
   tGen.mParms = gParms.mHistoryGenWiener;
   // Generate the history.
   tGen.generate(tHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   TrialStatistics  tTrialStatistics;

   // Start the statistics.
   tTrialStatistics.startTrial();

   // Loop through all of the samples in the history.
   for (int k = 0; k < tHistory.mMaxSamples; k++)
   {
      // Put history value to statistics.
      tTrialStatistics.put(tHistory.mValue[k]);
   }

   // Finish the statistics.
   tTrialStatistics.finishTrial();
   tTrialStatistics.show();

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

void TestOne::doRun2()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Input time series.

   // Initialize signal time series.
   TimeSeriesTime* tTime   = new TimeSeriesTime();
   TimeSeriesLPGN* tSeries = new TimeSeriesLPGN();

   tTime->mDuration     =     gParms.mDuration;
   tTime->mFs           =     gParms.mFs;
   tTime->generate();

   tSeries->reset();
   tSeries->mDuration   =     gParms.mDuration;
   tSeries->mN          =     gParms.mFilterOrder;
   tSeries->mFs         =     gParms.mFs;
   tSeries->mFc         =     gParms.mFc;
   tSeries->mEX         =     gParms.mEX;
   tSeries->mUX         =     gParms.mUX;
   tSeries->initialize();
   tSeries->show();
   tSeries->generate();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Statistics.

   // Statistics
   TrialStatistics  tTrialStatistics;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Signal histories.

   History tHistory1;
   History tHistory2;

   tHistory1.initialize(gParms.mHistoryMaxSamples);
   tHistory2.initialize(gParms.mHistoryMaxSamples);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Transfer the time series to signal history1.

   // Start the history.
   tHistory1.startHistory();

   // Start statistics.
   tTrialStatistics.startTrial();

   // Loop through all of the samples in the time series.
   for (int k = 0; k < gParms.mHistoryMaxSamples; k++)
   {
      // Copy the the time series sample to the signal history.
      tHistory1.writeSample(
         tTime->mT[k],
         tSeries->mX[k]);

      // Put sample to statistics.
      tTrialStatistics.put(tSeries->mX[k]);
   }

   // Finish the history.
   tHistory1.finishHistory();

   // Finish statistics.
   tTrialStatistics.finishTrial();
   tTrialStatistics.show();

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

   // Done.
   delete tTime;
   delete tSeries;
}

