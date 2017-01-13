#ifndef _DSPHISTORYGENWIENER_H_
#define _DSPHISTORYGENWIENER_H_

/*==============================================================================
Signal history generator for a wiener process.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "risCmdLineFile.h"
#include "dspHistory.h"


namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a generator for a signal history that evolves
// according to an integrated wiener process. The signal history is
// implemented by low pass filtering gaussian noise with a butterworth filter
// with a specified cutoff frequency. The history is then normalized to have
// a specified expectation and uncertainty.
// 
// The class inherits from BaseCmdLineExec so that it can process command lines
// from a nested command line file to set its parameters.


class HistoryGenWiener : public Ris::BaseCmdLineExec
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   double  mDuration;     // History duration
   double  mFs;           // Sampling frequency
   double  mFc;           // Cutoff frequency 
   int     mFilterOrder;  // Filter order

   double  mEX;           // Desired expectation
   double  mUX;           // Desired uncertainty

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Constructor and parameter initialization.

   // Constructor.
   HistoryGenWiener();
   void reset();

   // Execute a command line in the section of the parms file that is specific
   // to this object and set member variables accordingly. When an "End" is
   // encountered, pop back out of the section and return control to its parent
   // executive.
   void execute(Ris::CmdLineCmd* aCmd);

   // Show.
   void show();

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Generate the signal history according to the parameters.

   void generate(History& aHistory);

};

//******************************************************************************
}//namespace

#endif

