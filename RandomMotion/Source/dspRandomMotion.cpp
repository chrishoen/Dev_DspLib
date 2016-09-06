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

#define  _DSPFILTERTESTER_CPP_
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

   mAp1 = 0.01;
   mAp2 = 1.0 - mAp1;
   mAp3 = 0.0;

   mWindowSampleSize = 100;
   mWindowTimeSize = 0.100;

   mInputFileName[0]=0;
   mOutputFileName [0]=0;
}

void MotionParms::initialize()
{
   mTs = 1.0 / mFs;
   mNumSamples = (int)(round(mDuration) * mFs);

   mWindowSampleSize = (int)(mWindowTimeSize * mFs);
// Prn::print(0,"MotionParms.mWindowTimeSize   %10.5f",mWindowTimeSize);
// Prn::print(0,"MotionParms.mWindowSampleSize %10d",  mWindowSampleSize);
}

void MotionParms::setInputFileName  (char* aFileName) { strcpy(mInputFileName,  aFileName); }
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

void RandomMotion::testAlphaOne(MotionParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();
   // Initialize filter.
   mAlphaOne.initialize(aParms->mAp1);

   // Input and output files.
   CsvFileReader  tSampleReader;
   CsvFileWriter  tSampleWriter;

   tSampleReader.open(aParms->mInputFileName);
   tSampleWriter.open(aParms->mOutputFileName);

   // Local
   int tSampleCount = 0;
   Sample tSample;

   // Loop through all of the samples in the input file.
   while (true)
   {
      // Read sample row from input file
      if(!tSampleReader.readRow()) break;

      // Convert input and store in sample temp.
      tSample.put(tSampleReader(0),tSampleReader(1));

      // Put sample to filter
      mAlphaOne.put(tSample.mVolts);

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tSampleCount,
         tSample.mTime,
         tSample.mVolts,
         mAlphaOne.mXX);
      tSampleCount++;
   }

   Prn::print(0, "TestAlphaOne %d",tSampleCount);
   // Close files.
   tSampleReader.close();
   tSampleWriter.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void RandomMotion::testAlphaTwo(MotionParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();
   // Initialize filter.
   mAlphaTwo.initialize(aParms->mAp1,aParms->mAp2,aParms->mTs);

   // Input and output files.
   CsvFileReader  tSampleReader;
   CsvFileWriter  tSampleWriter;

   tSampleReader.open(aParms->mInputFileName);
   tSampleWriter.open(aParms->mOutputFileName);

   // Local
   int tSampleCount = 0;
   Sample tSample;

   // Loop through all of the samples in the input file.
   while (true)
   {
      // Read sample row from input file
      if(!tSampleReader.readRow()) break;

      // Convert input and store in sample temp.
      tSample.put(tSampleReader(0),tSampleReader(1));

      // Put sample to filter
      mAlphaTwo.put(tSample.mVolts);

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tSampleCount,
         tSample.mTime,
         tSample.mVolts,
         mAlphaTwo.mXX,
         mAlphaTwo.mXV);
      tSampleCount++;
   }

   Prn::print(0, "TestAlphaTwo %d",tSampleCount);
   // Close files.
   tSampleReader.close();
   tSampleWriter.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void RandomMotion::testAlphaThree(MotionParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();
   // Initialize filter.
   mAlphaThree.initialize(aParms->mAp1,aParms->mAp2,aParms->mAp3,aParms->mTs);

   // Input and output files.
   CsvFileReader  tSampleReader;
   CsvFileWriter  tSampleWriter;

   tSampleReader.open(aParms->mInputFileName);
   tSampleWriter.open(aParms->mOutputFileName);

   // Local
   int tSampleCount = 0;
   Sample tSample;

   // Loop through all of the samples in the input file.
   while (true)
   {
      // Read sample row from input file
      if(!tSampleReader.readRow()) break;

      // Convert input and store in sample temp.
      tSample.put(tSampleReader(0),tSampleReader(1));

      // Put sample to filter
      mAlphaThree.put(tSample.mVolts);

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tSampleCount,
         tSample.mTime,
         tSample.mVolts,
         mAlphaThree.mXX,
         mAlphaThree.mXV);
      tSampleCount++;
   }

   Prn::print(0, "TestAlphaThree %d",tSampleCount);
   // Close files.
   tSampleReader.close();
   tSampleWriter.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void RandomMotion::testAlphaStatistics(MotionParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();
   // Initialize filter.
   mAlphaStatistics.initialize(aParms->mAp1);

   // Input and output files.
   CsvFileReader  tSampleReader;
   CsvFileWriter  tSampleWriter;

   tSampleReader.open(aParms->mInputFileName);
   tSampleWriter.open(aParms->mOutputFileName);

   // Local
   int tSampleCount = 0;
   Sample tSample;

   // Loop through all of the samples in the input file.
   while (true)
   {
      // Read sample row from input file
      if(!tSampleReader.readRow()) break;

      // Convert input and store in sample temp.
      tSample.put(tSampleReader(0),tSampleReader(1));

      // Put sample to filter
      mAlphaStatistics.put(tSample.mVolts);

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tSampleCount,
         tSample.mTime,
         tSample.mVolts,
         mAlphaStatistics.mEX,
         mAlphaStatistics.mUX);
      tSampleCount++;
   }

   Prn::print(0, "TestAlphaStatistics %d",tSampleCount);
   // Close files.
   tSampleReader.close();
   tSampleWriter.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void RandomMotion::testMovingAverage(MotionParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();
   // Initialize filter.
   mMovingAverage.initialize(aParms->mWindowSampleSize);

   // Input and output files.
   CsvFileReader  tSampleReader;
   CsvFileWriter  tSampleWriter;

   tSampleReader.open(aParms->mInputFileName);
   tSampleWriter.open(aParms->mOutputFileName);

   // Local
   int tSampleCount = 0;
   Sample tSample;

   // Loop through all of the samples in the input file.
   while (true)
   {
      // Read sample row from input file
      if(!tSampleReader.readRow()) break;

      // Convert input and store in sample temp.
      tSample.put(tSampleReader(0),tSampleReader(1));

      // Put sample to filter
      mMovingAverage.put(tSample.mVolts);

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tSampleCount,
         tSample.mTime,
         tSample.mVolts,
         mMovingAverage.mEX,
         mMovingAverage.mUX);
      tSampleCount++;
   }

   Prn::print(0, "TestMovingAverage %d %s",tSampleCount,aParms->mInputFileName);
   // Close files.
   tSampleReader.close();
   tSampleWriter.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void RandomMotion::trial11(MotionParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();

   // Start statistics.
   mTrialStatistics.startTrial();

   // Input file.
   CsvFileReader  tSampleReader;

   tSampleReader.open(aParms->mInputFileName);

   // Local
   int tSampleCount = 0;
   int tRowIndex = 0;
   Sample tSample;

   // Loop through all of the samples in the input file.
   while (true)
   {
      // Read sample row from input file
      if(!tSampleReader.readRow()) break;
      tRowIndex = tSampleReader.mRowIndex;

      // Convert input and store in sample temp.
      tSample.put(tSampleReader(0),tSampleReader(1));

      // Put sample to statistics.
      mTrialStatistics.put(tSample.mVolts);

      // Update.
      tSampleCount++;
   }

   // Finish statistics.
   mTrialStatistics.finishTrial();

   Prn::print(0, "Trial11 %d %s",tSampleCount,aParms->mInputFileName);
   mTrialStatistics.show();
   // Close files.
   tSampleReader.close();
}

//******************************************************************************   
}//namespace