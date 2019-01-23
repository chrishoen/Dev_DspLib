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

   void executeRun1    (Ris::CmdLineCmd* aCmd);
   void executeRun1Deg (Ris::CmdLineCmd* aCmd);
   void executeRun2    (Ris::CmdLineCmd* aCmd);
   void executeRun3    (Ris::CmdLineCmd* aCmd);
   void executeRun4    (Ris::CmdLineCmd* aCmd);
   void executeRun5    (Ris::CmdLineCmd* aCmd);
   void executeRun6    (Ris::CmdLineCmd* aCmd);
   void executeRun7    (Ris::CmdLineCmd* aCmd);
   void executeMem1    (Ris::CmdLineCmd* aCmd);

   void executeCausal1     (Ris::CmdLineCmd* aCmd);
   void executeCausal12    (Ris::CmdLineCmd* aCmd);
   void executeNoncausal1  (Ris::CmdLineCmd* aCmd);
   void executeNoncausal12 (Ris::CmdLineCmd* aCmd);
   void executeDemo1       (Ris::CmdLineCmd* aCmd);
   void executeDemo2       (Ris::CmdLineCmd* aCmd);
   void executeDemo3       (Ris::CmdLineCmd* aCmd);

   void executeParms (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************

