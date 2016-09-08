#ifndef _SETTINGS_H_
#define _SETTINGS_H_
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
// ProtoCommSettings class, inherits from BaseCmdLineExec to process
// command lines from a command line file.
// Each application reads its own print settings from a common settings
// file. 

class Settings : public Ris::BaseCmdLineExec
{
public:

   //---------------------------------------------------------------------------
   // Settings members.

   double  mDuration;     // Trial duration
   double  mFs;           // Sampling frequency
   double  mFp;           // Carrier frequency 

   double  mOffset;       // Offset
   double  mAmplitude;    // amplitude
   double  mSigma;        // Sigma

   //---------------------------------------------------------------------------
   // Infrastucture. Constructor and such

   typedef Ris::BaseCmdLineExec BaseClass;
   Settings();
   void show();

   // Baseclass override, executes for each line in the settings
   // command line file

   void execute(Ris::CmdLineCmd* aCmd);

   // Initialize.
   // aSettingsFileName is the settings filename. aSection is the settings
   // file section that each application extracts its settings from. 
   // aSectionMode specifies the section mode. Each section begins with a 
   // command line, such as "Begin CmdFile Default", where "Begin" is the 
   // command ,"CmdFile" is  first argument and denotes the section and
   // "Default" is the second argument and denotes the section mode.

   bool initialize(char* aSection);

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Section

   char mSection[200];
   char mSectionMode[200];

   bool isMySection(Ris::CmdLineCmd* aCmd);
   bool mSectionFlag;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global instance

#ifdef _SETTINGS_CPP_
        Settings gSettings;
#else
        extern Settings gSettings;
#endif

#endif

