#pragma once

#include "risCmdLineExec.h"
#include "dspFIRSavGol.h"

//******************************************************************************
// specific command line executive
//******************************************************************************

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

   Dsp::FIRSavGol<float, 9, 34> mCDiff;

   CmdLineExec();

   void reset();
   void execute(Ris::CmdLineCmd* aCmd);

   void executeGo1(Ris::CmdLineCmd* aCmd);
   void executeGo2(Ris::CmdLineCmd* aCmd);
   void executeGo3(Ris::CmdLineCmd* aCmd);
   void executeGo4(Ris::CmdLineCmd* aCmd);
   void executeGo5(Ris::CmdLineCmd* aCmd);

   void executeAlpha   (Ris::CmdLineCmd* aCmd);
   void executeCDiff   (Ris::CmdLineCmd* aCmd);

   void executeTest1   (Ris::CmdLineCmd* aCmd);
   void executeTest2   (Ris::CmdLineCmd* aCmd);
   void executeTest3   (Ris::CmdLineCmd* aCmd);

   void executePlotA   (Ris::CmdLineCmd* aCmd);
   void executeParms   (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************

