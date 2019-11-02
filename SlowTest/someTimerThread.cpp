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

   // Update the thresholder.
   bool tPass = false;
   bool tChangeFlag = false;
   mThresholder.doUpdate(mValue,tPass,tChangeFlag);
   mThresholder.show();

   // Update the input value.
   mValue += mDelta;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace