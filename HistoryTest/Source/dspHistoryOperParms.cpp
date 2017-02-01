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
   mFilterOrder = 1;
   mN = 1;
   mM = 0;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void HistoryOperParms::show(char* aLabel)
{
   printf("HistoryOperParms ************* BEGIN %s\n", aLabel);

   printf("OperType           %10s\n",   asStringOperType(mOperType));
   printf("FilterOrder        %10d\n",   mFilterOrder);
   printf("N                  %10d\n",   mN);
   printf("M                  %10d\n",   mM);

   printf("HistoryOperParms ************* END   %s\n", aLabel);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void HistoryOperParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("FilterOrder"))           mFilterOrder = aCmd->argInt(1);

   if (aCmd->isCmd("OperType"))
   {
      if (aCmd->isArgString(1,asStringOperType(cOperIdentity)))     mOperType = cOperIdentity;
      if (aCmd->isArgString(1,asStringOperType(cOperSmoother)))     mOperType = cOperSmoother;
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
   // Guard, filter order must be odd.
   if (mFilterOrder<=0) mFilterOrder=1;
   if (mFilterOrder%2==0) mFilterOrder++;

   mN = mFilterOrder;
   mM = (mN-1)/2;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

char* HistoryOperParms::asStringOperType(int aOperType)
{
   switch (aOperType)
   {
   case cOperIdentity    : return "Identity";
   case cOperSmoother    : return "Smoother";
   case cOperDerivOne    : return "DerivOne";
   default : return "UNKNOWN";
   }
}


}//namespace