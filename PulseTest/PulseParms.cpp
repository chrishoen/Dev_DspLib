//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnPaths.h"

#define  _PULSEPARMS_CPP_
#include "PulseParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Samp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

PulseParms::PulseParms()
{
   resetVars();
}

void PulseParms::reset()
{
   BaseClass::reset();
   BaseClass::setFilePath(Cmn::get_files_filepath("Pulse_Parms.txt"));
   resetVars();
}

void PulseParms::resetVars()
{
   mFilterDT = 0;
   mFilterStepTime = 0;
   mCountMax = 0;
   mCountMin = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void PulseParms::show()
{
   printf("\n");
   printf("PulseParms************************************************ %s\n", mTargetSection);

   printf("\n");

   printf("FilterDT                     %-10.4f\n", mFilterDT);
   printf("FilterStepTime               %-10.4f\n", mFilterStepTime);
   printf("CountMax                     %-10d\n",    mCountMax);
   printf("CountMin                     %-10d\n",    mCountMin);
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void PulseParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("FilterDT"))                 mFilterDT = aCmd->argDouble(1);
   if (aCmd->isCmd("FilterStepTime"))           mFilterStepTime = aCmd->argDouble(1);

   if (aCmd->isCmd("CountMax"))                 mCountMax = aCmd->argInt(1);
   if (aCmd->isCmd("CountMin"))                 mCountMax = aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void PulseParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace