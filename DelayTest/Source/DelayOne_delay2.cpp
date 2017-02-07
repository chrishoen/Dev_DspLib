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
#include "dspHistoryLoopClock.h"
#include "dspHistoryTextFile.h"
#include "dspHistoryGenGen.h"
#include "dspHistoryFilterOperator.h"

#include "Parms.h"
#include "DelayOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void DelayOne::doDelay2()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate two signal histories.

   // Signal history.
   History tHistoryX1;
   History tHistoryX2;

   // Generate two of the same signal.
   HistoryGenGen tGen1(gParms.mHistoryGenParms);
   HistoryGenGen tGen2(gParms.mHistoryGenParms);


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
   tStatistics.show();

   tStatistics.collectValue(tHistoryDX1);
   tStatistics.show();

   tStatistics.collectValue(tHistoryDX2);
   tStatistics.show();

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

   Prn::print(0, "DelayOne::doDelay2 %d",tHistoryX.mMaxSamples);
}

