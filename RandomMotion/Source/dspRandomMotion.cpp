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
#include "dspTimeSeriesFilteredGN.h"
#include "dspTimeSeriesHarmonic.h"

#include "Parms.h"
#include "FilterCo.h"
#include "dspRandomMotion.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

RandomMotion::RandomMotion()
{
   initialize();
}

void RandomMotion::initialize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void RandomMotion::propagate1()
{
   // Initialize signal time series.
   TimeSeriesTime* tTime   = new TimeSeriesTime();
   TimeSeriesLPGN* tSeries = new TimeSeriesLPGN();

   tTime->mDuration     =     gParms.mDuration;
   tTime->mFs           =     gParms.mFs;
   tTime->generate();

   tSeries->mDuration   =     gParms.mDuration;
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

   // Loop through all of the samples in the input file.
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

   Prn::print(0, "RandomMotion::propagate1 %d",gParms.mNumSamples);

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

void RandomMotion::propagate2()
{
   // Initialize signal time series.
   TimeSeriesTime* tTime   = new TimeSeriesTime();
   TimeSeriesHarmonic* tSeries = new TimeSeriesHarmonic();

   tTime->mDuration     =     gParms.mDuration;
   tTime->mFs           =     gParms.mFs;
   tTime->generate();

   tSeries->mDuration   =     gParms.mDuration;
   tSeries->mFs         =     gParms.mFs;
   tSeries->mEX         =     gParms.mEX;
   tSeries->mUX         =     gParms.mUX;

   tSeries->mFc1        =     gParms.mFc1;
   tSeries->mFc2        =     gParms.mFc2;
   tSeries->mAc1        =     gParms.mAc1;
   tSeries->mAc2        =     gParms.mAc2;
   tSeries->mPc1        =     gParms.mPc1;
   tSeries->mPc2        =     gParms.mPc2;

   tSeries->mFcRandom   =     gParms.mFcRandom;
   tSeries->mAcRandom   =     gParms.mAcRandom;
   tSeries->mPcRandom   =     gParms.mPcRandom;

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

   // Loop through all of the samples in the input file.
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

   Prn::print(0, "RandomMotion::propagate1 %d",gParms.mNumSamples);

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

void RandomMotion::propagate3()
{
   // Initialize signal time series.
   TimeSeriesTime* tTime   = new TimeSeriesTime();
   TimeSeriesFilteredGN* tSeries = new TimeSeriesFilteredGN();

   tTime->mDuration     =     gParms.mDuration;
   tTime->mFs           =     gParms.mFs;
   tTime->generate();

   tSeries->mDuration   =     gParms.mDuration;
   tSeries->mFs         =     gParms.mFs;
   tSeries->mEX         =     gParms.mEX;
   tSeries->mUX         =     gParms.mUX;
   tSeries->mBSize      =     gFilterCo.mBandPassB1.mRows;
   tSeries->mASize      =     gFilterCo.mBandPassA1.mRows;
   tSeries->mBArray     =     gFilterCo.mBandPassB1.mValues;
   tSeries->mAArray     =     gFilterCo.mBandPassA1.mValues;
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

   // Loop through all of the samples in the input file.
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

   Prn::print(0, "RandomMotion::propagate3 %d",gParms.mNumSamples);

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
}//namespace
