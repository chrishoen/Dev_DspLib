/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <math.h>
#include "my_functions.h"
#include "prnPrint.h"
#include "logFiles.h"

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
   History tHistoryX;

   // Signal history generator.
   HistoryGenerator tGen(gParms.mHistoryGenParms);

   // Generate the history.
   tGen.generateHistory(tHistoryX);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Filter the signal history. Differentiator.

   // Signal history.
   History tHistoryDX1;

   // Signal history filter.
   HistoryFilterOperator tDifferentiator1(gParms.mHistoryFilterParms1);

   // Apply the operator on the history to produce a new history. F:XS->Y,DY.
   tDifferentiator1.operate(tHistoryX,tHistoryDX1);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Filter the signal history. Differentiator.

   // Signal history.
   History tHistoryDX2;

   // Signal history filter.
   HistoryFilterOperator tDifferentiator2(gParms.mHistoryFilterParms2);

   // Apply the operator on the history to produce a new history. F:XS->Y,DY.
   tDifferentiator2.operate(tHistoryX,tHistoryDX2);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistoryX);
   tStatistics.show(0,"X  ");

   tStatistics.collectValue(tHistoryDX1);
   tStatistics.show(0,"DX1");

   tStatistics.collectValue(tHistoryDX2);
   tStatistics.show(0,"DX2");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistory(tHistoryX,tHistoryDX1,tHistoryDX2);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "DemoOne::doDemo2 %d",tHistoryX.mMaxSamples);
}

