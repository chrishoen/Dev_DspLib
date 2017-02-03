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
#include "dspHistoryFilterParms.h"

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

HistoryFilterParms::HistoryFilterParms()
{
   reset();
}

void HistoryFilterParms::reset()
{
   BaseClass::reset();

   mFilterType    = cFilterIdentity;
   mFilterMethod  = cMethodSavGol;

   mFilterOrder = 1;
   mH = 1.0;

   mSelect = 1;

   mCausalType    = cCausalButterworthLP;
   mFs = 1.0;
   mFc = 1.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void HistoryFilterParms::show(char* aLabel)
{
   printf("HistoryFilterParms ************* BEGIN %s\n", aLabel);

   printf("FilterType         %10s\n",   asStringFilterType(mFilterType));
   printf("FilterMethod       %10s\n",   asStringFilterMethod(mFilterMethod));
   printf("FilterOrder        %10d\n",   mFilterOrder);
   printf("H                  %10.6f\n", mH);
   printf("Select             %10d\n",   mSelect);
   printf("CausalType      %10s\n",   asStringCausalType(mCausalType));
   printf("Fs                 %10.4f\n", mFs);
   printf("Fc                 %10.4f\n", mFc);

   printf("HistoryFilterParms ************* END   %s\n", aLabel);
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void HistoryFilterParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("FilterOrder"))     mFilterOrder = aCmd->argInt(1);
   if (aCmd->isCmd("H"))               mH           = aCmd->argDouble(1);
   if (aCmd->isCmd("Select"))          mSelect      = aCmd->argInt(1);
   if (aCmd->isCmd("Fs"))              mFs          = aCmd->argDouble(1);
   if (aCmd->isCmd("Fc"))              mFc          = aCmd->argDouble(1);

   if (aCmd->isCmd("FilterType"))
   {
      if (aCmd->isArgString(1,asStringFilterType(cFilterIdentity)))     mFilterType = cFilterIdentity;
      if (aCmd->isArgString(1,asStringFilterType(cFilterSmoother)))     mFilterType = cFilterSmoother;
      if (aCmd->isArgString(1,asStringFilterType(cFilterFirstDeriv)))   mFilterType = cFilterFirstDeriv;
      if (aCmd->isArgString(1,asStringFilterType(cFilterSecondDeriv)))  mFilterType = cFilterSecondDeriv;
   }

   if (aCmd->isCmd("FilterMethod"))
   {
      if (aCmd->isArgString(1,asStringFilterMethod(cMethodSavGol)))     mFilterMethod = cMethodSavGol;
      if (aCmd->isArgString(1,asStringFilterMethod(cMethodHolob)))      mFilterMethod = cMethodHolob;
   }

   if (aCmd->isCmd("CausalType"))
   {
      if (aCmd->isArgString(1,asStringCausalType(cCausalButterworthLP)))  mCausalType = cCausalButterworthLP;
      if (aCmd->isArgString(1,asStringCausalType(cCausalAlphaOne)))       mCausalType = cCausalAlphaOne;
      if (aCmd->isArgString(1,asStringCausalType(cCausalAlphaTwo)))       mCausalType = cCausalAlphaTwo;
      if (aCmd->isArgString(1,asStringCausalType(cCausalAlphaThree)))     mCausalType = cCausalAlphaThree;
   }

   // Pop back out at the end.
   if(aCmd->isCmd("}"    ))  nestedPop(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void HistoryFilterParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

char* HistoryFilterParms::asStringFilterType(int aX)
{
   switch (aX)
   {
   case cFilterIdentity    : return "Identity";
   case cFilterSmoother    : return "Smoother";
   case cFilterFirstDeriv  : return "FirstDeriv";
   case cFilterSecondDeriv : return "SecondDeriv";
   default : return "UNKNOWN";
   }
}

char* HistoryFilterParms::asStringFilterMethod(int aX)
{
   switch (aX)
   {
   case cMethodSavGol    : return "SavGol";
   case cMethodHolob     : return "Holob";
   default : return "UNKNOWN";
   }
}

char* HistoryFilterParms::asStringCausalType(int aX)
{
   switch (aX)
   {
   case cCausalButterworthLP    : return "ButterworthLP";
   case cCausalAlphaOne         : return "AlphaOne";
   case cCausalAlphaTwo         : return "AlphaTwo";
   case cCausalAlphaThree       : return "AlphaThree";
   default : return "UNKNOWN";
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

char* HistoryFilterParms::asStringFilterType()
{
   return asStringFilterType(mFilterType);
}

char* HistoryFilterParms::asStringFilterMethod()
{
   return asStringFilterMethod(mFilterMethod);
}

char* HistoryFilterParms::asStringCausalType()
{
   return asStringCausalType(mCausalType);
}


}//namespace