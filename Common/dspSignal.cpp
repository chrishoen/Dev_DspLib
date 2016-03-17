/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "prnPrint.h"
#include "risTextFile.h"
#include "dspSignal.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

Signal::Signal()
{
   mFs = 8000.0;
   mTs = 1.0 / mFs;
   mFp = 1.0;
   mFm = 1.0;
   mTp = 1.0 / mFp;
   mTm = 1.0 / mFm;

   mDCp = 1.0;
   mDCm = 1.0;
   mAlpha = 0.0;
            
   mDuration = 10.0;
   mNumSamples = (int)(mDuration * mFs);

   mM1=0.0;
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
   Prn::print(0,"mFs          %10.4f",mFs);
   Prn::print(0,"mTs          %10.4f",mTs);
   Prn::print(0,"mFp          %10.4f",mFp);
   Prn::print(0,"mTp          %10.4f",mTp);
   Prn::print(0,"mFm          %10.4f",mFm);
   Prn::print(0,"mTm          %10.4f",mTm);
   Prn::print(0,"mDuration    %10.4f",mDuration);

   Prn::print(0,"mNumSamples  %10d",  mNumSamples);
   Prn::print(0,"mNs          %10d",  mNs);
   Prn::print(0,"mNp          %10d",  mNp);
   Prn::print(0,"mNp1         %10d",  mNp1);
   Prn::print(0,"mNp2         %10d",  mNp2);
   Prn::print(0,"mNm          %10d",  mNm);
   Prn::print(0,"mNm1         %10d",  mNm1);
   Prn::print(0,"mNm2         %10d",  mNm2);

   Prn::print(0,"mDCp         %10.4f",mDCp);
   Prn::print(0,"mDCm         %10.4f",mDCm);
   Prn::print(0,"mM1          %10.4f",mM1);
   Prn::print(0,"mAlpha       %10.4f",mAlpha);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write

void Signal::writeToTextFile(char* aFileName)
{
   // Open output file.
   Ris::CsvFileWriter tWriter;
   tWriter.open(aFileName);

   // Loop through all of the samples in the signal.
   for (int i = 0; i < mNumSamples; i++)
   {
      // Write the signal time and sample to the file.
      tWriter.write((double)i*mTs, mX[i]);
   }

   // Done
   tWriter.close();
   Prn::print(0, "Wrote Samples %s %d",aFileName,mNumSamples);
}

}//namespace