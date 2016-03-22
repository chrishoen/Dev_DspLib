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

  void executeF11(Ris::CmdLineCmd* aCmd);
  void executeF12(Ris::CmdLineCmd* aCmd);


  void executeS51 (Ris::CmdLineCmd* aCmd);
  void executeS52 (Ris::CmdLineCmd* aCmd);
  void executeS53 (Ris::CmdLineCmd* aCmd);
  void executeS54 (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
#endif

