//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>

#include "my_functions.h"
#include "risCmdLineFile.h"
#include "risPortableCalls.h"

#define  _SETTINGS_CPP_
#include "Settings.h"

//******************************************************************************

   Settings::Settings()
{
   mSection[0]=0;

   mDuration = 10.0;
   mFs = 1.0;
   mFp = 1.0;
   mAmplitude = 1.0;
   mSigma = 0.0;
   mOffset = 0.0;
}

void Settings::show()
{
   printf("Settings ******* %s\n", mSection);

   printf("mDuration    %10.4f\n",mDuration);
   printf("mFs          %10.4f\n",mFs);
   printf("mFp          %10.4f\n",mFp);
   printf("mSigma       %10.4f\n",mSigma);
   printf("mOffset      %10.4f\n",mOffset);
   printf("mAmplitude   %10.4f\n",mAmplitude);

   printf("Settings ******* %s\n", mSection);
}

//******************************************************************************
// For a given command line "Begin Section", this returns true
// if "Section", the first command line argument, is the same as the section 
// specified in initialize.

bool Settings::isMySection(Ris::CmdLineCmd* aCmd)
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

void Settings::execute(Ris::CmdLineCmd* aCmd)
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

   if(aCmd->isCmd("Duration"    )) mDuration  = aCmd->argDouble(1);
   if(aCmd->isCmd("Fs"          )) mFs        = aCmd->argDouble(1);
   if(aCmd->isCmd("Fp"          )) mFp        = aCmd->argDouble(1);
   if(aCmd->isCmd("Offset"      )) mOffset    = aCmd->argDouble(1);
   if(aCmd->isCmd("Amplitude"   )) mAmplitude = aCmd->argDouble(1);
   if(aCmd->isCmd("Sigma"       )) mSigma     = aCmd->argDouble(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

bool Settings::initialize(char* aSection)
{ 
   // File path
   char tFilePath[200];

   strcpy(tFilePath, Ris::portableGetCurrentWorkingDir());
   strcat(tFilePath, "..\\..\\Files\\RandomMotionSettings.txt");

   // Copy arguments
   strcpy(mSection,aSection);
   // Apply settings file to this executive   
   Ris::CmdLineFile tCmdLineFile;

   if (tCmdLineFile.open(tFilePath))
   {
      printf("Settings::file open PASS %s\n",tFilePath);
      tCmdLineFile.execute(this);
      tCmdLineFile.close();
      return true;
   }
   else
   {
      printf("Settings::file open FAIL %s\n",tFilePath);
      return false;
   }
}




