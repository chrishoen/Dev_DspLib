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
   mDetectFlag1 = false;
   mDetectFlag2 = false;
   mDetectFlag3 = false;
   mCount1 = 0;
   mCount2 = 0;
   mCount3 = 0;
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
   char tString7[40]; tString7[0] = 0;
   char tString8[40]; tString8[0] = 0;

   if (mPulseFlag)                strcpy(tString1, "pulse");
   else                           strcpy(tString1, ".....");  
   if (mDetectFlag1)              strcpy(tString2, "detect1");
   else                           strcpy(tString2, ".......");  
   sprintf(tString3, "%5d", mCount1);

   mFileWriter.write("%s %s %s %s %s %s %s %s", 
      tString1,tString2,tString3,tString4,tString5,tString6,tString7,tString8);
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
