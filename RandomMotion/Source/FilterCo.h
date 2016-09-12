#ifndef _FILTERCO_H_
#define _FILTERCO_H_
/*==============================================================================

This file contains settings for filter coefficients. 

==============================================================================*/

//**********************************************************************
//**********************************************************************
//**********************************************************************

#include "risCmdLineTables.h"
#include "risCmdLineFile.h"

//**********************************************************************
//**********************************************************************
//**********************************************************************
// ProtoCommFilterCo class, inherits from BaseCmdLineExec to process
// command lines from a command line file.
// Each application reads its own print settings from a common settings
// file. 

class FilterCo : public Ris::BaseCmdLineExec
{
public:

   //---------------------------------------------------------------------------
   // Filter coefficients tables.

   Ris::CmdLineDoubleTable1D  mBandPassB1;
   Ris::CmdLineDoubleTable1D  mBandPassA1;

   //---------------------------------------------------------------------------
   // Infrastucture. Constructor and such

   typedef Ris::BaseCmdLineExec BaseClass;
   FilterCo();
   void reset();
   void show();

   // Initialize.
   // aFilterCoFileName is the settings filename. aSection is the settings
   // file section that each application extracts its settings from. 
   // aSectionMode specifies the section mode. Each section begins with a 
   // command line, such as "Begin CmdFile Default", where "Begin" is the 
   // command ,"CmdFile" is  first argument and denotes the section and
   // "Default" is the second argument and denotes the section mode.

   bool readSection(char* aSection);

   // Baseclass override, executes for each line in the settings
   // command line file

   void execute(Ris::CmdLineCmd* aCmd);

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
        FilterCo gFilterCo;
#else
        extern FilterCo gFilterCo;
#endif

#endif

