#ifndef _DSPFRONTEND_H_
#define _DSPFRONTEND_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "risTextFile.h"
#include "dspPulseDetector.h"

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class FrontEnd
{
public:
   FrontEnd();
   void initialize();

   // Detector
   PulseDetector mPulseDetector;

   // Input and output files
   Ris::CsvFileReader mSampleReader;
   Ris::CsvFileWriter mPdwWriter;

   // Read from sample file, detect pulses, write to pdw file
   void detect1();

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
