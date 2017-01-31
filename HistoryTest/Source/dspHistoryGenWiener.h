#ifndef _DSPHISTORYGENWIENER_H_
#define _DSPHISTORYGENWIENER_H_

/*==============================================================================
Signal history generator with a wiener process.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"

#include "dspHistoryGenBaseGN.h"
#include "dspFilterButterworth.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates parameters for the class that follows in this file.
// it inherits from BaseCmdLineExec so that it can process commands from a
// nested command file to set its parameters.

class HistoryGenWienerParms : public Ris::BaseCmdLineExec
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
   HistoryGenWienerParms();
   void reset();

   // Execute a command line in the section of the command file that is specific
   // to this object and set member variables accordingly. When an "End" is
   // encountered, pop back out of the section and return control to the parent
   // executive.
   void execute(Ris::CmdLineCmd* aCmd);

   // Show.
   void show(char* aLabel);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a generator for a signal history that evolves according
// to an integrated wiener process. The signal history is implemented by low
// pass filtering gaussian noise with a butterworth filter with a specified
// cutoff frequency. The history is then normalized to have a specified
// expectation and uncertainty.
 
class HistoryGenWiener : public HistoryGenBaseGN
{
public:
   typedef HistoryGenBaseGN BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Input parameters.
   HistoryGenWienerParms mParms;

   // Low pass butterworth filter.
   Filter::ButterworthLP mFilter;

   //--------------------------------------------------------------------------
   // Constructor.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HistoryGenWiener();
   HistoryGenWiener(HistoryGenWienerParms aParms);
   void reset();
   void show();

   // Generate the signal history according to the parameters.
   void generateHistoryType1(History& aHistory);   
   void generateHistoryType2(History& aHistory);


};

//******************************************************************************
}//namespace

#endif

