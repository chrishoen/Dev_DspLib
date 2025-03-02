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
#include "dspHistoryGenerator.h"

#include "Parms.h"
#include "TestOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun1Deg()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   gParms.mHistoryGenParms.show("Gen");

   // Signal history.
   History tHistory;

   // Signal history generator.
   HistoryGenerator tGen(gParms.mHistoryGenParms);

   // Generate the history.
   tGen.generateHistory(tHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistory);
   tStatistics.showDeg(0,"H   ");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistoryDeg(tHistory);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "TestOne::doRun1Deg %d",tHistory.mMaxSamples);
}

