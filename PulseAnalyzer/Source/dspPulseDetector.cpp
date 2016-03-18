/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include "prnPrint.h"

#include "dspPulseDetector.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

PulseDetector::PulseDetector()
{
   initialize();
}

void PulseDetector::initialize()
{
   mDetectState = 0;
   mDetectFlag = false;
   mDetectedPdw.reset();

   mDetectYesThreshold = 0.01;
   mDetectNoThreshold = 0.01;
   mSamplePeriod = 0.0001;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void PulseDetector::putSample(Sample* aSample)
{
   // Initially no detection for this sample. If there is a detection, this 
   // will get set in what follows.

   mDetectFlag = false;

   // Implement a state machine on the detection state. The amplitude is tested
   // against thresholds to change the state. If a pulse is detected then the
   // pdw member variable and flag are set. This also calculates intrapulse
   // sample statistics that are recorded in the pdw.

   switch (mDetectState)
   {
      //------------------------------------------------------------------------
      // The start of a pulse has not been detected.

      case cDetectNo:
      {
         // If the amplitude is above the threshold
         if (aSample->mAmplitude >= mDetectYesThreshold)
         {
            // Maybe the start of a pulse has been detected.
            mDetectCount = 1;
            mDetectState = cDetectMaybeYes;

            // Store the start time.
            mPulseStartTime = aSample->mTime;

            // Start new sample statistics.
            startSampleYesStatistics(aSample->mAmplitude);
         }
         // If the amplitude is not above the threshold
         else
         {
            // No change
         }
      }
      break;

      //------------------------------------------------------------------------
      // Maybe the start of a pulse has been detected.

      case cDetectMaybeYes:
      {
         // If the amplitude is above the threshold
         if (aSample->mAmplitude >= mDetectYesThreshold)
         {
            // If the amplitude has been above the threshold for the last 
            // three samples then the start of a pulse has been detected.
            if (++mDetectCount == cDetectCountYesLimit)
            {
               mDetectState = cDetectYes;
            }

            // Update the sample statistics.
            updateSampleYesStatistics(aSample->mAmplitude);
         }
         // If the amplitude is not above the threshold then the start of
         // a pulse has not been detected.
         else
         {
            mDetectState = cDetectNo;
         }
      }
      break;

      //------------------------------------------------------------------------
      // The start of a pulse has been detected but the end of the pulse
      // has not been detected.

      case cDetectYes:
      {
         // If the amplitude is above the threshold
         if (aSample->mAmplitude >= mDetectNoThreshold)
         {
            // Store the pulse end time.
            mPulseEndTime = aSample->mTime;

            // Update the sample statistics.
            updateSampleYesStatistics(aSample->mAmplitude);
         }
         // If the amplitude is not above the threshold then maybe the end of 
         // a pulse has been detected.
         else
         {
            // Detection logic
            mDetectCount = 1;
            mDetectState = cDetectMaybeNo;

            // Start new sample statistics.
            startSampleMaybeNoStatistics(aSample->mAmplitude);
         }
      }
      break;

      //------------------------------------------------------------------------
      // Maybe the end of a pulse has been detected.

      case cDetectMaybeNo:
      {
         // If the amplitude is not above the threshold
         if (aSample->mAmplitude < mDetectNoThreshold)
         {
            // If the amplitude has not been above the threshold for the last 
            // three samples then the end of a pulse has been detected.
            if (++mDetectCount == cDetectCountNoLimit)
            {
               mDetectState = cDetectNo;

               // Finish the sample statistics.
               finishSampleStatistics();

               // Update values for the detected pdw.
               mDetectedPdw.mSeqNum++;
               mDetectedPdw.mToa        = mPulseStartTime;
               mDetectedPdw.mAmplitude  = mPulseAmplitudeMean;
               mDetectedPdw.mPulseWidth = mPulseEndTime - mPulseStartTime + mSamplePeriod;
               mDetectFlag = true;
            }
            // If the amplitude has not been above the threshold for less than
            // the last three samples then the end of a pulse has not been
            // detected yet.
            else
            {
               // Update the sample statistics.
               updateSampleMaybeNoStatistics(aSample->mAmplitude);
            }
         }
         // If the amplitude is above the threshold then the end of pulse
         // has not been detected.
         else
         {
            mDetectState = cDetectYes;

            // Store the pulse end time.
            mPulseEndTime = aSample->mTime;

            // Merge the sample statistics for the two states.
            mergeSampleMaybeNoStatistics();
            // Update the sample statistics.
            updateSampleYesStatistics(aSample->mAmplitude);
         }
      }
      break;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void PulseDetector::startSampleYesStatistics  (double aAmplitude)
{
   mPulseAmplitudeYesSum = aAmplitude;
   mPulseSampleYesCount  = 1;
}

void PulseDetector::updateSampleYesStatistics(double aAmplitude)
{
   mPulseAmplitudeYesSum += aAmplitude;
   mPulseSampleYesCount++;
}

void PulseDetector::startSampleMaybeNoStatistics  (double aAmplitude)
{
   mPulseAmplitudeMaybeNoSum = aAmplitude;
   mPulseSampleMaybeNoCount  = 1;
}

void PulseDetector::updateSampleMaybeNoStatistics(double aAmplitude)
{
   mPulseAmplitudeMaybeNoSum += aAmplitude;
   mPulseSampleMaybeNoCount++;
}

void PulseDetector::mergeSampleMaybeNoStatistics()
{
   mPulseAmplitudeYesSum += mPulseAmplitudeMaybeNoSum;
   mPulseSampleYesCount  += mPulseSampleMaybeNoCount;
}

void PulseDetector::finishSampleStatistics()
{
   mPulseAmplitudeMean = mPulseAmplitudeYesSum/mPulseSampleYesCount;
}

}//namespace