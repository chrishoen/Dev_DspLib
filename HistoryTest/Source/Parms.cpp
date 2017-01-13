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

Parms::Parms()
{
   reset();
}

void Parms::reset()
{
   mSection[0]=0;
   mSectionMode[0]=0;
   mSectionFlag=false;
   mDefaultSection=false;

   mDuration = 10.0;
   mFs = 1.0;
   mFc = 1.0;
   mEX = 0.0;
   mUX = 1.0;

   mFc1 = 1.0;
   mFc2 = 1.0;

   mFilterOrder = 4;

   strcpy(mOutputFile,"Dynamic.txt");

   mTs = 1.0 / mFs;
   mNumSamples = (int)(mDuration * mFs);

   mHistoryMaxSamples=0;
   mHistoryDeltaT=0.0;

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Parms::expand()
{
   mTs = 1.0 / mFs;
   mNumSamples = (int)(round(mDuration) * mFs);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

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
// For a given command line "Begin Section", this returns true
// if "Section", the first command line argument, is the same as the section 
// specified at a call to read section.

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
// This is called for each command line in the settings file.
// It processes commands, with arguments
// BEGIN starts a section, END exits a section
// Only commands for a section are processed

void Parms::execute(Ris::CmdLineCmd* aCmd)
{
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Section commands


   if(aCmd->isCmd("SectionBegin"      ))  mSectionFlag=isMySection(aCmd);
   if(aCmd->isCmd("SectionEnd"        ))  mSectionFlag=false;

   if (!mSectionFlag) return;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Only process commands for the section specified in initialize.

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

bool Parms::readSection(char* aSection)
{ 
   // File path
   char tFilePath[200];

   strcpy(tFilePath, Ris::portableGetCurrentWorkingDir());
   strcat(tFilePath, "..\\..\\Files\\History_Parms.txt");

   // Copy arguments
   strcpy(mSection,aSection);
   mDefaultSection = strcmp(mSection,"default")==0;

   // Apply settings file to this executive   
   Ris::CmdLineFile tCmdLineFile;

   if (tCmdLineFile.open(tFilePath))
   {
      if (mDefaultSection)
      {
       //printf("Parms::file open PASS %s\n", tFilePath);
      }
      tCmdLineFile.execute(this);
      tCmdLineFile.close();
      expand();
      return true;
   }
   else
   {
      printf("Parms::file open FAIL %s\n",tFilePath);
      return false;
   }
}




