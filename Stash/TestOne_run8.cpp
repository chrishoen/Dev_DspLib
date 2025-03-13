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
#include "dspHistoryFilterOperator.h"

#include "Parms.h"
#include "TestOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun8()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read an input signal history from a file.

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
   // Generate an output signal history from the input.

   // Signal history.
   History tHistoryEX;
   History tHistoryUX;

   // Signal history generator.
   HistoryFilterOperator tFilter(gParms.mHistoryFilterParms1);

   // Apply the operator on the history to produce a new history. F:X->Y.
   tFilter.operate(tHistoryX,tHistoryEX,tHistoryUX);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistoryX);
   tStatistics.show(0,"X");

   tStatistics.collectValue(tHistoryEX);
   tStatistics.show(0,"EX");

   tStatistics.collectValue(tHistoryUX);
   tStatistics.show(0,"UX");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write the output signal history to a file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistory(
      tHistoryX,
      tHistoryEX,
      tHistoryUX);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "TestOne::doRun8 %d",tHistoryX.mMaxSamples);
}

