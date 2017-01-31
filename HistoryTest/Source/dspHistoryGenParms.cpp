//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "my_functions.h"
#include "risCmdLineFile.h"
#include "risPortableCalls.h"

#include "dsp_math.h"
#include "dspHistoryGenParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

HistoryGenParms::HistoryGenParms()
{
   reset();
}

void HistoryGenParms::reset()
{
   BaseClass::reset();

   mGenType  = cGenZero;
   mTimeType = cTimeType1;

   mDuration = 10.0;
   mFs = 1.0;
   mFc = 1.0;
   mEX = 0.0;
   mUX = 1.0;
   mFilterOrder = 4;
   mA   = 0.0;
   mPhi = 0.0;
   mTp  = 1.0;
   mSigma = 0.0;

   mTs = 1.0 / mFs;
   mMaxSamples = (int)(mDuration * mFs);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void HistoryGenParms::show(char* aLabel)
{
   printf("HistoryGenParms ******** BEGIN %s\n", aLabel);

   printf("GenType            %10s\n",  asStringGenType(mGenType));
   printf("TimeType           %10s\n",  asStringTimeType(mTimeType));
   printf("Duration           %10.4f\n", mDuration);
   printf("Fs                 %10.4f\n", mFs);
   printf("Fc                 %10.4f\n", mFc);
   printf("FilterOrder        %10d\n", mFilterOrder);
   printf("EX                 %10.4f\n", mEX);
   printf("UX                 %10.4f\n", mUX);
   printf("A                  %10.4f\n", mA);
   printf("Phi                %10.4f\n", deg(mPhi));
   printf("Tp                 %10.4f\n", mTp);
   printf("Sigma              %10.4f\n", mSigma);

   printf("HistoryGenParms ******** END %s\n", aLabel);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void HistoryGenParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("Duration"))    mDuration    = aCmd->argDouble(1);
   if (aCmd->isCmd("Fs"))          mFs          = aCmd->argDouble(1);
   if (aCmd->isCmd("Fc"))          mFc          = aCmd->argDouble(1);
   if (aCmd->isCmd("FilterOrder")) mFilterOrder = aCmd->argInt(1);
   if (aCmd->isCmd("EX"))          mEX          = aCmd->argDouble(1);
   if (aCmd->isCmd("UX"))          mUX          = aCmd->argDouble(1);
   if (aCmd->isCmd("A"))           mA           = aCmd->argDouble(1);
   if (aCmd->isCmd("Phi"))         mPhi         = aCmd->argAngle(1);
   if (aCmd->isCmd("Sigma"))       mSigma       = aCmd->argDouble(1);

   if (aCmd->isCmd("GenType"))
   {
      if (aCmd->isArgString(1,asStringGenType(cGenZero)))     mGenType = cGenZero;
      if (aCmd->isArgString(1,asStringGenType(cGenStep)))     mGenType = cGenStep;
      if (aCmd->isArgString(1,asStringGenType(cGenSinWave)))  mGenType = cGenSinWave;
      if (aCmd->isArgString(1,asStringGenType(cGenRandWave))) mGenType = cGenRandWave;
   }

   if (aCmd->isCmd("TimeType"))
   {
      if (aCmd->isArgString(1,asStringTimeType(cTimeType1)))     mTimeType = cTimeType1;
      if (aCmd->isArgString(1,asStringTimeType(cTimeType2)))     mTimeType = cTimeType2;
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void HistoryGenParms::expand()
{
   mTs = 1.0 / mFs;
   mMaxSamples = (int)(round(mDuration) * mFs);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

char* HistoryGenParms::asStringGenType(int aGenType)
{
   switch (aGenType)
   {
   case cGenZero     : return "Zero";
   case cGenStep     : return "Step";
   case cGenSinWave  : return "SinWave";
   case cGenRandWave : return "RandWave";
   default : return "UNKNOWN";
   }
}

char* HistoryGenParms::asStringTimeType(int aTimeType)
{
   switch (aTimeType)
   {
   case cTimeType1     : return "Type1";
   case cTimeType2     : return "Type2";
   default : return "UNKNOWN";
   }
}


}//namespace