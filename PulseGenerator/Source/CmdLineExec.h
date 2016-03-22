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

  void executeGo1 (Ris::CmdLineCmd* aCmd);
  void executeGo2 (Ris::CmdLineCmd* aCmd);

  void executeS11 (Ris::CmdLineCmd* aCmd);
  void executeS21 (Ris::CmdLineCmd* aCmd);
  void executeS22 (Ris::CmdLineCmd* aCmd);
  void executeS31 (Ris::CmdLineCmd* aCmd);
  void executeS32 (Ris::CmdLineCmd* aCmd);
  void executeS33 (Ris::CmdLineCmd* aCmd);
  void executeS34 (Ris::CmdLineCmd* aCmd);
  void executeS41 (Ris::CmdLineCmd* aCmd);
  void executeS42 (Ris::CmdLineCmd* aCmd);

  void executeP11 (Ris::CmdLineCmd* aCmd);
  void executeP21 (Ris::CmdLineCmd* aCmd);
  void executeP22 (Ris::CmdLineCmd* aCmd);

  void executeF51 (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
#endif

