#pragma once

/*==============================================================================
Write a signal history to a csv file.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "dspTextFile.h"
#include "dspHistory.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class HistoryCsvFileWriter : public CsvFileWriter
{
public:

   // Write history to a csv file.
   void writeHistory(
      History& aHistory);

   // Write history to a csv file.
   void writeHistory(
      History& aHistory1,
      History& aHistory2);

   // Write history to a csv file.
   void writeHistory(
      History& aHistory1,
      History& aHistory2,
      History& aHistory3);
};

//******************************************************************************
}//namespace


