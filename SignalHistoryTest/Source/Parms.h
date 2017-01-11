#ifndef _PARMS_H_
#define _PARMS_H_
/*==============================================================================

This file contains settings for parameter input. 

==============================================================================*/

//**********************************************************************
//**********************************************************************
//**********************************************************************

#include "risCmdLineFile.h"

//**********************************************************************
//**********************************************************************
//**********************************************************************
// ProtoCommParms class, inherits from BaseCmdLineExec to process
// command lines from a command line file.
// Each application reads its own print settings from a common settings
// file. 

class Parms : public Ris::BaseCmdLineExec
{
public:

   //---------------------------------------------------------------------------
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

   //---------------------------------------------------------------------------
   // Signal histories.

   int mHistoryMaxSamples;
      
   //---------------------------------------------------------------------------
   // Extra Parms members that are not read from the parms file.

   double  mTs;           // Sampling period
   int     mNumSamples;   // Number of samples in array

   //---------------------------------------------------------------------------
   // Infrastucture. Constructor and such

   typedef Ris::BaseCmdLineExec BaseClass;
   Parms();
   void reset();
   void show();

   // Initialize.
   // aParmsFileName is the settings filename. aSection is the settings
   // file section that each application extracts its settings from. 
   // aSectionMode specifies the section mode. Each section begins with a 
   // command line, such as "Begin CmdFile Default", where "Begin" is the 
   // command ,"CmdFile" is  first argument and denotes the section and
   // "Default" is the second argument and denotes the section mode.

   bool readSection(char* aSection);

   // Baseclass override, executes for each line in the settings
   // command line file

   void execute(Ris::CmdLineCmd* aCmd);

   // Calculate expanded parms.
   void expand();

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

