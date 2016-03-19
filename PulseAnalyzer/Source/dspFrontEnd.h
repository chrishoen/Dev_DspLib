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
   void detect1();

   // Read from sample file, analyze, write to sample file
   void analyze1();

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
