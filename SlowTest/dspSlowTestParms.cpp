//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#define  _SlowTESTPARMS_CPP_
#include "dspSlowTestParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

SlowTestParms::SlowTestParms()
{
   reset();
}

void SlowTestParms::reset()
{
   BaseClass::reset();
   BaseClass::setFilePath_RelativeToBaseDir("files/SlowTest_Parms.txt");

   mTimerPeriod = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Simulate expanded member variables. This is called after the entire
// section of the command file has been processed.

void SlowTestParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void SlowTestParms::show()
{
   printf("\n");
   printf("SlowTestParms************************************************ %s\n", mTargetSection);
   printf("TimerPeriod            %10d\n", mTimerPeriod);

   printf("\n");
   mThresholderParms.show();
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void SlowTestParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("TimerPeriod"))   mTimerPeriod = aCmd->argInt(1);

   if (aCmd->isCmd("Thresholder"))   readSection(aCmd->argString(1), &mThresholderParms);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace