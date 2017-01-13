#ifndef _PARMS_H_
#define _PARMS_H_
/*==============================================================================

This file contains settings for parameter input. 

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineFile.h"
#include "dspHistoryGenWienerParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Parameters class, inherits from BaseCmdLineExec to process
// commands from a command line file to set parameters.

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
   // Extra Parms members that are not read from the parms file.

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

   // Read a section of the command line file. This only reads variables for a 
   // specific section.
   bool readSection(char* aSection);

   // Baseclass override, execute for each line in the settings
   // command line file to set a member variable. 
   void execute(Ris::CmdLineCmd* aCmd);

   // Calculate expanded member variables.
   void expand();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Section

   char mSection[200];
   char mSectionMode[200];
   bool mSectionFlag;
   bool mDefaultSection;

   bool isMySection(Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _PARMS_CPP_
        Parms gParms;
#else
        extern Parms gParms;
#endif

#endif

