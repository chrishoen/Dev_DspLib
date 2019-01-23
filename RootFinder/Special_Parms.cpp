//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "my_functions.h"
#include "risCmdLineFile.h"
#include "risPortableCalls.h"

#define  _CALCSPECIALPARMS_CPP_
#include "Special_Parms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

Special_Parms::Special_Parms()
{
   reset();
}

void Special_Parms::reset()
{
   BaseClass::reset();
   strcpy(BaseClass::mDefaultFileName,  "Special_Parms.txt");
   strcpy(BaseClass::mOverrideFileName, "Special_Parms.txt");

   
   mC0 = 0.0;
   mC1 = 0.0;
   mC2 = 0.0;

   mX0 = 0.0;
   mY0 = 0.0;


   mA120 = 0.0;
   mA121 = 0.0;
   mA122 = 0.0;
   mA340 = 0.0;
   mA341 = 0.0;
   mA342 = 0.0;

   mB120 = 0.0;
   mB121 = 0.0;
   mB122 = 0.0;
   mB340 = 0.0;
   mB341 = 0.0;
   mB342 = 0.0;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void Special_Parms::show()
{
   printf("\n");
   printf("Special_Parms ******************************************\n");

   printf("\n");
   printf("C0                        %10.6f\n", mC0);
   printf("C1                        %10.6f\n", mC1);
   printf("C2                        %10.6f\n", mC2);
   printf("X0                     %10.6f\n", mX0);
   printf("Y0                      %10.6f\n", mY0);
   printf("A120                      %10.6f\n", mA120);
   printf("A121                      %10.6f\n", mA121);
   printf("A122                      %10.6f\n", mA122);
   printf("A340                      %10.6f\n", mA340);
   printf("A341                      %10.6f\n", mA341);
   printf("A342                      %10.6f\n", mA342);
   printf("B120                      %10.6f\n", mB120);
   printf("B121                      %10.6f\n", mB121);
   printf("B122                      %10.6f\n", mB122);
   printf("B340                      %10.6f\n", mB340);
   printf("B341                      %10.6f\n", mB341);
   printf("B342                      %10.6f\n", mB342);
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void Special_Parms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   
   if(aCmd->isCmd("C0"))          mC0 = aCmd->argDouble(1);
   if(aCmd->isCmd("C1"))          mC1 = aCmd->argDouble(1);
   if(aCmd->isCmd("C2"))          mC2 = aCmd->argDouble(1);
   if (aCmd->isCmd("X0"))          mX0 = aCmd->argDouble(1);
   if (aCmd->isCmd("Y0"))          mY0 = aCmd->argDouble(1);
   if (aCmd->isCmd("A120"))        mA120 = aCmd->argDouble(1);
   if (aCmd->isCmd("A121"))        mA121 = aCmd->argDouble(1);
   if (aCmd->isCmd("A122"))        mA122 = aCmd->argDouble(1);
   if (aCmd->isCmd("A340"))        mA340 = aCmd->argDouble(1);
   if (aCmd->isCmd("A341"))        mA341 = aCmd->argDouble(1);
   if (aCmd->isCmd("A342"))        mA342 = aCmd->argDouble(1);
   if (aCmd->isCmd("B120"))        mB120 = aCmd->argDouble(1);
   if (aCmd->isCmd("B121"))        mB121 = aCmd->argDouble(1);
   if (aCmd->isCmd("B122"))        mB122 = aCmd->argDouble(1);
   if (aCmd->isCmd("B340"))        mB340 = aCmd->argDouble(1);
   if (aCmd->isCmd("B341"))        mB341 = aCmd->argDouble(1);
   if (aCmd->isCmd("B342"))        mB342 = aCmd->argDouble(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void Special_Parms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************



