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
   mAc1 = 1.0;
   mAc2 = 1.0;
   mPc1 = 0.0;
   mPc2 = 0.0;
   mFcRandom = 0.0;
   mAcRandom = 0.0;
   mPcRandom = 0.0;

   strcpy(mOutputFile,"Dynamic.txt");

   mTs = 1.0 / mFs;
   mNumSamples = (int)(mDuration * mFs);
}

void Parms::expand()
{
   mTs = 1.0 / mFs;
   mNumSamples = (int)(round(mDuration) * mFs);
}

void Parms::show()
{
   printf("Parms ******* %s\n", mSection);

   printf("mDuration    %10.4f\n",mDuration);
   printf("mFs          %10.4f\n",mFs);
   printf("mFc          %10.4f\n",mFc);
   printf("mEX          %10.4f\n",mEX);
   printf("mUX          %10.4f\n",mUX);

   printf("mFc1         %10.4f\n",mFc1);
   printf("mFc2         %10.4f\n",mFc2);
   printf("mAc1         %10.4f\n",mAc1);
   printf("mAc2         %10.4f\n",mAc2);
   printf("mPc1         %10.4f\n",deg(mPc1));

   printf("mFcRandom    %10.4f\n",mFcRandom);
   printf("mAcRandom    %10.4f\n",mAcRandom);
   printf("mPcRandom    %10.4f\n",deg(mPcRandom));

   printf("mOutputFile  %10s\n",  mOutputFile);

   printf("Parms ******* %s\n", mSection);
}

//******************************************************************************
// For a given command line "Begin Section", this returns true
// if "Section", the first command line argument, is the same as the section 
// specified in initialize.

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

   if(aCmd->isCmd("Duration"    )) mDuration  = aCmd->argDouble(1);
   if(aCmd->isCmd("Fs"          )) mFs        = aCmd->argDouble(1);
   if(aCmd->isCmd("Fc"          )) mFc        = aCmd->argDouble(1);
   if(aCmd->isCmd("EX"          )) mEX        = aCmd->argDouble(1);
   if(aCmd->isCmd("UX"          )) mUX        = aCmd->argDouble(1);

   if(aCmd->isCmd("Fc1"         )) mFc1       = aCmd->argDouble(1);
   if(aCmd->isCmd("Fc2"         )) mFc2       = aCmd->argDouble(1);
   if(aCmd->isCmd("Ac1"         )) mAc1       = aCmd->argDouble(1);
   if(aCmd->isCmd("Ac2"         )) mAc2       = aCmd->argDouble(1);
   if(aCmd->isCmd("Pc1"         )) mPc1       = aCmd->argAngle(1);
   if(aCmd->isCmd("Pc2"         )) mPc2       = aCmd->argAngle(1);

   if(aCmd->isCmd("FcRandom"    )) mFcRandom  = aCmd->argDouble(1);
   if(aCmd->isCmd("AcRandom"    )) mAcRandom  = aCmd->argDouble(1);
   if(aCmd->isCmd("PcRandom"    )) mPcRandom  = aCmd->argAngle(1);

   if(aCmd->isCmd("OutputFile"  )) aCmd->copyArgString(1,mOutputFile,cMaxStringSize);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

bool Parms::readSection(char* aSection)
{ 
   // File path
   char tFilePath[200];

   strcpy(tFilePath, Ris::portableGetCurrentWorkingDir());
   strcat(tFilePath, "..\\..\\Files\\Parms.txt");

   // Copy arguments
   strcpy(mSection,aSection);
   mDefaultSection = strcmp(mSection,"default")==0;

   // Apply settings file to this executive   
   Ris::CmdLineFile tCmdLineFile;

   if (tCmdLineFile.open(tFilePath))
   {
      if (mDefaultSection)
      {
         printf("Parms::file open PASS %s\n", tFilePath);
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




