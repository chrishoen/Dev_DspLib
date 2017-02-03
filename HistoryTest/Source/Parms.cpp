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

   mHistoryGenParms.reset();
   mHistoryFilterParms1.reset();
   mHistoryFilterParms2.reset();

   mOutputFile[0]=0;

   mHistoryMaxSamples=0;
   mHistoryDeltaT=0.0;

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
   printf("HistoryMaxSamples  %10d\n",  mHistoryMaxSamples);
   printf("HistoryDeltaT      %10.4f\n",mHistoryDeltaT);
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

   if(aCmd->isCmd("HistoryGenParms"))    nestedPush(aCmd, &mHistoryGenParms);
   if(aCmd->isCmd("HistoryFilterParms1"))  nestedPush(aCmd, &mHistoryFilterParms1);
   if(aCmd->isCmd("HistoryFilterParms2"))  nestedPush(aCmd, &mHistoryFilterParms2);

   if(aCmd->isCmd("HistoryMaxSamples" )) mHistoryMaxSamples  = aCmd->argInt(1);
   if(aCmd->isCmd("HistoryDeltaT"     )) mHistoryDeltaT      = aCmd->argDouble(1);
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

