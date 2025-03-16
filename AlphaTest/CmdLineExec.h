#pragma once

#include "risCmdLineExec.h"

//******************************************************************************
// specific command line executive
//******************************************************************************

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

   CmdLineExec();

   void reset();
   void execute(Ris::CmdLineCmd* aCmd);

   void executeGo1(Ris::CmdLineCmd* aCmd);
   void executeGo2(Ris::CmdLineCmd* aCmd);
   void executeGo3(Ris::CmdLineCmd* aCmd);
   void executeGo4(Ris::CmdLineCmd* aCmd);
   void executeGo5(Ris::CmdLineCmd* aCmd);

   void executeAlpha1          (Ris::CmdLineCmd* aCmd);
   void executeAlpha2          (Ris::CmdLineCmd* aCmd);
   void executeAlpha3          (Ris::CmdLineCmd* aCmd);
   void executeSlidingMean2  (Ris::CmdLineCmd* aCmd);
   void executeSlidingMean3  (Ris::CmdLineCmd* aCmd);

   void executeTest1   (Ris::CmdLineCmd* aCmd);
   void executeTest2   (Ris::CmdLineCmd* aCmd);
   void executeTest3   (Ris::CmdLineCmd* aCmd);

   void executePlotA   (Ris::CmdLineCmd* aCmd);
   void executePlotSM  (Ris::CmdLineCmd* aCmd);
   void executeParms   (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************

