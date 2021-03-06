//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

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
   BaseClass::setFileName_RelAlphaFiles("DspLib/Delay_Parms.txt");

   mCode1 = 0;
   mCode2 = 0;

   mHistoryGenParms.reset();
   mHistoryFilterParms1.reset();
   mHistoryFilterParms2.reset();

   mOutputFile[0]=0;

   mXAInitial = 0.0;
   mXBInitial = 0.0;
   mTolerance = 0.0;
   mMaxIterations = 0;

   mTestDelay = 0.0;
   mTestSigma = 0.0;

   mDelayEstimatorSearchDelay = 0.0;
   mDelayEstimatorTolerance = 0.0;
   mDelayEstimatorMaxIterations = 0;
   mDelayEstimatorFs = 0.0;

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

   printf("OutputFile         %10s\n",  mOutputFile);
   printf("XAInitial          %10.6f\n",mXAInitial);
   printf("XBInitial          %10.6f\n",mXBInitial);
   printf("Tolerance          %10.6f\n",mTolerance);
   printf("MaxIterations      %10d\n",  mMaxIterations);

   printf("\n");
   printf("TestDelay                     %10.6f\n",mTestDelay);
   printf("TestSigma                     %10.6f\n",mTestSigma);

   printf("DelayEstimatorSearchDelay     %10.6f\n",mDelayEstimatorSearchDelay);
   printf("DelayEstimatorTolerance       %10.6f\n",mDelayEstimatorTolerance);
   printf("DelayEstimatorMaxIterations   %10d\n",  mDelayEstimatorMaxIterations);
   printf("DelayEstimatorFs              %10.6f\n",mDelayEstimatorFs);

   printf("\n");

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

   if(aCmd->isCmd("OutputFile"  )) aCmd->copyArgString(1,mOutputFile,cMaxStringSize);

   if(aCmd->isCmd("HistoryGenParms"))      nestedPush(aCmd, &mHistoryGenParms);
   if(aCmd->isCmd("HistoryFilterParms1"))  nestedPush(aCmd, &mHistoryFilterParms1);
   if(aCmd->isCmd("HistoryFilterParms2"))  nestedPush(aCmd, &mHistoryFilterParms2);

   if(aCmd->isCmd("XAInitial" ))         mXAInitial     = aCmd->argDouble(1);
   if(aCmd->isCmd("XBInitial" ))         mXBInitial     = aCmd->argDouble(1);
   if(aCmd->isCmd("Tolerance" ))         mTolerance     = aCmd->argDouble(1);
   if(aCmd->isCmd("MaxIterations" ))     mMaxIterations = aCmd->argInt(1);


   if(aCmd->isCmd("TestDelay" ))                   mTestDelay                   = aCmd->argDouble(1);
   if(aCmd->isCmd("TestSigma" ))                   mTestSigma                   = aCmd->argDouble(1);

   if(aCmd->isCmd("DelayEstimatorSearchDelay" ))   mDelayEstimatorSearchDelay   = aCmd->argDouble(1);
   if(aCmd->isCmd("DelayEstimatorTolerance" ))     mDelayEstimatorTolerance     = aCmd->argDouble(1);
   if(aCmd->isCmd("DelayEstimatorMaxIterations" )) mDelayEstimatorMaxIterations = aCmd->argInt(1);
   if(aCmd->isCmd("DelayEstimatorFs" ))            mDelayEstimatorFs            = aCmd->argDouble(1);
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
}

