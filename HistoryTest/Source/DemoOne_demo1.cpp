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
#include "DemoOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void DemoOne::doDemo1()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistoryX;

   // Signal history generator.
   HistoryGenGen tGen(gParms.mHistoryGenParms);

   // Generate the history.
   tGen.generateHistory(tHistoryX);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Filter the signal history. Smoother.

   // Signal history.
   History tHistoryXS;

   // Signal history filter.
   HistoryFilterOperator tSmoother(gParms.mHistoryFilterParms1);

   // Apply the operator on the history to produce a new history. F:X->XS.
   tSmoother.operate(tHistoryX,tHistoryXS);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Filter the signal history. Differentiator.

   // Signal history.
   History tHistoryY;
   History tHistoryDY;

   // Signal history filter.
   HistoryFilterOperator tDifferentiator(gParms.mHistoryFilterParms2);

   // Apply the operator on the history to produce a new history. F:XS->Y,DY.
   tDifferentiator.operate(tHistoryXS,tHistoryY,tHistoryDY);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistoryX);
   tStatistics.show();

   tStatistics.collectValue(tHistoryXS);
   tStatistics.show();

   tStatistics.collectValue(tHistoryDY);
   tStatistics.show();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistory(tHistoryX,tHistoryXS,tHistoryDY);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "DemoOne::doDemo1 %d",tHistoryX.mMaxSamples);
}

