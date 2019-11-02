//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _SOMEVIDEOPARMS_CPP_
#include "someThreadParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

ThreadParms::ThreadParms()
{
   reset();
}

void ThreadParms::reset()
{
   BaseClass::reset();
   BaseClass::setFileName_RelAlphaFiles("RisLib/Thread_Parms.txt");

   mTimerThreadPeriod = 0;
   mFilename[0] = 0;

   mDelayA1 = 0;
   mDelayA2 = 0;
   mDelayB1 = 0;
   mDelayB2 = 0;
   mShowCode = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void ThreadParms::show()
{
   printf("\n");
   printf("ThreadParms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("TimerThreadPeriod     %-10d\n",     mTimerThreadPeriod);
   printf("Filename              %-10s\n",     mFilename);

   printf("\n");
   printf("DelayA                %-10d %-4d\n", mDelayA1, mDelayA2);
   printf("DelayB                %-10d %-4d\n", mDelayB1, mDelayB2);
   printf("\n");
   printf("ShowCode              %-10d\n",      mShowCode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void ThreadParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TimerThreadPeriod"))   mTimerThreadPeriod = aCmd->argInt(1);

   if (aCmd->isCmd("DelayA"))
   {
      mDelayA1 = aCmd->argInt(1);
      mDelayA2 = aCmd->argInt(2);
   }

   if (aCmd->isCmd("DelayB"))
   {
      mDelayB1 = aCmd->argInt(1);
      mDelayB2 = aCmd->argInt(2);
   }

   if (aCmd->isCmd("ShowCode"))   mShowCode = aCmd->argInt(1);

   if (aCmd->isCmd("Filename"))   aCmd->copyArgString(1, mFilename,cMaxStringSize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void ThreadParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace