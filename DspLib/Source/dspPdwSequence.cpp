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
   Prn::print(0,"mFs          %10.4f",mFs);
   Prn::print(0,"mTs          %10.4f",mTs);
   Prn::print(0,"mFm          %10.4f",mFm);
   Prn::print(0,"mTm          %10.4f",mTm);
   Prn::print(0,"mDuration    %10.4f",mDuration);

   Prn::print(0,"mNumSamples  %10d",  mNumSamples);
   Prn::print(0,"mNs          %10d",  mNs);
   Prn::print(0,"mNm          %10d",  mNm);
   Prn::print(0,"mNm1         %10d",  mNm1);
   Prn::print(0,"mNm2         %10d",  mNm2);

   Prn::print(0,"mDCm         %10.4f",mDCm);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write

void PdwSequence::writeToTextFile()
{
   // Open output files.
   PdwCsvFileWriter   tPdwWriter;
   Ris::CsvFileWriter tPlotWriter;

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
   Prn::print(0, "Wrote Pdws    %s %d",mPdwFileName,mPdwCount);
}

}//namespace