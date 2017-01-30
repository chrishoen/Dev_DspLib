#pragma once

/*==============================================================================
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
// This class encapsulates parameters for the class that follows in this file.
// it inherits from BaseCmdLineExec so that it can process commands from a
// nested command file to set its parameters.

class HistoryGenTimeParms : public Ris::BaseCmdLineExec
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members. These are read in from a parms file.

   double  mDuration;     // History duration
   double  mFs;           // Sampling frequency
   double  mTm;           // Geometric distribution parameter

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Expanded members that are not read from the parms file.

   double  mTs;           // Sampling period
   int     mNumSamples;   // Number of samples in array

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Constructor and parameter initialization.

   // Constructor.
   HistoryGenTimeParms();
   void reset();

   // Execute a command line in the section of the command file that is specific
   // to this object and set member variables accordingly. When an "End" is
   // encountered, pop back out of the section and return control to the parent
   // executive.
   void execute(Ris::CmdLineCmd* aCmd) override;

   // Calculate expanded member variables. This is called after the entire
   // section of the command file has been processed.
   void expand();

   // Show.
   void show(char* aLabel);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a base class for signal history generators.

class HistoryGenTime
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Input parameters.

   HistoryGenTimeParms mParms;

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Methods.

   // Constructor.
   HistoryGenTime(HistoryGenTimeParms& aParms);
   void show();

   // Initialize member variables. Initialize the history memory for the correct
   // number of samples. Set the history value array to zero and the time array
   // to linearly increasing.
   void initializeLinearTime(History& aHistory);

   // Initialize member variables. Initialize the history memory for the correct
   // number of samples. Set the history value array to zero and the time array
   // to linearly increasing.
   void initializeRandomTime(History& aHistory);

};

//******************************************************************************
}//namespace


