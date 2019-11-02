//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspSlowThresholderParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SlowThresholderParms::SlowThresholderParms()
{
   reset();
}

void SlowThresholderParms::reset()
{
   mMode = 0;

   mFAFTs = 0.0;
   mFAFTc = 0.0;
   mFAFThreshHi = 0.0;
   mFAFThreshLo = 0.0;
   mSignalThresh1Lo = 0.0;
   mSignalThresh1Hi = 0.0;
   mSignalThresh2Lo = 0.0;
   mSignalThresh2Hi = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Set expanded member variables. This is called after the entire
// section of the command file has been processed.

void SlowThresholderParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SlowThresholderParms::show()
{
   printf("\n");
   printf("SlowThresholderParms*************************************BEGIN\n");

   printf("\n");
   printf("Mode                      %10d\n", mMode);
   printf("\n");

   printf("\n");
   printf("FAFTs                     %10.4f\n", mFAFTs);
   printf("FAFTc                     %10.4f\n", mFAFTc);
   printf("\n");

   printf("FAFThreshLo               %10.4f\n", mFAFThreshLo);
   printf("FAFThreshHi               %10.4f\n", mFAFThreshHi);
   printf("SignalThresh1Lo           %10.4f\n", mSignalThresh1Lo);
   printf("SignalThresh1Hi           %10.4f\n", mSignalThresh1Hi);
   printf("SignalThresh2Lo           %10.4f\n", mSignalThresh2Lo);
   printf("SignalThresh2Hi           %10.4f\n", mSignalThresh2Hi);

   printf("\n");
   printf("SlowThresholderParms*************************************END\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SlowThresholderParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("Mode"))              mMode = aCmd->argInt(1);

   if (aCmd->isCmd("FAFTs"))             mFAFTs = aCmd->argDouble(1);
   if (aCmd->isCmd("FAFTc"))             mFAFTc = aCmd->argDouble(1);

   if (aCmd->isCmd("FAFThreshLo"))       mFAFThreshLo = aCmd->argDouble(1);
   if (aCmd->isCmd("FAFThreshHi"))       mFAFThreshHi = aCmd->argDouble(1);
   if (aCmd->isCmd("SignalThresh1Lo"))   mSignalThresh1Lo = aCmd->argDouble(1);
   if (aCmd->isCmd("SignalThresh1Hi"))   mSignalThresh1Hi = aCmd->argDouble(1);
   if (aCmd->isCmd("SignalThresh2Lo"))   mSignalThresh2Lo = aCmd->argDouble(1);
   if (aCmd->isCmd("SignalThresh2Hi"))   mSignalThresh2Hi = aCmd->argDouble(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace