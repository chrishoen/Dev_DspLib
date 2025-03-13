/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "dspHistory.h"
#include "dspHistoryStatistics.h"
#include "dspHistoryCsvFileWriter.h"
#include "dspHistoryCsvFileReader.h"
#include "dspHistoryGenerator.h"
#include "dspHistoryFilterOperator.h"

#include "Parms.h"
#include "TestOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun1()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read a signal history.

   // Signal history.
   History tHistoryX;

   // Signal history reader.
   HistoryCsvFileReader tReader;
   tReader.openFromFilepath(gParms.mInputFile);

   // Read the history.
   tReader.readHistory(0.002, 2, tHistoryX);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistoryXX;

   // Signal history generator.
   HistoryFilterOperator tFilter(gParms.mHistoryFilterParms1);

   // Apply the operator on the history to produce a new history. F:X->Y.
   tFilter.operate(tHistoryX,tHistoryXX);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistoryX);
   tStatistics.show(0,"X");

   tStatistics.collectValue(tHistoryXX);
   tStatistics.show(0,"XX");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistory(
      tHistoryX,
      tHistoryXX);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "TestOne::doRun1 %d",tHistoryX.mMaxSamples);
}

