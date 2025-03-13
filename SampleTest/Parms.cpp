//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"
#include "risPortableCalls.h"
#include "dspPaths.h"

#define  _PARMS_CPP_
#include "Parms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

Parms::Parms()
{
}

void Parms::reset()
{
   BaseClass::reset();
   BaseClass::setFilePath(Dsp::get_files_filepath("SampleTest_Parms.txt"));

   mCode1 = 0;
   mCode2 = 0;

   mHistoryGenParms.reset();
   mHistoryFilterParms1.reset();
   mHistoryFilterParms2.reset();

   mInputFile[0]=0;
   mOutputFile[0]=0;
   mOutputFile2[0]=0;
   mOutputFile3[0]=0;

   mHistoryMaxSamples=0;
   mHistoryDeltaT=0.0;

   mAlpha1 = 0.0;
   mAlpha2 = 0.0;
   mLambda1 = 0.0;
   mLambda2 = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void Parms::show()
{
   printf("Parms ************************ BEGIN %s\n", BaseClass::mTargetSection);

   printf("Code1              %10d\n",mCode1);
   printf("Code2              %10d\n",mCode2);

   printf("InputFile          %10s\n",  mInputFile);
   printf("OutputFile         %10s\n",  mOutputFile);
   if (mOutputFile2[0] != 0)
   {
      printf("OutputFile2        %10s\n", mOutputFile2);
   }
   if (mOutputFile3[0] != 0)
   {
   printf("OutputFile3        %10s\n", mOutputFile3);
   }
   printf("HistoryMaxSamples  %10d\n",  mHistoryMaxSamples);
   printf("HistoryDeltaT      %10.4f\n",mHistoryDeltaT);
   printf("\n");

   printf("\n");
   printf("Alpha1             %10.4f\n",mAlpha1);
   printf("Alpha2             %10.4f\n",mAlpha2);
   printf("Lambda1            %10.4f\n",mLambda1);
   printf("Lambda2            %10.4f\n",mLambda2);


   mHistoryGenParms.show("Gen");
   printf("\n");
   mHistoryFilterParms1.show("Filter1");
   printf("\n");
   mHistoryFilterParms2.show("Filter2");
   printf("\n");

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

   if(aCmd->isCmd("InputFile"   )) aCmd->copyArgString(1,mInputFile,cMaxStringSize);
   if(aCmd->isCmd("OutputFile"  )) aCmd->copyArgString(1,mOutputFile,cMaxStringSize);
   if(aCmd->isCmd("OutputFile2" )) aCmd->copyArgString(1,mOutputFile2,cMaxStringSize);
   if(aCmd->isCmd("OutputFile3" )) aCmd->copyArgString(1,mOutputFile3,cMaxStringSize);

   if(aCmd->isCmd("HistoryGenParms"))      nestedPush(aCmd, &mHistoryGenParms);
   if(aCmd->isCmd("HistoryFilterParms1"))  nestedPush(aCmd, &mHistoryFilterParms1);
   if(aCmd->isCmd("HistoryFilterParms2"))  nestedPush(aCmd, &mHistoryFilterParms2);

   if(aCmd->isCmd("HistoryMaxSamples" )) mHistoryMaxSamples  = aCmd->argInt(1);
   if(aCmd->isCmd("HistoryDeltaT"     )) mHistoryDeltaT      = aCmd->argDouble(1);

   if(aCmd->isCmd("Alpha1"     )) mAlpha1 = aCmd->argDouble(1);
   if(aCmd->isCmd("Alpha2"     )) mAlpha2 = aCmd->argDouble(1);
   if(aCmd->isCmd("Lambda1"    )) mLambda1 = aCmd->argDouble(1);
   if(aCmd->isCmd("Lambda2"    )) mLambda2 = aCmd->argDouble(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void Parms::expand()
{
   mHistoryGenParms.expand();
   mHistoryFilterParms1.expand();
   mHistoryFilterParms2.expand();
   mHistoryFilterParms1.mAlphaDT = mHistoryDeltaT;
   mHistoryFilterParms2.mAlphaDT = mHistoryDeltaT;
}

