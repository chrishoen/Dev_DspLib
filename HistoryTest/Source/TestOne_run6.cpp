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
#include "dspHistory.h"
#include "dspHistoryOps.h"
#include "dspHistoryGenRandWave.h"
#include "dspHistoryStatistics.h"
#include "dspHistoryLoopClock.h"

#include "Parms.h"
#include "TestOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun6()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   History tHistory;

   // Signal history generator.
   HistoryGenRandWave tGen(gParms.mHistoryGenParms);

   // Generate the history.
   tGen.generateHistoryType2(tHistory);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistory);
   tStatistics.show();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   CsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);


   // Loop through all of the samples in the history.
   for (int k=0;k<tHistory.mNumSamples;k++)
   {
      // Read the sample from the history.
      int    tIndex = k;
      double tTime  = 0.0;
      double tValue = 0.0;
      tHistory.readSampleAtIndex(k,&tTime,&tValue);

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

   Prn::print(0, "TestOne::doRun6 %d",tHistory.mMaxSamples);
}

