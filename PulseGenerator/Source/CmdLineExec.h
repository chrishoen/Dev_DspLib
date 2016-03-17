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

  void executeT11 (Ris::CmdLineCmd* aCmd);
  void executeT21 (Ris::CmdLineCmd* aCmd);
  void executeT22 (Ris::CmdLineCmd* aCmd);
  void executeT31 (Ris::CmdLineCmd* aCmd);
  void executeT32 (Ris::CmdLineCmd* aCmd);
  void executeT33 (Ris::CmdLineCmd* aCmd);
  void executeT41 (Ris::CmdLineCmd* aCmd);
  void executeT42 (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
#endif

