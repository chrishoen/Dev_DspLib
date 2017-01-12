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

void TestOne::doRun1()
{
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

   // Input and output files.
   CsvFileWriter  tSampleWriter;

   tSampleWriter.open(gParms.mOutputFile);

   // Statistics
   TrialStatistics  mTrialStatistics;
   mTrialStatistics.startTrial();

   // Local
   Sample tSample;

   // Loop through all of the samples in the time series.
   for (int k = 0; k < gParms.mNumSamples; k++)
   {
      // Write the sample to the output file.
      tSampleWriter.writeRow(
         k,
         tTime->mT[k],
         tSeries->mX[k]);

      // Put sample to statistics.
      mTrialStatistics.put(tSeries->mX[k]);
    
   }

   Prn::print(0, "TestOne::doRun1 %d",gParms.mNumSamples);

   // Close files.
   tSampleWriter.close();

   // Finish statistics.
   mTrialStatistics.finishTrial();
   mTrialStatistics.show();

   // Done.
   delete tTime;
   delete tSeries;
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

