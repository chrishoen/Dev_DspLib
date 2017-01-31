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

#include "dspSample.h"
#include "dspTextFile.h"
#include "dspStatistics.h"
#include "dspTimeSeriesTime.h"
#include "dspTimeSeriesLPGN.h"
#include "dspHistory.h"
#include "dspHistoryOps.h"
#include "dspHistoryGenWiener.h"
#include "dspHistoryStatistics.h"
#include "dspHistoryLoopClock.h"
#include "dspHistoryGenTime.h"

#include "Parms.h"
#include "TestOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun4()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistory;

   // Signal history generator.
   HistoryGenTime tGen(gParms.mHistoryGenTime);

   // Generate the history.
   tGen.initializeRandomTime(tHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   CsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);


   // Loop through all of the samples in the history.
   for (int k = 0; k < tHistory.mNumSamples; k++)
   {
      int    tIndex = k;
      double tTime  = tHistory.mTime[k];
      double tValue = 0.0;

      // Write the sample to the output file.
      tSampleWriter.writeRow(
         tIndex,
         tTime,
         tValue);
   }

   // Close the output file.
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "TestOne::doRun4 %d",tHistory.mNumSamples);
}

