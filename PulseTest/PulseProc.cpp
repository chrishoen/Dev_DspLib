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
   mDetectFlag1 = false;
   mDetectFlag2 = false;
   mDetectFlag3 = false;
}

void PulseProc::initialize()
{
   resetVars();

   // Initialize the components.
   mBoundCount.reset();
   mBoundCount.mMin = gPulseParms.mBoundCountMin;
   mBoundCount.mMax = gPulseParms.mBoundCountMax;

   mSlidingSum.reset();

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
   // Update the components.
   mBoundCount.update(aPulseFlag);
   mDetectFlag1 = mBoundCount.mDetectFlag;

   // Update the writers.
   gPlotWriter.resetVars();
   gPlotWriter.mPulseFlag = aPulseFlag;
   gPlotWriter.mDetectFlag1 = mDetectFlag1;
   gPlotWriter.mDetectFlag2 = mDetectFlag2;
   gPlotWriter.mDetectFlag3 = mDetectFlag3;
   gPlotWriter.doWrite();
   
   gPulseWriter.resetVars();
   gPulseWriter.mPulseFlag = aPulseFlag;
   gPulseWriter.mDetectFlag1 = mDetectFlag1;
   gPulseWriter.mDetectFlag2 = mDetectFlag2;
   gPulseWriter.mDetectFlag3 = mDetectFlag3;

   gPulseWriter.mCount1 = mBoundCount.mCount;
   gPulseWriter.doWrite();
}

