//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnPaths.h"
#include "PulseParms.h"

#define  _PLOTWRITER_CPP_
#include "PlotWriter.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

PlotWriter::PlotWriter()
{
   mTime = 0;
   resetVars();
}

void PlotWriter::resetVars()
{
   mPulseFlag = false;
   mDetectFlag1 = false;
   mDetectFlag2 = false;
   mDetectFlag3 = false;
}

bool PlotWriter::initialize()
{
   auto tFilePath = Cmn::get_filepath_from_id(Cmn::cFile_PulsePlot);
   printf("PlotWriter::initialize %s\n", tFilePath->c_str());
   mTime = 0;
   resetVars();

   if (!mCsvFileWriter.open(tFilePath->c_str()))
   {
      printf("PlotWriter::initialize FAIL101\n");
      return false;
   }
   return true;
}

void PlotWriter::finalize()
{
   printf("PlotWriter::finalize\n");
   mCsvFileWriter.close();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to the history file.

void PlotWriter::doWrite()
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

void PlotWriter::doWrite1()
{
   mCsvFileWriter.writeRow(
      mTime,
      mPulseFlag  ? 1.0 : 0.0,
      mDetectFlag1  ? 1.0 : 0.0,
      mDetectFlag2  ? 1.0 : 0.0,
      mDetectFlag3  ? 1.0 : 0.0
   );
   
   mTime += 0.0020f;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write to the history file.

void PlotWriter::doWrite2()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
