//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>

#include "my_functions.h"
#include "dsp_math.h"
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
   // File member variables.
   mSection[0]=0;
   mSectionFlag=false;

   // Parameter member variables.
   mDuration = 10.0;
   mFs = 1.0;
   mFc = 1.0;
   mEX = 0.0;
   mUX = 1.0;

   mFc1 = 1.0;
   mFc2 = 1.0;

   mFilterOrder = 4;

   mOutputFile[0]=0;

   mTs = 1.0 / mFs;
   mNumSamples = (int)(mDuration * mFs);

   mHistoryMaxSamples=0;
   mHistoryDeltaT=0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void Parms::expand()
{
   mTs = 1.0 / mFs;
   mNumSamples = (int)(round(mDuration) * mFs);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void Parms::show()
{
   printf("Parms ******* %s\n", mSection);

   printf("Code1               %d\n",mCode1);
   printf("Code2               %d\n",mCode2);
   printf("mDuration          %10.4f\n",mDuration);
   printf("mFs                %10.4f\n",mFs);
   printf("mFc                %10.4f\n",mFc);
   printf("mEX                %10.4f\n",mEX);
   printf("mUX                %10.4f\n",mUX);

   printf("mFc1               %10.4f\n",mFc1);
   printf("mFc2               %10.4f\n",mFc2);
   printf("mFilterOrder       %10d\n",  mFilterOrder);

   printf("mOutputFile        %10s\n",  mOutputFile);

   printf("mHistoryMaxSamples %10d\n",  mHistoryMaxSamples);
   printf("mHistoryDeltaT     %10.4f\n",mHistoryDeltaT);

   mHistoryGenWiener.show("HistoryGenWiener");

   printf("Parms ******* %s\n", mSection);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable. This is called by the associated command file object
// for each command in the file.

void Parms::execute(Ris::CmdLineCmd* aCmd)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Section commands. If not in the section to be read then exit.


   if(aCmd->isCmd("SectionBegin"      ))  mSectionFlag=isMySection(aCmd);
   if(aCmd->isCmd("SectionEnd"        ))  mSectionFlag=false;

   if (!mSectionFlag) return;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Jump table: Execute the command to set a member variable. Only process   
   // commands for the section to be read.

   if(aCmd->isCmd("Code1"))  mCode1 = aCmd->argInt (1);
   if(aCmd->isCmd("Code2"))  mCode2 = aCmd->argInt (1);

   if(aCmd->isCmd("Duration"          )) mDuration           = aCmd->argDouble(1);
   if(aCmd->isCmd("Fs"                )) mFs                 = aCmd->argDouble(1);
   if(aCmd->isCmd("Fc"                )) mFc                 = aCmd->argDouble(1);
   if(aCmd->isCmd("EX"                )) mEX                 = aCmd->argDouble(1);
   if(aCmd->isCmd("UX"                )) mUX                 = aCmd->argDouble(1);

   if(aCmd->isCmd("Fc1"               )) mFc1                = aCmd->argDouble(1);
   if(aCmd->isCmd("Fc2"               )) mFc2                = aCmd->argDouble(1);
   if(aCmd->isCmd("FilterOrder"       )) mFilterOrder        = aCmd->argInt(1);
   if(aCmd->isCmd("HistoryMaxSamples" )) mHistoryMaxSamples  = aCmd->argInt(1);
   if(aCmd->isCmd("HistoryDeltaT"     )) mHistoryDeltaT      = aCmd->argDouble(1);

   if(aCmd->isCmd("OutputFile"  )) aCmd->copyArgString(1,mOutputFile,cMaxStringSize);

   if(aCmd->isCmd("HistoryGenWiener")) nestedPush(aCmd, &mHistoryGenWiener);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return true if the input command's first argument is equal to the
// section that is to be read. This is called if the command is
// "SectionBegin" and returns true if the section is equal to the section
// that is to be read.

bool Parms::isMySection(Ris::CmdLineCmd* aCmd)
{
   bool tFlag=false;

   if (aCmd->numArg()==1)
   {
      if (aCmd->isArgString(1,mSection))
      {
         tFlag=true;
      }
   }

   return tFlag;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read a section of the command file and set member variables accordingly.
// Create a command file object, open the file, pass this object to the file
// object to read the file and apply this object's execution method to each
// command in the file, and then close the file. This only reads variables for
// a specific section in the file.

bool Parms::readSection(char* aSection)
{ 
   // Store arguments.
   strcpy(mSection,aSection);

   // File path.
   char tFilePath[200];

   strcpy(tFilePath, Ris::portableGetCurrentWorkingDir());
   strcat(tFilePath, "..\\..\\Files\\History_Parms.txt");

   // Temporary command line file object.   
   Ris::CmdLineFile tCmdLineFile;

   // Open the file.
   if (tCmdLineFile.open(tFilePath))
   {
      // Pass this object to the file object to read the file and apply this
      // object's execution method to each command in the file.
      tCmdLineFile.execute(this);

      // Close the file.
      tCmdLineFile.close();

      // Expand extra member variables.
      expand();

   //printf("Parms::file open PASS %s\n", tFilePath);
      return true;
   }
   else
   {
      printf("Parms::file open FAIL %s\n",tFilePath);
      return false;
   }
}




