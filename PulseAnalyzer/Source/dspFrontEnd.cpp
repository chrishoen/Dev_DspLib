/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "my_functions.h"
#include "prnPrint.h"

#include "dspPdwFreeList.h"

#define  _DSPFRONTEND_CPP_
#include "dspFrontEnd.h"

namespace Dsp
{

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

void FrontEnd::detect1()
{
   // Initialize.
   mPulseDetector.initialize();

   // Read from input samples file.
   mFileReader.read("C:\\MyLib\\Data\\Sample41.csv");

   // Open output pdw file.
   mFileWriter.open("C:\\MyLib\\Data\\Pdw41.csv");

   // Local
   int tSampleCount = mFileReader.mRows;
   int tPdwCount = 0;
   Sample tSample;

   // Loop through all of the samples in the input file.
   for (int i = 0; i < tSampleCount; i++)
   {
      // Convert and store input in sample temp.
      tSample.put(mFileReader(i,0),mFileReader(i,1));

      // Put the sample to the pulse detector.
      // It returns a pdw if it detects a pulse.
      Pdw* tPdw = mPulseDetector.putSample(&tSample);

      // If a pulse was detected
      if (tPdw)
      {
         // Update
         tPdwCount++;
         // Write the detected pdw to the output file
         mFileWriter.write(
            tPdw->mToa,
            tPdw->mAmplitude,
            tPdw->mPulseWidth);
         // Free the pdw.
         freePdw(tPdw);
      }
   }

   Prn::print(0, "Detect1 %d %d",tSampleCount,tPdwCount);
   // Close output pdw file.
   mFileWriter.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void FrontEnd::analyze1()
{
   // Initialize.
   mPulseDetector.initialize();
   mPulseList.initialize(1000);
   mPulseStatistics.initialize();

   // Read all of the samples from the input file.
   mFileReader.read("C:\\MyLib\\Data\\Sample41.csv");

   // Open the output file.
   mFileWriter.open("C:\\MyLib\\Data\\Analyze41.csv");

   // Local
   int    tSampleCount = mFileReader.mRows;
   Sample tSample;
   int    tDetectedPdwCount = 0;
   Pdw*   tDetectedPdw = 0;
   Pdw*   tRemovedPdw = 0;

   // Loop through all of the samples in the input file.
   for (int i = 0; i < tSampleCount; i++)
   {
      // Store inputs in sample variable.
      tSample.put(mFileReader(i,0),mFileReader(i,1));

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
      mFileWriter.write(
         tSample.mTime,
         mPulseStatistics.mCount,
         mPulseStatistics.mAmplitude.mMean,
         mPulseStatistics.mPulseWidth.mMean);
   }

   Prn::print(0, "Analyze1 %d %d",tSampleCount,tDetectedPdwCount);
   // Close output file.
   mFileWriter.close();
}

   
}//namespace
