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

   mOperType    = cOperIdentity;
   mFiltStruct  = cFiltStructSavGol;

   mFilterOrder = 1;
   mH = 1.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void HistoryOperParms::show(char* aLabel)
{
   printf("HistoryOperParms ************* BEGIN %s\n", aLabel);

   printf("OperType           %10s\n",   asStringOperType(mOperType));
   printf("FiltStruct         %10s\n",   asStringFiltStruct(mFiltStruct));
   printf("FilterOrder        %10d\n",   mFilterOrder);
   printf("H                  %10.6f\n", mH);

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
   if (aCmd->isCmd("FilterOrder"))     mFilterOrder = aCmd->argInt(1);
   if (aCmd->isCmd("H"))               mH           = aCmd->argDouble(1);

   if (aCmd->isCmd("OperType"))
   {
      if (aCmd->isArgString(1,asStringOperType(cOperIdentity)))     mOperType = cOperIdentity;
      if (aCmd->isArgString(1,asStringOperType(cOperSmoother)))     mOperType = cOperSmoother;
      if (aCmd->isArgString(1,asStringOperType(cOperDerivOne)))     mOperType = cOperDerivOne;
   }

   if (aCmd->isCmd("FiltStruct"))
   {
      if (aCmd->isArgString(1,asStringFiltStruct(cFiltStructSavGol)))     mFiltStruct = cFiltStructSavGol;
      if (aCmd->isArgString(1,asStringFiltStruct(cFiltStructHolob)))      mFiltStruct = cFiltStructHolob;
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

char* HistoryOperParms::asStringOperType(int aX)
{
   switch (aX)
   {
   case cOperIdentity    : return "Identity";
   case cOperSmoother    : return "Smoother";
   case cOperDerivOne    : return "DerivOne";
   default : return "UNKNOWN";
   }
}

char* HistoryOperParms::asStringFiltStruct(int aX)
{
   switch (aX)
   {
   case cFiltStructSavGol    : return "SavGol";
   case cFiltStructHolob     : return "Holob";
   default : return "UNKNOWN";
   }
}


}//namespace