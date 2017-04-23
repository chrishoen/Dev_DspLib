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
#include "dspHistoryConverters.h"

#include "Parms.h"
#include "DemoOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void DemoOne::doDemo3()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistoryX_Type2;

   // Signal history generator.
   HistoryGenerator tGen(gParms.mHistoryGenParms);

   // Generate the history.
   tGen.generateHistory(tHistoryX_Type2);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history, converted

   // Signal history.
   History tHistoryX_Type1;

   // Signal history generator.
   convertHistoryFromType2ToType1(
      tHistoryX_Type2,
      gParms.mHistoryGenParms.mFs,
      tHistoryX_Type1);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Filter the signal history. Smoother.

   // Signal history.
   History tHistoryXS;

   // Signal history filter.
   HistoryFilterOperator tSmoother(gParms.mHistoryFilterParms1);

   // Apply the operator on the history to produce a new history. F:X->XS.
   tSmoother.operate(tHistoryX_Type1,tHistoryXS);

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
   tStatistics.collectValue(tHistoryX_Type2);
   tStatistics.show(0,"X_Type2");

   tStatistics.collectValue(tHistoryX_Type1);
   tStatistics.show(0,"X_Type1");

   tStatistics.collectValue(tHistoryXS);
   tStatistics.show(0,"XS");

   tStatistics.collectValue(tHistoryDY);
   tStatistics.show(0,"DY");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;

   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistory(tHistoryX_Type2,tHistoryX_Type1);
   tSampleWriter.close();

   tSampleWriter.open(gParms.mOutputFile2);
   tSampleWriter.writeHistory(tHistoryX_Type2,tHistoryXS,tHistoryDY);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "DemoOne::doDemo3 %d %d",tHistoryX_Type2.mMaxSamples,tHistoryX_Type1.mMaxSamples);
}

