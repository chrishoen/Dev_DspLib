#ifndef _DSPFRONTEND_H_
#define _DSPFRONTEND_H_

/*==============================================================================
Pulse Analyzer Front End
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "dspTextFile.h"
#include "dspPdwTextFile.h"
#include "dspPulseDetector.h"
#include "dspPulseList.h"
#include "dspPulseStatistics.h"

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Pulse Analyzer Front End Parameters.

class FrontEndParms
{
public:

   //--------------------------------------------------------------------------
   // Parameters

   double  mFs;           // Sampling frequency
   double  mTs;           // Sampling period
   double  mDuration;     // Time duration of signal
   int     mNumSamples;   // Number of samples in array

   double mDetectYesThreshold;
   double mDetectNoThreshold;

   int    mListMaxNumOfElements;
   double mListWindowTimeSize;

   //--------------------------------------------------------------------------
   // File names

   static const int cMaxStringSize=400;

   char mInputFileName  [cMaxStringSize];
   char mOutputFileName [cMaxStringSize];

   void setInputFileName  (char* aFileName);
   void setOutputFileName (char* aFileName);
   
   //--------------------------------------------------------------------------
   // Constructors

   FrontEndParms();
   void reset();
   void initialize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Pulse analyzer front end. This uses the pulse detector, pulse list,
// and pulse statistics to test them out. It is a prototype for a pulse
// analyzer class.

class FrontEnd
{
public:
   FrontEnd();
   void initialize();

   // Pulse analyzer components
   PulseDetector    mPulseDetector;
   PulseList        mPulseList;
   PulseStatistics  mPulseStatistics;

   // Read from sample file, detect pulses, write to pdw file
   void detect1  (FrontEndParms* aParms);

   // Read from pdw file, analyze, write to sample file
   void analyze11(FrontEndParms* aParms);
   void analyze12(FrontEndParms* aParms);
   // Read from sample file, analyze, write to sample file
   void analyze2 (FrontEndParms* aParms);

};

//******************************************************************************
// Global instance

#ifdef _DSPFRONTEND_CPP_
          FrontEnd gFrontEnd;
#else
   extern FrontEnd gFrontEnd;
#endif

//******************************************************************************
}//namespace

#endif
