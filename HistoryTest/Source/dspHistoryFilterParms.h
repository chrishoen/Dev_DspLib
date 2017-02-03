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

class HistoryFilterParms : public Ris::BaseCmdLineExec
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   // Filter types.
   static const int cFilterIdentity    = 1;
   static const int cFilterSmoother    = 2;
   static const int cFilterFirstDeriv  = 3;
   static const int cFilterSecondDeriv = 4;
   static const int cFilterCausal      = 5;

   // Filter methods.
   static const int cMethodSavGol = 1;
   static const int cMethodHolob  = 2;

   // Causal filter types.
   static const int cCausalButterworthLP   = 1;
   static const int cCausalAlphaOne        = 2;
   static const int cCausalAlphaTwo        = 3;
   static const int cCausalAlphaThree      = 4;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members that are read from the parms file.

   int     mFilterType;     // Filter type.
   int     mFilterMethod;   // Filter structure type.

   int     mFilterOrder;    // Central difference filter order. Must be odd.
   double  mH;              // Central difference time delta. 

   int     mSelect;         // Selector, general purpose.

   int     mCausalType;     // Causal filter type.
   double  mFs;             // Causal filter Sampling frequency.
   double  mFc;             // Causal filter cutoff frequency. 

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Expanded members that are not read from the parms file.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infrastucture.

   // Constructor,
   typedef Ris::BaseCmdLineExec BaseClass;
   HistoryFilterParms();
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

   static char* asStringFilterType (int aX);
   static char* asStringFilterMethod (int aX);
   static char* asStringCausalType (int aX);

   char* asStringFilterType ();
   char* asStringFilterMethod ();
   char* asStringCausalType ();

};

}//namespace