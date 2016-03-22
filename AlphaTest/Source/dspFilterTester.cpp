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
#include "dspFilterTester.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

FilterParms::FilterParms()
{
   reset();
}

void FilterParms::reset()
{
   mFs = 10000.0;
   mTs = 1.0 / mFs;
   mDuration = 10.0;
   mNumSamples = (int)(mDuration * mFs);

   mAp1 = 0.01;
   mAp2 = 1.0 - mAp1;

   mInputFileName[0]=0;
   mOutputFileName [0]=0;
}

void FilterParms::initialize()
{
   mTs = 1.0 / mFs;
   mNumSamples = (int)(round(mDuration) * mFs);
}

void FilterParms::setInputFileName  (char* aFileName) { strcpy(mInputFileName,  aFileName); }
void FilterParms::setOutputFileName (char* aFileName) { strcpy(mOutputFileName, aFileName); }
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

FilterTester::FilterTester()
{
   initialize();
}

void FilterTester::initialize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void FilterTester::filter11(FilterParms* aParms)
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

      // Put sample to filter
      mAlphaOne.put(tSample.mAmplitude);

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tSampleCount,
         tSample.mTime,
         tSample.mAmplitude,
         mAlphaOne.mXX);
      tSampleCount++;
   }

   Prn::print(0, "Filter1 %d",tSampleCount);
   // Close files.
   tSampleReader.close();
   tSampleWriter.close();
}

//******************************************************************************   
}//namespace
