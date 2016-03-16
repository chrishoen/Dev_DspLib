#ifndef _DSPPULSEDETECTOR_H_
#define _DSPPULSEDETECTOR_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspPdw.h"

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

   // Initialize detection logic.
   void initialize();

   // Put new a sample to the detector, called at the sampling rate.
   // Detection results are contained in the following two variables.
   void putSample(int aTime,double aAmplitude);

   // This is true if a pulse was detected by the last call to PutSample.
   bool mDetectFlag;

   // This is the Pdw for the last detected pulse.
   Pdw  mDetectPdw;

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

   //---------------------------------------------------------------------------
   // Intrapulse sample variables

   int    mPulseStartTime;
   int    mPulseEndTime;
   double mPulseAmplitudeSum;
   double mPulseAmplitudeMean;
   int    mPulseSampleCount;

   void startSampleStatistics  (double aAmplitude);
   void updateSampleStatistics (double aAmplitude);
   void finishSampleStatistics ();


};

//******************************************************************************
}//namespace

#endif

