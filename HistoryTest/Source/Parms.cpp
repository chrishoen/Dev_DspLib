//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "my_functions.h"
#include "risCmdLineFile.h"
#include "risPortableCalls.h"

#define  _PARMS_CPP_
#include "Parms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

Parms::Parms()
{
   reset();
}

void Parms::reset()
{
   BaseClass::reset();
   strcpy(BaseClass::mFileName,"History_Parms.txt");

   mCode1 = 0;
   mCode2 = 0;

   mLockFlag=false;
   mDuration = 10.0;
   mFs = 1.0;
   mFc = 1.0;
   mEX = 0.0;
   mUX = 1.0;

   mFc1 = 1.0;
   mFc2 = 1.0;

   mFilterOrder = 4;

   mOutputFile[0]=0;

   mTs = 1.0 / mFs;
   mNumSamples = (int)(mDuration * mFs);

   mHistoryMaxSamples=0;
   mHistoryDeltaT=0.0;

   mHistoryGenWiener.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void Parms::expand()
{
   mTs = 1.0 / mFs;
   mNumSamples = (int)(round(mDuration) * mFs);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void Parms::show()
{
   printf("Parms ***************** BEGIN %s\n", BaseClass::mTargetSection);

   printf("Code1              %10d\n",mCode1);
   printf("Code2              %10d\n",mCode2);

   printf("LockFlag           %10s\n",  my_string_from_bool(mLockFlag));
   printf("Duration           %10.4f\n",mDuration);
   printf("Fs                 %10.4f\n",mFs);
   printf("Fc                 %10.4f\n",mFc);
   printf("EX                 %10.4f\n",mEX);
   printf("UX                 %10.4f\n",mUX);

   printf("Fc1                %10.4f\n",mFc1);
   printf("Fc2                %10.4f\n",mFc2);
   printf("FilterOrder        %10d\n",  mFilterOrder);

   printf("OutputFile         %10s\n",  mOutputFile);

   printf("HistoryMaxSamples  %10d\n",  mHistoryMaxSamples);
   printf("HistoryDeltaT      %10.4f\n",mHistoryDeltaT);

   mHistoryGenWiener.show("HistoryGenWiener");

   printf("Parms ******************* END %s\n", BaseClass::mTargetSection);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void Parms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if(aCmd->isCmd("Code1"))  mCode1 = aCmd->argInt (1);
   if(aCmd->isCmd("Code2"))  mCode2 = aCmd->argInt (1);

   if(aCmd->isCmd("Duration"          )) mDuration           = aCmd->argDouble(1);
   if(aCmd->isCmd("Fs"                )) mFs                 = aCmd->argDouble(1);
   if(aCmd->isCmd("Fc"                )) mFc                 = aCmd->argDouble(1);
   if(aCmd->isCmd("EX"                )) mEX                 = aCmd->argDouble(1);
   if(aCmd->isCmd("UX"                )) mUX                 = aCmd->argDouble(1);

   if(aCmd->isCmd("Fc1"               )) mFc1                = aCmd->argDouble(1);
   if(aCmd->isCmd("Fc2"               )) mFc2                = aCmd->argDouble(1);
   if(aCmd->isCmd("FilterOrder"       )) mFilterOrder        = aCmd->argInt(1);
   if(aCmd->isCmd("HistoryMaxSamples" )) mHistoryMaxSamples  = aCmd->argInt(1);
   if(aCmd->isCmd("HistoryDeltaT"     )) mHistoryDeltaT      = aCmd->argDouble(1);

   if(aCmd->isCmd("OutputFile"  )) aCmd->copyArgString(1,mOutputFile,cMaxStringSize);

   if(aCmd->isCmd("HistoryGenWiener")) nestedPush(aCmd, &mHistoryGenWiener);
}

