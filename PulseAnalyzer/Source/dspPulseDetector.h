#ifndef _DSPPULSEDETECTOR_H_
#define _DSPPULSEDETECTOR_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspPdw.h"
#include "dspSample.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

   class PulseDetector
{
public:
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Interface

   // Constructor.
   PulseDetector();

   // Initialize the detection logic.
   void initialize();

   // Put a new sample to the detector, called at the sampling rate.
   // Detection results are contained in the following two variables.
   void putSample(Sample* aSample);

   // This is true if a pulse was detected by the last call to PutSample.
   bool mDetectFlag;

   // This is the Pdw for the last detected pulse.
   Pdw  mDetectedPdw;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Members

   //---------------------------------------------------------------------------
   // Detection state

   static const int cDetectNo       = 0;
   static const int cDetectMaybeYes = 1;
   static const int cDetectYes      = 2;
   static const int cDetectMaybeNo  = 3;

   int mDetectState;

   static const int cDetectCountYesLimit  = 3;
   static const int cDetectCountNoLimit   = 3;

   int mDetectCount;

   //---------------------------------------------------------------------------
   // Detection thresholds

   double mDetectYesThreshold;
   double mDetectNoThreshold;
   double mSamplePeriod;

   //---------------------------------------------------------------------------
   // Intrapulse sample variables

   // This is the time of the sample that causes a state change from No
   // to MaybeYes.
   double mPulseStartTime;

   // This is the time of the last sample for which the state was Yes.
   double mPulseEndTime;

   // This is the calculated mean amplitude.
   double mPulseAmplitudeMean;

   // Statistics for Yes state. These are started when the state changes from
   // No to MaybeYes and updated for states MaybeYes and Yes.
   int    mPulseSampleYesCount;
   double mPulseAmplitudeYesSum;

   void startSampleYesStatistics      (double aAmplitude);
   void updateSampleYesStatistics     (double aAmplitude);

   // Statistics for MaybeNo state. These are started when the state changes
   // from Yes to MaybeNo and updated for state MaybeNo. If the state changes
   // from MaybeNo back to Yes (a false alarm for end of pulse detection) then
   // the MaybeNo statistics are added to the Yes statistics.
   int    mPulseSampleMaybeNoCount;
   double mPulseAmplitudeMaybeNoSum;

   void startSampleMaybeNoStatistics  (double aAmplitude);
   void updateSampleMaybeNoStatistics (double aAmplitude);
   void mergeSampleMaybeNoStatistics ();

   // This calulates the means from the sums and counts. It is called when 
   // the state changes from MaybeNo to No and the end of a pulse is detected.
   void finishSampleStatistics ();
};

//******************************************************************************
}//namespace

#endif

