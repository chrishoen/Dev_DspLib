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
#include "dspHistoryFilterOperator.h"

#include "Parms.h"
#include "DemoOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void DemoOne::doDemo2()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistoryXX;

   // Signal history generator.
   HistoryGenerator tGen(gParms.mHistoryGenParms);

   // Generate the history.
   tGen.generateHistory(tHistoryXX);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Filter the signal history. Differentiator.

   // Signal history.
   History tHistoryXV;

   // Signal history filter.
   HistoryFilterOperator tDifferentiator(gParms.mHistoryFilterParms1);

   // Apply the operator on the history to produce a new history. F:XS->Y,DY.
   tDifferentiator.operate(tHistoryXX,tHistoryXV);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistoryXX);
   tStatistics.show(0,"XX");

   tStatistics.collectValue(tHistoryXV);
   tStatistics.show(0,"XV");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistory(tHistoryXX,tHistoryXV);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "DemoOne::doDemo2 %d",tHistoryXX.mMaxSamples);
}

