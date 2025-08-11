/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnPaths.h"
#include "PulseParms.h"
#include "PlotWriter.h"
#include "PulseWriter.h"


#define  _PULSEPROC_CPP_
#include "PulseProc.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

PulseProc::PulseProc()
{
   resetVars();
}

void PulseProc::resetVars()
{
   mPulseFlag = false;
   mPulseRise = false;
   mPulseFall = false;
   mLastPulseFlag = false;

   mDetectFlag = false;
   mDetectRise = false;
   mDetectFall = false;
   mLastDetectFlag = false;

   mCount = 0;
}

void PulseProc::initialize()
{
   resetVars();

   // Initialize the components.
   mBoundCount.reset();
   mBoundCount.mMin = gPulseParms.mBoundCountMin;
   mBoundCount.mMax = gPulseParms.mBoundCountMax;

   mSlidingSum.reset();
   mSlidingSum.mSumHigh = gPulseParms.mSlidingSumHigh;
   mSlidingSum.mSumLow = gPulseParms.mSlidingSumLow;

   mFuzzyAlpha.initialize(
      gPulseParms.mFilterDT, gPulseParms.mFuzzyStepTime, gPulseParms.mFuzzyCrisp);

   // Initialize the writers.
   gPlotWriter.initialize();
   gPulseWriter.initialize();
}

void PulseProc::finalize()
{
   gPlotWriter.finalize();
   gPulseWriter.finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Process a pulse.

void PulseProc::processPulse(bool aPulseFlag)
{
   // Pulse rising and falling edges.
   mPulseFlag = aPulseFlag;
   mPulseRise = !mLastPulseFlag && mPulseFlag;
   mPulseFall = mLastPulseFlag && !mPulseFlag;
   mLastPulseFlag = mPulseFlag;

   // Set some writer variables.
   gPlotWriter.resetVars();
   gPulseWriter.resetVars();
   gPlotWriter.mPulseFlag = mPulseFlag;
   gPulseWriter.mPulseFlag = mPulseFlag;
   gPulseWriter.mPulseRise = mPulseRise;
   gPulseWriter.mPulseFall = mPulseFall;

   // Select
   switch(gPulseParms.mMode)
   {
      case 1: processPulse1(aPulseFlag); break;
      case 2: processPulse2(aPulseFlag); break;
      case 3: processPulse3(aPulseFlag); break;
   }

   // Detection flags.
   mDetectRise = !mLastDetectFlag && mDetectFlag;
   mDetectFall = mLastDetectFlag && !mDetectFlag;
   mLastDetectFlag = mDetectFlag;

   // Set some writer variables.
   gPlotWriter.mDetectFlag1 = mDetectFlag;
   gPulseWriter.mDetectFlag = mDetectFlag;
   gPulseWriter.mDetectRise = mDetectRise;
   gPulseWriter.mDetectFall = mDetectFall;
   gPulseWriter.mCount = mCount;

   // Write the writers.
   gPlotWriter.doWrite();
   gPulseWriter.doWrite();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Process a pulse.

void PulseProc::processPulse1(bool aPulseFlag)
{
   // Update the components.
   mBoundCount.update(aPulseFlag);

   // Set some pulse variables.
   mDetectFlag = mBoundCount.mDetectFlag;
   mCount = mBoundCount.mCount;
}

void PulseProc::processPulse2(bool aPulseFlag)
{
   // Update the components.
   mSlidingSum.doPut(aPulseFlag);

   // Set some pulse variables.
   mCount = mSlidingSum.mSum;
   if (mSlidingSum.mHighFlag)  mDetectFlag = true;
   if (mSlidingSum.mLowFlag)   mDetectFlag = false;
}

void PulseProc::processPulse3(bool aPulseFlag)
{
}

