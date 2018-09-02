/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dsp_math.h"
#include "dsp_functions.h"
#include "dspHistoryTextFile.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a history to a csv file.

void HistoryCsvFileWriter::writeHistory(
   History& aHistory)
{
   // Loop through all of the samples in the history.
   for (int k = 0; k < aHistory.mNumSamples; k++)
   {
      // Write the sample to the csv file
      writeRow(
         k,
         aHistory.mTime[k],
         aHistory.mValue[k]);
   }
}

void HistoryCsvFileWriter::writeHistoryDeg(
   History& aHistory)
{
   // Loop through all of the samples in the history.
   for (int k = 0; k < aHistory.mNumSamples; k++)
   {
      // Write the sample to the csv file
      writeRow(
         k,
         aHistory.mTime[k],
         deg(aHistory.mValue[k]));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a history to a csv file.

void HistoryCsvFileWriter::writeHistory(
   History& aHistory1,
   History& aHistory2)
{
   int tMaxSamples = dsp_imin(
      aHistory1.mNumSamples,
      aHistory2.mNumSamples);

   // Loop through all of the samples in the history.
   for (int k = 0; k < tMaxSamples; k++)
   {
      // Write the sample to the csv file
      writeRow(
         k,
         aHistory1.mTime[k],
         aHistory1.mValue[k],
         aHistory2.mValue[k]);
   }
}

void HistoryCsvFileWriter::writeHistoryDeg(
   History& aHistory1,
   History& aHistory2)
{
   int tMaxSamples = dsp_imin(
      aHistory1.mNumSamples,
      aHistory2.mNumSamples);

   // Loop through all of the samples in the history.
   for (int k = 0; k < tMaxSamples; k++)
   {
      // Write the sample to the csv file
      writeRow(
         k,
         aHistory1.mTime[k],
         deg(aHistory1.mValue[k]),
         deg(aHistory2.mValue[k]));
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Write a history to a csv file.

void HistoryCsvFileWriter::writeHistory(
   History& aHistory1,
   History& aHistory2,
   History& aHistory3)
{
   int tMaxSamples = dsp_imin(
      aHistory1.mNumSamples,
      aHistory2.mNumSamples);

   tMaxSamples = dsp_imin(
      tMaxSamples,
      aHistory3.mNumSamples);

   // Loop through all of the samples in the history.
   for (int k = 0; k < tMaxSamples; k++)
   {
      // Write the sample to the csv file
      writeRow(
         k,
         aHistory1.mTime[k],
         aHistory1.mValue[k],
         aHistory2.mValue[k],
         aHistory3.mValue[k]);
   }
}

void HistoryCsvFileWriter::writeHistoryDeg(
   History& aHistory1,
   History& aHistory2,
   History& aHistory3)
{
   int tMaxSamples = dsp_imin(
      aHistory1.mNumSamples,
      aHistory2.mNumSamples);

   tMaxSamples = dsp_imin(
      tMaxSamples,
      aHistory3.mNumSamples);

   // Loop through all of the samples in the history.
   for (int k = 0; k < tMaxSamples; k++)
   {
      // Write the sample to the csv file
      writeRow(
         k,
         aHistory1.mTime[k],
         deg(aHistory1.mValue[k]),
         deg(aHistory2.mValue[k]),
         deg(aHistory3.mValue[k]));
   }
}

}//namespace