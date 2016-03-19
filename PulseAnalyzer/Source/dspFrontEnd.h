#ifndef _DSPFRONTEND_H_
#define _DSPFRONTEND_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "risTextFile.h"
#include "dspPulseDetector.h"
#include "dspPulseList.h"
#include "dspPulseStatistics.h"

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class FrontEndParms
{
public:

   //--------------------------------------------------------------------------
   // Members

   static const int cMaxStringSize=400;

   char mInputFileName  [cMaxStringSize];
   char mOutputFileName [cMaxStringSize];

   void setInputFileName  (char* aFileName);
   void setOutputFileName (char* aFileName);
   
   double mDetectYesThreshold;
   double mDetectNoThreshold;
   double mSamplePeriod;

   int    mListMaxNumOfElements;
   double mListWindowTimeSize;

   //--------------------------------------------------------------------------
   // Constructors

   FrontEndParms();
   void reset();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

class FrontEnd
{
public:
   FrontEnd();
   void initialize();

   // Pulse analyzer components
   PulseDetector    mPulseDetector;
   PulseList        mPulseList;
   PulseStatistics  mPulseStatistics;

   // Input and output files
   Ris::CsvFileReader mFileReader;
   Ris::CsvFileWriter mFileWriter;

   // Read from sample file, detect pulses, write to pdw file
   void detect1  (FrontEndParms* aParms);

   // Read from sample file, analyze, write to sample file
   void analyze1 (FrontEndParms* aParms);

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
