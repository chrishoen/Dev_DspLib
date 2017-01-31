#ifndef _CMDLINEEXEC_H_
#define _CMDLINEEXEC_H_

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

   void executeRun1 (Ris::CmdLineCmd* aCmd);
   void executeRun2 (Ris::CmdLineCmd* aCmd);
   void executeRun3 (Ris::CmdLineCmd* aCmd);
   void executeRun4 (Ris::CmdLineCmd* aCmd);
   void executeRun5 (Ris::CmdLineCmd* aCmd);

   void executeParms (Ris::CmdLineCmd* aCmd);
   void executeBin   (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
#endif

