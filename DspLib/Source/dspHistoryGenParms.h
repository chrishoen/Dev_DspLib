#pragma once

/*==============================================================================

Parameters class whose values are read from a command file. 

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

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

class HistoryGenParms : public Ris::BaseCmdLineExec
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // Generator types.
   static const int cGenZero     = 1;
   static const int cGenStep     = 2;
   static const int cGenSinWave  = 3;
   static const int cGenRandWave = 4;

   // Sampling time types.
   static const int cTimeType1   = 1;
   static const int cTimeType2   = 2;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members that are read from the parms file.

   int     mGenType;      // History generator type.
   int     mTimeType;     // History sampling time type.

   double  mDuration;     // History duration.
   double  mFs;           // Sampling frequency.
   double  mFc;           // Filter cutoff frequency. 
   int     mFilterOrder;  // Filter order.

   bool    mAngleFlag;    // True if values are angles.

   double  mEX;           // Desired expectation.
   double  mUX;           // Desired uncertainty.

   double  mA;            // Sin wave amplitude.
   double  mPhi;          // Sin wave phase.

   double  mTp;           // Step transition time.

   double  mSigma;        // Additive gaussian noise.

   int     mFsDivisor;    // Undersampling frequency divisor.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Expanded members that are not read from the parms file.

   double  mTs;           // Sampling period
   int     mMaxSamples;   // Number of samples in array

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastucture.

   // Constructor,
   typedef Ris::BaseCmdLineExec BaseClass;
   HistoryGenParms();
   void reset();
   void show(char* aLabel);

   // Base class override: Execute a command from the command file to set a 
   // member variable. This is called by the associated command file object
   // for each command in the file.
   void execute(Ris::CmdLineCmd* aCmd);

   // Calculate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Helpers.

   static char* asStringGenType (int aGenType);
   static char* asStringTimeType(int aTimeType);

};

}//namespace