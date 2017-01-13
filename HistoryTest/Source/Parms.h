#ifndef _PARMS_H_
#define _PARMS_H_
/*==============================================================================

Parameters class whose values are read from a command file. 

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineFile.h"
#include "dspHistoryGenWiener.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class that contains parameter member variables. The values of the
// parameters are set by reading a text file that contains command lines. Each
// command line is of the form "command argument1 argument2 ...".
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
// This class inherits from BaseCmdLineExec. It provides an overload 
// execute(cmd) method that is called by the CmdLineFile object 
// for each command in the file. It then sets a member variables, according
// to the command.
// 
// This class can contain member variables that also inherit from
// BaseCmdLineExec. This provides for command files that have a nested
// structure. If so, then this class is the root.
// 

class Parms : public Ris::BaseCmdLineExec
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
   // Infrastucture. Constructor and such

   typedef Ris::BaseCmdLineExec BaseClass;
   Parms();
   void reset();
   void show();

   // Read a section of the command file and set member variables accordingly.
   // This only reads variables for a specific section in the file.
   bool readSection(char* aSection);

   // Base class override: Execute a command from the command file to set a 
   // member variable. This is called by an associated command file object
   // for each command in the file.
   void execute(Ris::CmdLineCmd* aCmd);

   // Calculate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Section varaibles.

   char mSection[200];
   char mSectionMode[200];
   bool mSectionFlag;
   bool mDefaultSection;

   bool isMySection(Ris::CmdLineCmd* aCmd);
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

