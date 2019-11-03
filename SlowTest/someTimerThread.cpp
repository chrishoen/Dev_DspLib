/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "dspSlowTestParms.h"

#define  _SOMETIMERTHREAD_CPP_
#include "someTimerThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

TimerThread::TimerThread()
{
   // Set base class variables.
   BaseClass::setThreadName("Timer");
   BaseClass::setThreadPrintLevel(TS::PrintLevel(0, 3));

   // Set base class variables.
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mTimerTest);

   // Set timer period.
   BaseClass::mTimerPeriod = 200;

   // Initialize variables.
   mSuspendFlag = false;
   mValue = 0.0;
   mDelta = 0.0;
   mNoiseRequestFlag = false;
   mNoiseSigma = 0.0;
   mNoise = 0.0;

   mThresholder.initialize(&Dsp::gSlowTestParms.mThresholderParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TimerThread::threadInitFunction()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TimerThread::executeOnTimer(int aTimeCount)
{
   // Guard.
   if (mSuspendFlag) return;

   // Update the simulated input value.
   doUpdateValue();

   // Update the thresholder.
   bool tPass = false;
   bool tChangeFlag = false;
   mThresholder.doUpdate(mValue + mNoise,tPass,tChangeFlag);
   mThresholder.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Update the simulated input value.

void TimerThread::doUpdateValue()
{
   // If there is a request for gaussian noise then initialize the gaussian
   // noise generator.
   if (mNoiseRequestFlag)
   {
      mNoiseRequestFlag = false;
      mGaussNoise.initialize(mNoiseSigma);
   }
      
   // Get from the noise generator.
   mNoise = mGaussNoise.getNoise();

   // Update the input value.
   mValue += mDelta;
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace