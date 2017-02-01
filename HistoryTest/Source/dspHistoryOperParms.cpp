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
#include "dspHistoryOperParms.h"

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

HistoryOperParms::HistoryOperParms()
{
   reset();
}

void HistoryOperParms::reset()
{
   BaseClass::reset();

   mOperType  = cOperIdentity;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void HistoryOperParms::show(char* aLabel)
{
   printf("HistoryOperParms ************** BEGIN %s\n", aLabel);

   printf("OperType           %10s\n",   asStringOperType(mOperType));
   printf("M                  %10d\n",   mM);

   printf("HistoryOperParms ************** END   %s\n", aLabel);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void HistoryOperParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("M"))           mM           = aCmd->argInt(1);

   if (aCmd->isCmd("OperType"))
   {
      if (aCmd->isArgString(1,asStringOperType(cOperIdentity)))     mOperType = cOperIdentity;
      if (aCmd->isArgString(1,asStringOperType(cOperDerivOne)))     mOperType = cOperDerivOne;
   }

   // Pop back out at the end.
   if(aCmd->isCmd("}"    ))  nestedPop(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void HistoryOperParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

char* HistoryOperParms::asStringOperType(int aOperType)
{
   switch (aOperType)
   {
   case cOperIdentity    : return "Identity";
   case cOperDerivOne    : return "DerivOne";
   default : return "UNKNOWN";
   }
}


}//namespace