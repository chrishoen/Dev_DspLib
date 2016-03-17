/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "my_functions.h"
#include "prnPrint.h"

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
   mSampleReader.read("C:\\MyLib\\Data\\Sample41.csv");

   // Open output pdw file.
   mPdwWriter.open("C:\\MyLib\\Data\\Pdw41.csv");

   // Local
   int tSampleCount=mSampleReader.mRows;
   int tPdwCount=0;
   Sample tSample;

   // Loop through all of the samples in the input file.
   for (int i = 0; i < tSampleCount; i++)
   {
      // Convert and store input in sample temp.
      tSample.put(mSampleReader(i,0),mSampleReader(i,1));

      // Put the sample to the pulse detector.
      mPulseDetector.putSample(&tSample);

      // If a pulse was detected
      if (mPulseDetector.mDetectFlag)
      {
         // Update
         tPdwCount++;
         // Write the detected pdw to the output file
         mPdwWriter.write(
            mPulseDetector.mDetectPdw.mToa,
            mPulseDetector.mDetectPdw.mAmplitude,
            mPulseDetector.mDetectPdw.mPulseWidth);
      }
   }

   Prn::print(0, "Detect1 %d %d",tSampleCount,tPdwCount);
   // Close output pdw file.
   mPdwWriter.close();
}

   
}//namespace
