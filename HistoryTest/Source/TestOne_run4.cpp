/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "dspHistory.h"
#include "dspHistoryStatistics.h"
#include "dspHistoryTextFile.h"
#include "dspHistoryGenerator.h"
#include "dspHistoryConverters.h"

#include "Parms.h"
#include "TestOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun4()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistoryX;

   // Signal history generator.
   HistoryGenerator tGen(gParms.mHistoryGenParms);

   // Generate the history.
   tGen.generateHistory(tHistoryX);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history, converted

   // Signal history.
   History tHistoryY;

   // Signal history generator.
   convertHistoryFromType2ToType1(
      tHistoryX,
      gParms.mHistoryGenParms.mFs,
      tHistoryY);

   tHistoryX.show2(Prn::DspRun1,"X");
   tHistoryY.show2(Prn::DspRun1,"Y");
   Prn::print(Prn::DspRun1," ");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistoryX);
   tStatistics.show(0,"X   ");

   tStatistics.collectValue(tHistoryY);
   tStatistics.show(0,"Y   ");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistory(
      tHistoryX);
   tSampleWriter.close();

   tSampleWriter.open(gParms.mOutputFile2);
   tSampleWriter.writeHistory(
      tHistoryY);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "TestOne::doRun4 %d",tHistoryX.mMaxSamples);
}

