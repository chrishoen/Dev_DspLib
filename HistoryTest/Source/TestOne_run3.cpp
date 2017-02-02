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
#include "dspHistoryOperGen.h"

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
   HistoryGenGen tGen(gParms.mHistoryGenParms);

   // Generate the history.
   tGen.generateHistory(tHistoryX);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistoryY;

   // Signal history generator.
   HistoryOperGen tOperXY(gParms.mHistoryOperParms1);

   // Apply the operator on the history to produce a new history. F:X->Y.
   tOperXY.operate(tHistoryX,tHistoryY);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistoryZ;

   // Signal history generator.
   HistoryOperGen tOperYZ(gParms.mHistoryOperParms2);

   // Apply the operator on the history to produce a new history. F:Y->Z.
   tOperYZ.operate(tHistoryY,tHistoryZ);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistoryX);
   tStatistics.show();

   tStatistics.collectValue(tHistoryY);
   tStatistics.show();

   tStatistics.collectValue(tHistoryZ);
   tStatistics.show();

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

