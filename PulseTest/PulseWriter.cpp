//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risBitUtils.h"
#include "cmnPaths.h"
#include "PulseParms.h"

#define  _PULSEWRITER_CPP_
#include "PulseWriter.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

PulseWriter::PulseWriter()
{
   resetVars();
}

void PulseWriter::resetVars()
{
   mPulseFlag = false;
   mPulseRise = false;
   mPulseFall = false;

   mDetectFlag = false;
   mDetectRise = false;
   mDetectFall = false;

   mCount = 0;
}

bool PulseWriter::initialize()
{
   auto tFilePath = Cmn::get_filepath_from_id(Cmn::cFile_PulsePulse);
   printf("PulseWriter::initialize %s\n", tFilePath->c_str());
   resetVars();

   if (!mFileWriter.open(tFilePath->c_str()))
   {
      printf("PulseWriter::initialize FAIL101\n");
      return false;
   }
   return true;
}

void PulseWriter::finalize()
{
   printf("PulseWriter::finalize\n");
   mFileWriter.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to the history file.

void PulseWriter::doWrite()
{
    switch(1)
    {
      case 1: doWrite1(); break;
      case 2: doWrite2(); break;
    }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to the history file.

void PulseWriter::doWrite1()
{
   char tString1[40]; tString1[0] = 0;
   char tString2[40]; tString2[0] = 0;
   char tString3[40]; tString3[0] = 0;
   char tString4[40]; tString4[0] = 0;
   char tString5[40]; tString5[0] = 0;
   char tString6[40]; tString6[0] = 0;

   if (mPulseFlag)                strcpy(tString1, "pulse");
   else                           strcpy(tString1, ".....");  
   if (mDetectFlag)               strcpy(tString2, "detect");
   else                           strcpy(tString2, "..... ");  
   if (mPulseRise)                strcpy(tString3, "prise");
   else if (mPulseFall)           strcpy(tString3, "pfall");  
   else                           strcpy(tString3, "     ");  
   if (mDetectRise)               strcpy(tString4, "drise");
   else if (mDetectFall)          strcpy(tString4, "dfall");  
   else                           strcpy(tString4, "     ");  
   sprintf(tString5, "%5d", mCount);
   if (mPulseRise)                strcpy(tString6, "here ");
   else                           strcpy(tString6, "     ");

   mFileWriter.write("%s %s %s %s %s %s", 
      tString1,tString2,tString3,tString4,tString5,tString6);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to the history file.

void PulseWriter::doWrite2()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
