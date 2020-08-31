/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "someSlowTestParmsFile.h"
#include "someSlowTestParms.h"

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
   BaseClass::setThreadPrintLevel(0);

   // Set base class variables.
   BaseClass::setThreadPriority(Ris::Threads::gPriorities.mTimerTest);

   // Set timer period.
   BaseClass::mTimerPeriod = Some::gSlowTestParmsFile.mTimerPeriod;

   // Initialize variables.
   mSuspendFlag = false;
   mValue = Some::gSlowTestParmsFile.mInitialValue;
   mDelta = 0.0;
   mNoiseRequestFlag = false;
   mNoiseSigma = 0.0;
   mNoise = 0.0;

   mThresholder.initialize(&Some::gSlowTestParms.mTestThresholderParms);
   mClassifier.initialize();
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

   // Test something.
   if (gSlowTestParmsFile.mTestMode == 1)
   {
      // Update the thresholder.
      bool tPass = false;
      bool tChangeFlag = false;
      mThresholder.doUpdate(mValue + mNoise, tPass, tChangeFlag);
      char tBuffer[200];
      Prn::print(Prn::View11, "%s", mThresholder.asShowString(tBuffer));
   }
   else
   {
      // Update the classifier.
      int  tClass = -99;
      bool tChangeFlag = false;
      mClassifier.doClassify(mValue + mNoise, tClass, tChangeFlag);
      char tBuffer[200];
      Prn::print(Prn::View11, "%s", mClassifier.asShowString(tBuffer));
   }
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
   mNoise = (float)mGaussNoise.getNoise();

   // Update the input value.
   mValue += mDelta;
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

}//namespace