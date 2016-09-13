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
#include "FilterCo.h"

//******************************************************************************

FilterCo::FilterCo()
{
   reset();
}

void FilterCo::reset()
{
   mSection[0]=0;
   mSectionMode[0]=0;
   mSectionFlag=false;
   mDefaultSection=false;

   mBandPassB1.initialize(5);
   mBandPassA1.initialize(5);
   mCode1=0;
   mCode2=0;
}

void FilterCo::show()
{
   printf("FilterCo ******* %s\n", mSection);

   mBandPassB1.show("BandPassB1");
   mBandPassA1.show("BandPassA1");

   printf("Code1      %10d\n",  mCode1);
   printf("Code2      %10d\n",  mCode2);

   printf("FilterCo ******* %s\n", mSection);
}

//******************************************************************************
// For a given command line "Begin Section", this returns true
// if "Section", the first command line argument, is the same as the section 
// specified in initialize.

bool FilterCo::isMySection(Ris::CmdLineCmd* aCmd)
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

void FilterCo::execute(Ris::CmdLineCmd* aCmd)
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

   if (aCmd->isCmd("FilterB1"))           mBandPassB1.execute(aCmd);
   if (aCmd->isCmd("FilterA1"))           mBandPassA1.execute(aCmd);

   if(aCmd->isCmd("Code1"        ))       mCode1 = aCmd->argInt(1);
   if(aCmd->isCmd("Code2"        ))       mCode2 = aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

bool FilterCo::readSection(char* aSection)
{ 
   // File path
   char tFilePath[200];

   strcpy(tFilePath, Ris::portableGetCurrentWorkingDir());
   strcat(tFilePath, "..\\..\\Files\\DspFilterCo.txt");

   // Copy arguments
   strcpy(mSection,aSection);
   mDefaultSection = strcmp(mSection,"default")==0;

   // Apply settings file to this executive   
   Ris::CmdLineFile tCmdLineFile;

   if (tCmdLineFile.open(tFilePath))
   {
      if (mDefaultSection)
      {
         printf("FilterCo::file open PASS %s\n", tFilePath);
      }
      tCmdLineFile.execute(this);
      tCmdLineFile.close();
      return true;
   }
   else
   {
      printf("FilterCo::file open FAIL %s\n",tFilePath);
      return false;
   }
}




