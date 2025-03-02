/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dsp_math.h"
#include "dsp_functions.h"
#include "dspHistoryCsvFileReader.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read a csv file to get the number of rows in the file.

int HistoryCsvFileReader::getNumRows()
{
   int tNumRows=0;
   // Read all of rows.
   while (1)
   {
      if (fgets(mString, cMaxStringSize, mFile) == NULL) break;
      tNumRows++;
   }
   // Go back to the beginning of the file.
   fseek(mFile, 0, SEEK_SET);
   // Done.
   return tNumRows;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read history from a csv file column, auto generate the time.

void HistoryCsvFileReader::readHistory(
   double aDT,
   int aSampleColIndex,
   History& aHistory)
{
   // Read from the csv file to get the number of rows.
   int tNumRows = getNumRows();

   // Initialize the history for the number of rows.
   aHistory.initialize(tNumRows);

   // Read from the csv file and write the sample to the history.
   // Supply the time.
   double tTime = 0;
   aHistory.startWrite();
   // Loop for all of the rows in the csv file.
   for (int i=0; i<tNumRows; i++)
   {
      // Read a row from the csv file.
      readRow();
      // Write a row sample to the history, supply the time.
      aHistory.writeSample(tTime, e(aSampleColIndex));
      tTime += aDT; 
   }
   // Done.
   aHistory.finishWrite();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read history from a csv file time column and a sample column.

void HistoryCsvFileReader::readHistory2(
   int aTimeColIndex,
   int aSampleColIndex,
   History& aHistory)
{
   // Read from the csv file to get the number of rows.
   int tNumRows = getNumRows();

   // Initialize the history for the number of rows.
   aHistory.initialize(tNumRows);

   // Read from the csv file and write the value to the history.
   aHistory.startWrite();
   // Loop for all of the rows in the csv file.
   for (int i=0; i<tNumRows; i++)
   {
      // Read a row from the csv file.
      readRow();
      // Write a row time and sample to the history.
      aHistory.writeSample(e(aTimeColIndex), e(aSampleColIndex));
   }
   // Done.
   aHistory.finishWrite();
}
      


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace