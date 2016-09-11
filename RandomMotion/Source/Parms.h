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
   // Parms members that are read from the parms file.

   double  mDuration;     // Trial duration
   double  mFs;           // Sampling frequency
   double  mFp;           // Carrier frequency 

   double  mEX;           // Desired expectation
   double  mUX;           // Desired uncertainty

   double  mFc1;          // Carrier frequency 
   double  mFc2;          // Carrier frequency 
   double  mAc1;          // Carrier amplitude 
   double  mAc2;          // Carrier amplitude 
   double  mPc1;          // Carrier phase 
   double  mPc2;          // Carrier phase 

   double  mFcRandom;     // Carrier frequency randomize
   double  mAcRandom;     // Carrier amplitude randomize
   double  mPcRandom;     // Carrier phase randomize

   static const int cMaxStringSize=400;
   char mOutputFile [cMaxStringSize];

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

   bool isMySection(Ris::CmdLineCmd* aCmd);
   bool mSectionFlag;
   bool mDefaultSection;
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

