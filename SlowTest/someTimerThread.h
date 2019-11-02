#pragma once

/*==============================================================================
Timer test thread.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "risThreadsTimerThread.h"
#include "dspSlowThresholder.h"

namespace Some
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class TimerThread : public Ris::Threads::BaseTimerThread
{
public:
   typedef Ris::Threads::BaseTimerThread BaseClass;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Members.

   // Suspend.
   bool mSuspendFlag;

   // Input value.
   double mValue;
   double mDelta;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Members.

   Dsp::SlowThresholder mThresholder;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Methods.

   // Constructor.
   TimerThread();

   // Base class overloads.
   void threadInitFunction() override;
   void executeOnTimer(int aTimeCount) override;

   void executeTest1 (int aTimeCount);
   void executeTest2 (int aTimeCount);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _SOMETIMERTHREAD_CPP_
          TimerThread* gTimerThread;
#else
   extern TimerThread* gTimerThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


