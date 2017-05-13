/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <string.h>

#include "prnPrint.h"
#include "logFiles.h"

#include "dsp_math.h"
#include "dspStatistics.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::showCount(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s $$ %12llu %12llu",
      aLabel,
      mCount,
      mDropCount);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TrialStatistics::show(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s %6llu $$ %12.6f %12.6f %12.6f  %12.6f",
      aLabel,
      mCount,
      mEX,
      mUX,
      mMinX,
      mMaxX);
}

//******************************************************************************

void TrialStatistics::showDeg(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s %6llu $$ %12.6f %12.6f %12.6f  %12.6f",
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

void TrialStatistics::showEUMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mUX,
      mMinX,
      mMaxX);
}

//******************************************************************************

void TrialStatistics::showDegEUMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mUX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************

void TrialStatistics::showCEUMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s %6llu $$ %12.6f %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      mEX,
      mUX,
      mMinX,
      mMaxX);
}

//******************************************************************************

void TrialStatistics::showDegCEUMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s %6llu $$ %12.6f %12.6f %12.6f %12.6f",
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

void TrialStatistics::showEUX(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mUX,
      mExtX);
}

//******************************************************************************

void TrialStatistics::showDegEUX(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mUX),
      deg(mExtX));
}

//******************************************************************************

void TrialStatistics::showCEUX(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      mEX,
      mUX,
      mExtX);
}

//******************************************************************************

void TrialStatistics::showDegCEUX(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
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

void TrialStatistics::showEMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mMinX,
      mMaxX);
}

//******************************************************************************

void TrialStatistics::showDegEMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mMinX),
      deg(mMaxX));
}

//******************************************************************************

void TrialStatistics::showCEMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      mEX,
      mMinX,
      mMaxX);
}

//******************************************************************************

void TrialStatistics::showDegCEMM(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
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

void TrialStatistics::showEUS(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      mEX,
      mUX,
      mSX);
}

//******************************************************************************

void TrialStatistics::showDegEUS(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s $$ %12.6f %12.6f %12.6f",
      aLabel,
      deg(mEX),
      deg(mUX),
      deg(mSX));
}

//******************************************************************************

void TrialStatistics::showCEUS(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
      aLabel,
      mCount,
      mEX,
      mUX,
      mSX);
}

//******************************************************************************

void TrialStatistics::showDegCEUS(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s %6llu $$ %12.6f %12.6f %12.6f",
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

void TrialStatistics::showTimeExt(int aPF,char* aLabel)
{
   Prn::print(aPF,"%-10s %6llu $$ %12.6f",
      aLabel,
      mCount,
      mTimeExtX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

