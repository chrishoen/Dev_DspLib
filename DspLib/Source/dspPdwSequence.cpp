/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspTextFile.h"
#include "dspPdwTextFile.h"
#include "dspPdwSequence.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

PdwSequence::PdwSequence()
{
   reset();
}

void PdwSequence::reset()
{
   mFs = 8000.0;
   mTs = 1.0 / mFs;
   mFm = 1.0;
   mTm = 1.0 / mFm;

   mDCm = 1.0;
            
   mDuration = 10.0;
   mNumSamples = (int)(mDuration * mFs);

   mPdwArray=0;
   mPdwCount=0;
}

PdwSequence::~PdwSequence()
{
   if (mPdwArray)
   {
      delete mPdwArray;
      mPdwArray = 0;
   }
}

void PdwSequence::setPdwFileName  (char* aFileName) { strcpy(mPdwFileName,  aFileName); }
void PdwSequence::setPlotFileName (char* aFileName) { strcpy(mPlotFileName, aFileName); }
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize

void PdwSequence::initialize()
{
   mTs = 1.0 / mFs;

   mNm = (int)round(mFs / mFm);
   mNm1 = (int)round(mDCm * mNm);
   mNm2 = (int)round((1.0 - mDCm) * mNm);
   mFm = mFs / (double)mNm;
   mTm = 1.0 / mFm;

   double nsamples = (int)(round(mDuration) * mFs);
   mNs = (int)round(nsamples / mNm) * mNm;
   mDuration = mNs * mTs;
   mNumSamples = mNs;

   mPdwArray = new Pdw[cMaxNumOfPdws];
   mPdwCount = 0;
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put Pdw to the PdwArray

void PdwSequence::putPdw(Pdw* aPdw)
{
   if (mPdwCount >= cMaxNumOfPdws) return;
   mPdwArray[mPdwCount++] = *aPdw;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void PdwSequence::show()
{
   printf("mFs          %10.4f\n",mFs);
   printf("mTs          %10.4f\n",mTs);
   printf("mFm          %10.4f\n",mFm);
   printf("mTm          %10.4f\n",mTm);
   printf("mDuration    %10.4f\n",mDuration);

   printf("mNumSamples  %10d\n",  mNumSamples);
   printf("mNs          %10d\n",  mNs);
   printf("mNm          %10d\n",  mNm);
   printf("mNm1         %10d\n",  mNm1);
   printf("mNm2         %10d\n",  mNm2);

   printf("mDCm         %10.4f\n",mDCm);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write

void PdwSequence::writeToTextFile()
{
   // Open output files.
   PdwCsvFileWriter   tPdwWriter;
   CsvFileWriter      tPlotWriter;

   tPdwWriter.open  (mPdwFileName);
   tPlotWriter.open (mPlotFileName);

   // Write first row
   tPlotWriter.writeRow (0, 0.0, 0.0);
   // Loop through all of the pdws in the sequence.
   for (int i = 0; i < mPdwCount; i++)
   {
      // Write the pdw values to the output files.
      Pdw* tPdw = &mPdwArray[i];
      tPdwWriter.writePdw(tPdw);

      tPlotWriter.writeRow (tPdw->mIndex-1, tPdw->mToa - mTs, 0.0);
      tPlotWriter.writeRow (tPdw->mIndex,   tPdw->mToa,       tPdw->mAmplitude);
      tPlotWriter.writeRow (tPdw->mIndex+1, tPdw->mToa + mTs, 0.0);
   }

   // Done
   tPdwWriter.close();
   printf("Wrote Pdws    %s %d\n",mPdwFileName,mPdwCount);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace