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
#include "dspHistoryGenGen.h"

#include "Parms.h"
#include "TestOne.h"

using namespace Dsp;

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void my_test_function(History aX)
{
   aX.show("my_test_function");
}

void TestOne::doMem1()
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Generate a signal history.

   // Signal history.
   printf("Instantiate History1\n");
   History tHistory1;

   tHistory1.show("History1 first");

   // Signal history generator.
   HistoryGenGen tGen(gParms.mHistoryGenParms);

   // Generate the history.
   tGen.generateHistory(tHistory1);

   tHistory1.show("History1 second");


   printf("Instantiate History2\n");
   History tHistory2(tHistory1);

   printf("Intantiate History3\n");
   History tHistory3 = tHistory2;

   printf("Instantiate History4\n");
   History tHistory4;
   tHistory4 = tHistory3;

   printf("Call my_test_function\n");
   my_test_function(tHistory4);

   tHistory1.show("History1");
   tHistory2.show("History2");
   tHistory3.show("History3");
   tHistory4.show("History3");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Collect statistics on the history.

   // Statistics
   HistoryStatistics  tStatistics;
   tStatistics.collectValue(tHistory1);
   tStatistics.show();
   tStatistics.collectValue(tHistory2);
   tStatistics.show();
   tStatistics.collectValue(tHistory3);
   tStatistics.show();

   Prn::print(0, "TestOne::doMem1");
   return;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Loop to transfer the signal history to an output file.

   // Output file.
   HistoryCsvFileWriter  tSampleWriter;
   tSampleWriter.open(gParms.mOutputFile);
   tSampleWriter.writeHistory(tHistory1);
   tSampleWriter.close();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   Prn::print(0, "TestOne::doMem1 %d",tHistory1.mMaxSamples);
}

