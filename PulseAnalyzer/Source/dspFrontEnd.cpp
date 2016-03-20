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

#include "dspPdwFreeList.h"

#define  _DSPFRONTEND_CPP_
#include "dspFrontEnd.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

FrontEndParms::FrontEndParms()
{
   reset();
}

void FrontEndParms::reset()
{
   mFs = 10000.0;
   mTs = 1.0 / mFs;
   mDuration = 10.0;
   mNumSamples = (int)(mDuration * mFs);

   mDetectYesThreshold = 0.01;
   mDetectNoThreshold = 0.01;

   mListMaxNumOfElements = 10000;
   mListWindowTimeSize = 0.100;

   mInputFileName[0]=0;
   mOutputFileName [0]=0;
}

void FrontEndParms::initialize()
{
   mTs = 1.0 / mFs;
   mNumSamples = (int)(round(mDuration) * mFs);
}

void FrontEndParms::setInputFileName  (char* aFileName) { strcpy(mInputFileName,  aFileName); }
void FrontEndParms::setOutputFileName (char* aFileName) { strcpy(mOutputFileName, aFileName); }
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

FrontEnd::FrontEnd()
{
   initialize();
}

void FrontEnd::initialize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void FrontEnd::detect1(FrontEndParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();
   // Initialize detector.
   mPulseDetector.reset();
   mPulseDetector.mDetectYesThreshold = aParms->mDetectYesThreshold;
   mPulseDetector.mDetectNoThreshold  = aParms->mDetectNoThreshold;
   mPulseDetector.mSamplePeriod       = aParms->mTs;
   mPulseDetector.initialize();

   // Input and output files.
   Ris::CsvFileReader tSampleReader;
   PdwCsvFileWriter   tPdwWriter;

   tSampleReader.open(aParms->mInputFileName);
   tPdwWriter.open(aParms->mOutputFileName);

   // Local
   int tSampleCount = 0;
   int tRowIndex = 0;
   int tPdwCount = 0;
   Sample tSample;

   // Loop through all of the samples in the input file.
   while (true)
   {
      // Read sample row from input file
      if(!tSampleReader.readRow()) break;
      tRowIndex = tSampleReader.mRowIndex;
      tSampleCount++;

      // Convert input and store in sample temp.
      tSample.put(tSampleReader(0),tSampleReader(1));

      // Put the sample to the pulse detector.
      // It returns a pdw if it detects a pulse.
      Pdw* tPdw = mPulseDetector.putSample(&tSample);

      // If a pulse was detected
      if (tPdw)
      {
         // Update
         tPdwCount++;

         // Write the detected pdw to the output file
         tPdw->mIndex = tRowIndex;
         tPdwWriter.writePdw(tPdw);

         // Free the pdw.
         freePdw(tPdw);
      }
   }

   Prn::print(0, "Detect1 %d %d",tSampleCount,tPdwCount);
   // Close files.
   tSampleReader.close();
   tPdwWriter.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void FrontEnd::analyze11(FrontEndParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();

   // Initialize pulse detector.
   mPulseDetector.reset();
   mPulseDetector.mDetectYesThreshold = aParms->mDetectYesThreshold;
   mPulseDetector.mDetectNoThreshold  = aParms->mDetectNoThreshold;
   mPulseDetector.mSamplePeriod       = aParms->mTs;
   mPulseDetector.initialize();

   // Initialize pulse list.
   mPulseList.reset();
   mPulseList.mWindowTimeSize = aParms->mListWindowTimeSize;
   mPulseList.initialize();

   // Initialize pulse statistics.
   mPulseStatistics.initialize();

   // Input and output files.
   PdwCsvFileReader   tPdwReader;
   Ris::CsvFileWriter tSampleWriter;

   tPdwReader.open(aParms->mInputFileName);
   tSampleWriter.open(aParms->mOutputFileName);

   // Local
   int    tSampleCount = 0;
   double tSampleTime = 0.0;
   Sample tSample;
   int    tDetectedPdwCount = 0;
   Pdw*   tDetectedPdw = 0;
   Pdw*   tRemovedPdw = 0;

   // Read the first pdw.
   tDetectedPdw = tPdwReader.readPdw();
   tDetectedPdwCount = 1;

   // Loop through all of the samples in the duration.
   for (int k = 0; k < aParms->mNumSamples; k++)
   {
      // Set the sample.
      tSampleTime = k*aParms->mTs;
      tSample.put(tSampleTime,0.0);

      // If the next detected pdw is in this sample period
      if (tDetectedPdw)
      {
         if (k == tDetectedPdw->mIndex)
         {
            // Process the detected pdw.
            tSample.put(tSampleTime, 1.0);
            // Free the detected pdw.
            freePdw(tDetectedPdw);
            // Read the next pdw.
            tDetectedPdw = tPdwReader.readPdw();
            tDetectedPdwCount++;
         }
      }

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tSampleCount,
         tSample.mTime,
         tSample.mAmplitude);
      tSampleCount++;
   }

   Prn::print(0, "Analyze1 %d %d",tSampleCount,tDetectedPdwCount);
   // Close files.
   tPdwReader.close();
   tSampleWriter.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void FrontEnd::analyze12(FrontEndParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();

   // Initialize pulse detector.
   mPulseDetector.reset();
   mPulseDetector.mDetectYesThreshold = aParms->mDetectYesThreshold;
   mPulseDetector.mDetectNoThreshold  = aParms->mDetectNoThreshold;
   mPulseDetector.mSamplePeriod       = aParms->mTs;
   mPulseDetector.initialize();

   // Initialize pulse list.
   mPulseList.reset();
   mPulseList.mWindowTimeSize = aParms->mListWindowTimeSize;
   mPulseList.initialize();

   // Initialize pulse statistics.
   mPulseStatistics.initialize();

   // Input and output files.
   PdwCsvFileReader   tPdwReader;
   Ris::CsvFileWriter tSampleWriter;

   tPdwReader.open(aParms->mInputFileName);
   tSampleWriter.open(aParms->mOutputFileName);

   // Local
   int    tSampleCount = 0;
   double tSampleTime = 0.0;
   Sample tSample;
   int    tDetectedPdwCount = 0;
   Pdw*   tDetectedPdw = 0;
   Pdw*   tRemovedPdw = 0;

   // Read the first pdw.
   tDetectedPdw = tPdwReader.readPdw();
   tDetectedPdwCount = 1;

   // Loop through all of the samples in the duration.
   for (int k = 0; k < aParms->mNumSamples; k++)
   {
      // Set the sample.
      tSampleTime = k*aParms->mTs;
      tSample.put(tSampleTime,0.0);

      // If the next detected pdw is in this sample period
      if (tDetectedPdw)
      {
         if (k == tDetectedPdw->mIndex)
         {
            // Set the sample to mark it.
            tSample.put(tSampleTime, 1.0);

            // Add the detected pdw to the pdw statistics.
            mPulseStatistics.addPdw(tDetectedPdw);

            // Add the detected pdw to the pdw list.
            tRemovedPdw = mPulseList.addNewPdw(tDetectedPdw);

            // If a pdw was removed from the pdw list
            if (tRemovedPdw)
            {
               // Subtract the removed pdw from the pdw statistics.
               mPulseStatistics.subtractPdw(tRemovedPdw);

               // Free the removed pdw.
               freePdw(tRemovedPdw);
            }

            // Read the next pdw.
            tDetectedPdw = tPdwReader.readPdw();

            // Update the count.
            tDetectedPdwCount++;
         }
      }

      // Update the pulse list time. This removes the oldest pdw from the
      // list, if it has fallen ouside of the list sliding window.
      tRemovedPdw = mPulseList.updateTime(tSample.mTime);

      // If a pdw was removed from the pdw list
      if (tRemovedPdw)
      {
         // Subtract the removed pdw from the pdw statistics.
         mPulseStatistics.subtractPdw(tRemovedPdw);

         // Free the removed pdw.
         freePdw(tRemovedPdw);
      }

      // Write statistics to the output file.
      tSampleWriter.writeRow(
         tSampleCount,
         tSample.mTime,
         tSample.mAmplitude,
         mPulseStatistics.mCount,
         mPulseStatistics.mAmplitude.mMean,
         mPulseStatistics.mPulseWidth.mMean);

      // Update counter.
      tSampleCount++;
   }

   Prn::print(0, "Analyze1 %d %d",tSampleCount,tDetectedPdwCount);

   // Close files.
   tPdwReader.close();
   tSampleWriter.close();

   Prn::print(0, "mPulseList.mPutCount    %10d",mPulseList.mPutCount);
   Prn::print(0, "mPulseList.mGetCount    %10d",mPulseList.mGetCount);
   Prn::print(0, "mPulseList.mTestCount1  %10d",mPulseList.mTestCount1);
   Prn::print(0, "mPulseList.mTestCount2  %10d",mPulseList.mTestCount2);

   Prn::print(0, "mPulseList.mWindowTimeSize        %10.5f",mPulseList.mWindowTimeSize);
   Prn::print(0, "mPulseList.mWindowTimeUpperLimit  %10.5f",mPulseList.mWindowTimeUpperLimit),
   Prn::print(0, "mPulseList.mWindowTimeLowerLimit  %10.5f",mPulseList.mWindowTimeLowerLimit);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void FrontEnd::analyze2(FrontEndParms* aParms)
{
   // Initialize parameters.
   aParms->initialize();

   // Initialize pulse detector.
   mPulseDetector.reset();
   mPulseDetector.mDetectYesThreshold = aParms->mDetectYesThreshold;
   mPulseDetector.mDetectNoThreshold  = aParms->mDetectNoThreshold;
   mPulseDetector.mSamplePeriod       = aParms->mTs;
   mPulseDetector.initialize();

   // Initialize pulse list.
   mPulseList.reset();
   mPulseList.mWindowTimeSize = aParms->mListWindowTimeSize;
   mPulseList.initialize();

   // Initialize pulse statistics.
   mPulseStatistics.initialize();

   // Input and output files.
   Ris::CsvFileReader tSampleReader;
   Ris::CsvFileWriter tSampleWriter;

   tSampleReader.open(aParms->mInputFileName);
   tSampleWriter.open(aParms->mOutputFileName);

   // Local
   int    tSampleCount = 0;
   Sample tSample;
   int    tDetectedPdwCount = 0;
   Pdw*   tDetectedPdw = 0;
   Pdw*   tRemovedPdw = 0;

   // Loop through all of the samples in the input file.
   while (true)
   {
      // Read sample row from input file
      if(!tSampleReader.readRow()) break;
      tSampleCount++;

      // Convert input and store in sample temp.
      tSample.put(tSampleReader(0),tSampleReader(1));

      // Put the sample to the pulse detector.
      // It returns a pdw if it detects a pulse.
      tDetectedPdw = mPulseDetector.putSample(&tSample);

      // If a pulse was detected
      if (tDetectedPdw)
      {
         // Update the count.
         tDetectedPdwCount++;

         // Add the detected pdw to the pdw statistics.
         mPulseStatistics.addPdw(tDetectedPdw);

         // Add the detected pdw to the pdw list.
         tRemovedPdw = mPulseList.addNewPdw(tDetectedPdw);

         // Free the detected pdw.
         freePdw(tDetectedPdw);

         // If a pdw was removed from the pdw list
         if (tRemovedPdw)
         {
            // Subtract the removed pdw from the pdw statistics.
            mPulseStatistics.addPdw(tDetectedPdw);

            // Free the removed pdw.
            freePdw(tRemovedPdw);
         }
      }

      // Update the pulse list time. This removes the oldest pdw from the
      // list, if it has fallen ouside of the list sliding window.
      tRemovedPdw = mPulseList.updateTime(tSample.mTime);

      // If a pdw was removed from the pdw list
      if (tRemovedPdw)
      {
         // Subtract the removed pdw from the pdw statistics.
         mPulseStatistics.addPdw(tDetectedPdw);

         // Free the removed pdw.
         freePdw(tRemovedPdw);
      }

      // Write statistics to the output file.
      tSampleWriter.writeRow(
         tSampleCount,
         tSample.mTime,
         mPulseStatistics.mCount,
         mPulseStatistics.mAmplitude.mMean,
         mPulseStatistics.mPulseWidth.mMean);
   }

   Prn::print(0, "Analyze2 %d %d",tSampleCount,tDetectedPdwCount);
   // Close files.
   tSampleReader.close();
   tSampleWriter.close();
}

   
}//namespace
