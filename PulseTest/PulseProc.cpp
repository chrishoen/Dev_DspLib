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

   // Set some writer variables.
   gPlotWriter.mDetectFlag1 = mBoundCount.mDetectFlag;
   gPulseWriter.mCount = mBoundCount.mCount;
   gPulseWriter.mDetectFlag = mBoundCount.mDetectFlag;
   gPulseWriter.mDetectRise = mBoundCount.mDetectRise;
   gPulseWriter.mDetectFall = mBoundCount.mDetectFall;
}

void PulseProc::processPulse2(bool aPulseFlag)
{
}

void PulseProc::processPulse3(bool aPulseFlag)
{
}

