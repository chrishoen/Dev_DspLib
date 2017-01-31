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

void TestOne::doRun5()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history. Periodic wiener wave.

   // Signal history.
   History tHistory1;

   // Signal history generator.
   HistoryGenWiener tGen1(gParms.mHistoryGenWiener);

   // Generate the history.
   tGen1.generateHistoryType1(tHistory1);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history. Random time.

   // Signal history.
   History tHistory2;

   // Signal history generator.
   HistoryGenTime tGen2(gParms.mHistoryGenTime);

   // Generate the history.
   tGen2.initializeRandomTime(tHistory2);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   CsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);

   tHistory2.startRead();
   
   // Loop through all of the samples in the history.
   for (int k = 0; k < tHistory2.mNumSamples; k++)
   {
      int    tIndex = k;
      double tTime  = tHistory2.mTime[k];
      double tValue = tHistory1.readValueAtTime(tTime);

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

   Prn::print(0, "TestOne::doRun5 %d",tHistory2.mNumSamples);
}

