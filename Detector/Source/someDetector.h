#ifndef _SOMEDETECTOR_H_
#define _SOMEDETECTOR_H_

/*==============================================================================
Frequency detector
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "dspFilterFilters.h"
#include "dspFilterStatistics.h"

namespace Some
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class  Detector
{
public:

   // Constructor
   Detector();

   // Initialize with filter constants
   void initialize();
   void show();

   // Put input to frequency detector
   void put(double aInput);

   // Outputs, mean and standard deviation
   double mEX;
   double mUX;
   int    mK;

   // Bandpass filter centered at 4 hz with Fs of 4096 hz.
   Dsp::Filter::IIRFilter       mBandpassFilter;

   // Alpha statistics on abs of bandpass filter output. 
   // Step response of 10 seconds with Fs of 4096 hz.
   Dsp::Filter::AlphaStatistics mAlphaStats;

   // Unit test
   void test(double aF);

};

//******************************************************************************
// Global instance

#ifdef _SOMEDETECTOR_CPP_
Detector gDetector;
#else
extern Detector gDetector;
#endif

//******************************************************************************
}//namespace


#endif

