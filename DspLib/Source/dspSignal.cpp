/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dspTextFile.h"
#include "dspSignal.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

Signal::Signal()
{
   mX=0;
   mFs = 8000.0;
   mTs = 1.0 / mFs;
   mFp = 1.0;
   mFm = 1.0;
   mTp = 1.0 / mFp;
   mTm = 1.0 / mFm;

   mDCp = 1.0;
   mDCm = 1.0;
            
   mDuration = 10.0;
   mNumSamples = (int)(mDuration * mFs);

   mKev1 = 0;
   mKev2 = 0;
}

Signal::~Signal()
{
   if (mX)
   {
      delete mX;
      mX = 0;
   }
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void Signal::initialize()
{
   mTs = 1.0 / mFs;

   mNp = (int)round(mFs / mFp);
   mNp1 = (int)round(mDCp * mNp);
   mNp2 = (int)round((1.0 - mDCp) * mNp);
   mFp = mFs / (double)mNp;
   mTp = 1.0 / mFp;

   mNm = (int)round(mFp / mFm)*mNp;
   mNm1 = (int)round(mDCm * mNm);
   mNm2 = (int)round((1.0 - mDCm) * mNm);
   mFm = mFp * (double)mNp/(double)mNm;
   mTm = 1.0 / mFm;

   double nsamples = (int)(round(mDuration) * mFs);
   mNs = (int)round(nsamples / mNp) * mNp;
   mDuration = mNs * mTs;
   mNumSamples = mNs;
   mX = new double[mNumSamples];
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Normalize

void Signal::normalize()
{
   // Get min and max
   double xMin = 0.0;
   double xMax = 0.0;

   for (int k = 0; k < mNs; k++)
   {
      double x = mX[k];
      if (x < xMin) xMin = x;
      if (x > xMax) xMax = x;
   }

   // Get scale and offset
   if (xMin != xMax)
   {
      double scale = 1.0 / ((xMax - xMin) / 2.0);
      double offset = (xMax + xMin) / 2.0;

      // Adjust signal to be -1 <= x[k] <= 1
      for (int k = 0; k < mNs; k++)
      {
         double x = mX[k];
         double xa = scale * (x - offset);
         mX[k] = xa;
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void Signal::show()
{
   printf("mFs          %10.4f\n",mFs);
   printf("mTs          %10.4f\n",mTs);
   printf("mFp          %10.4f\n",mFp);
   printf("mTp          %10.4f\n",mTp);
   printf("mFm          %10.4f\n",mFm);
   printf("mTm          %10.4f\n",mTm);
   printf("mDuration    %10.4f\n",mDuration);

   printf("mNumSamples  %10d\n",  mNumSamples);
   printf("mNs          %10d\n",  mNs);
   printf("mNp          %10d\n",  mNp);
   printf("mNp1         %10d\n",  mNp1);
   printf("mNp2         %10d\n",  mNp2);
   printf("mNm          %10d\n",  mNm);
   printf("mNm1         %10d\n",  mNm1);
   printf("mNm2         %10d\n",  mNm2);

   printf("mDCp         %10.4f\n",mDCp);
   printf("mDCm         %10.4f\n",mDCm);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write

void Signal::writeToTextFile(char* aFileName)
{
   // Open output file.
   CsvFileWriter tWriter;
   tWriter.open(aFileName);

   // Loop through all of the samples in the signal.
   for (int i = 0; i < mNumSamples; i++)
   {
      // Write the signal time and sample to the file.
      tWriter.writeRow(i,(double)i*mTs, mX[i]);
   }

   // Done
   tWriter.close();
   printf( "Wrote Samples %s %d\n",aFileName,mNumSamples);
}

}//namespace