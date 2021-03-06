/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "prnPrint.h"
#include "logFiles.h"

#include "dsp_math.h"
#include "dspTrialStatistics.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::log(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f  %12.6f",
      aLabel,
      mCount,
      mEX,
      mUX,
      mMinX,
      mMaxX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDeg(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f  %12.6f",
      aLabel,
      mCount,
      deg(mEX),
      deg(mUX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logEUMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mUX,
      mMinX,
      mMaxX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDegEUMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mUX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logCEUMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      mEX,
      mUX,
      mMinX,
      mMaxX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDegCEUMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      deg(mEX),
      deg(mUX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logERMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mRms,
      mMinX,
      mMaxX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDegERMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mRms),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logCERMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      mEX,
      mRms,
      mMinX,
      mMaxX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDegCERMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      deg(mEX),
      deg(mRms),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logEUX(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mUX,
      mExtX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDegEUX(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mUX),
      deg(mExtX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logCEUX(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      mEX,
      mUX,
      mExtX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDegCEUX(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      deg(mEX),
      deg(mUX),
      deg(mExtX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f",
      aLabel,
      mMinX,
      mMaxX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDegMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f",
      aLabel,
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logEMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mMinX,
      mMaxX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDegEMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logCEMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      mEX,
      mMinX,
      mMaxX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDegCEMM(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      deg(mEX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logEUS(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mUX,
      mSX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDegEUS(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mUX),
      deg(mSX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logCEUS(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      mEX,
      mUX,
      mSX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logDegCEUS(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      deg(mEX),
      deg(mUX),
      deg(mSX));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::logTimeExt(int aLN,char* aLabel)
{
   Log::write(aLN,"%-10s %6llu $$ %12.6f",
      aLabel,
      mCount,
      mTimeExtX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

