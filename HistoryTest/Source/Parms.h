#ifndef _PARMS_H_
#define _PARMS_H_
/*==============================================================================

Parameters class whose values are read from a command file. 

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineParms.h"
#include "dspHistoryGenWiener.h"
#include "dspHistoryGenTime.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that contains parameter member variables. The values of
// the parameters are set by reading a text file that contains command lines.
// Each command line is of the form "command argument1 argument2 ...".
// 
// The command files are partitioned into different sections and only one
// section can be read at a time to set member variables that are specified
// in it.
//
// The command files are managed by a CmdLineFile object. This opens the 
// file, reads each line in it, parses the line into a CmdLineCmd command 
// object, passes the command object to this object for command execution,
// and then closes the file. 
//
// This class inherits from BaseCmdLineParms, which inherits from 
// BaseCmdLineExec. BaseCmdLineParms provides a method that uses a
// CmdLineFile object to read and process the file. BaseCmdLineExec provides
// an abstract execute(cmd) method to which inheritors provide an overload
// that is called by the CmdLineFile object for each command in the file.
// This execute method then sets a member variables, according to the
// command.
// 
// This class can contain member variables that also inherit from
// BaseCmdLineExec. This provides for command files that have a nested
// structure. If so, then this class is the root.
// 

class Parms : public Ris::BaseCmdLineParms
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Integrity checks.

   int   mCode1;
   int   mCode2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Lowpass filtered gaussian noise time series.

   bool    mLockFlag;     // True if locked.
   double  mDuration;     // Trial duration
   double  mFs;           // Sampling frequency
   double  mFc;           // Cutoff frequency 
   double  mFc1;          // Cutoff frequency 
   double  mFc2;          // Cutoff frequency 
   int     mFilterOrder;  // Filter order

   double  mEX;           // Desired expectation
   double  mUX;           // Desired uncertainty

   static const int cMaxStringSize=400;
   char mOutputFile [cMaxStringSize];

   Dsp::HistoryGenWienerParms mHistoryGenWiener;
   Dsp::HistoryGenTimeParms   mHistoryGenTime;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Signal histories.

   int mHistoryMaxSamples;
   double mHistoryDeltaT;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Expanded members that are not read from the parms file.

   double  mTs;           // Sampling period
   int     mNumSamples;   // Number of samples in array

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastucture.

   // Constructor,
   typedef Ris::BaseCmdLineParms BaseClass;
   Parms();
   void reset();
   void show();

   // Base class override: Execute a command from the command file to set a 
   // member variable. This is called by the associated command file object
   // for each command in the file.
   void execute(Ris::CmdLineCmd* aCmd);

   // Calculate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance.

#ifdef _PARMS_CPP_
        Parms gParms;
#else
        extern Parms gParms;
#endif

#endif

