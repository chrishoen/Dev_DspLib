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
#include "TestOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun3()
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
   // Generate a signal history.

   // Signal history.
   History tHistoryY;

   // Signal history generator.
   HistoryFilterOperator tFilterXY(gParms.mHistoryFilterParms1);

   // Apply the operator on the history to produce a new history. F:X->Y.
   tFilterXY.operate(tHistoryX,tHistoryY);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistoryZ;

   // Signal history generator.
   HistoryFilterOperator tFilterYZ(gParms.mHistoryFilterParms2);

   // Apply the operator on the history to produce a new history. F:Y->Z.
   tFilterYZ.operate(tHistoryY,tHistoryZ);

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

   tStatistics.collectValue(tHistoryZ);
   tStatistics.show(0,"Z   ");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistory(
      tHistoryX,
      tHistoryY,
      tHistoryZ);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "TestOne::doRun3 %d",tHistoryX.mMaxSamples);
}

