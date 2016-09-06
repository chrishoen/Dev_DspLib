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
#include "dspSignalSourceLPGN.h"

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

   mAmplitude = 1.0;
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

void RandomMotion::propagate(MotionParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();

   // Initialize signal source.
   SignalSourceLPGN* tSource = new SignalSourceLPGN();
   tSource->mFs         =     aParms->mFs;
   tSource->mFp         =     aParms->mFp;
   tSource->mSigma      =     aParms->mSigma;
   tSource->mOffset     =     aParms->mOffset;
   tSource->mAmplitude  =     aParms->mAmplitude;
   tSource->initialize();

   // Input and output files.
   CsvFileWriter  tSampleWriter;

   tSampleWriter.open(aParms->mOutputFileName);

   // Local
   int tSampleCount = 0;
   Sample tSample;

   // Loop through all of the samples in the input file.
   do
   {
      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tSampleCount,
         tSource->mT,
         tSource->mX);

      // Advance the sample.
      tSource->advance();

   } while (++tSampleCount < aParms->mNumSamples);

   Prn::print(0, "TestAlphaOne %d",tSampleCount);

   // Close files.
   tSampleWriter.close();
}

//******************************************************************************   
}//namespace
