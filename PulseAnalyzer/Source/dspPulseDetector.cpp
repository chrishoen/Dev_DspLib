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
   mDetectPdw.reset();

   mDetectYesThreshold = 0.10;
   mDetectNoThreshold = 0.10;
   mSampleDeltaTime = 0.0001;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void PulseDetector::putSample(Sample* aSample)
{
   // Initially no detection for this sample false
   // If there is a detection, this will get set in what follows.

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
            startSampleStatistics(aSample->mAmplitude);
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
            updateSampleStatistics(aSample->mAmplitude);
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
            updateSampleStatistics(aSample->mAmplitude);
         }
         // If the amplitude is not above the threshold then maybe the end of 
         // a pulse has been detected.
         else
         {
            // Detection logic
            mDetectCount = 1;
            mDetectState = cDetectMaybeNo;
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
               mDetectPdw.mSeqNum++;
               mDetectPdw.mToa        = mPulseStartTime;
               mDetectPdw.mAmplitude  = mPulseAmplitudeMean;
               mDetectPdw.mPulseWidth = mPulseEndTime - mPulseStartTime + mSampleDeltaTime;
               mDetectFlag = true;

#if 1
               Prn::print(0, "DETECT %d %d %10.4f %10.4f",
                  mDetectPdw.mSeqNum,
                  mPulseSampleCount,
                  mPulseStartTime,
                  mPulseEndTime);
#endif
            }
         }
         // If the amplitude is above the threshold then the end of pulse
         // has not been detected.
         else
         {
            mDetectState = cDetectYes;

            // Store the pulse end time.
            mPulseEndTime = aSample->mTime;

            // Update the sample statistics.
            updateSampleStatistics(aSample->mAmplitude);
         }
      }
      break;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************
void PulseDetector::startSampleStatistics  (double aAmplitude)
{
   mPulseAmplitudeSum = aAmplitude;
   mPulseSampleCount  = 1;
}

void PulseDetector::updateSampleStatistics(double aAmplitude)
{
   mPulseAmplitudeSum += aAmplitude;
   mPulseSampleCount++;
}
void PulseDetector::finishSampleStatistics()
{
   mPulseAmplitudeMean = mPulseAmplitudeSum/mPulseSampleCount;
}

}//namespace