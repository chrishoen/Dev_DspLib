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
#include "dspSignalSourceLPGN.h"
#include "dspTimeSeriesTime.h"
#include "dspTimeSeriesLPGN.h"

#include "dspRandomMotion.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

MotionParms::MotionParms()
{
   reset();
}

void MotionParms::reset()
{
   mFs = 10000.0;
   mTs = 1.0 / mFs;
   mDuration = 10.0;
   mNumSamples = (int)(mDuration * mFs);

   mFp = 1.0;
   mTp = 1.0 / mFp;

   mScale = 1.0;
   mSigma = 0.0;
   mOffset = 0.0;

   mOutputFileName [0]=0;
}

void MotionParms::initialize()
{
   mTs = 1.0 / mFs;
   mNumSamples = (int)(round(mDuration) * mFs);

}

void MotionParms::setOutputFileName (char* aFileName) { strcpy(mOutputFileName, aFileName); }
   
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

void RandomMotion::propagate1(MotionParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();

   // Initialize signal time series.
   TimeSeriesTime* tTime   = new TimeSeriesTime();
   TimeSeriesLPGN* tSeries = new TimeSeriesLPGN();

   tTime->mDuration     =     aParms->mDuration;
   tTime->mFs           =     aParms->mFs;
   tTime->generate();

   tSeries->mDuration   =     aParms->mDuration;
   tSeries->mFs         =     aParms->mFs;
   tSeries->mFp         =     aParms->mFp;
   tSeries->mSigma      =     aParms->mSigma;
   tSeries->mOffset     =     aParms->mOffset;
   tSeries->mScale      =     aParms->mScale;
   tSeries->initialize();
   tSeries->show();
   tSeries->generate();

   // Input and output files.
   CsvFileWriter  tSampleWriter;

   tSampleWriter.open(aParms->mOutputFileName);

   // Statistics
   TrialStatistics  mTrialStatistics;
   mTrialStatistics.startTrial();

   // Local
   Sample tSample;

   // Loop through all of the samples in the input file.
   for (int k = 0; k < aParms->mNumSamples; k++)
   {
      // Write the sample to the output file.
      tSampleWriter.writeRow(
         k,
         tTime->mT[k],
         tSeries->mX[k]);

      // Put sample to statistics.
      mTrialStatistics.put(tSeries->mX[k]);
    
   }

   Prn::print(0, "RandomMotion::propagate1 %d",aParms->mNumSamples);

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

void RandomMotion::propagate2(MotionParms* aParms)
{
}

//******************************************************************************   
}//namespace
