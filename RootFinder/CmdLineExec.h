#pragma once

#include "risCmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

  CmdLineExec();

  void reset();
  void execute(Ris::CmdLineCmd* aCmd);

  void executeGo11(Ris::CmdLineCmd* aCmd);
  void executeGo12(Ris::CmdLineCmd* aCmd);

  void executeGo21(Ris::CmdLineCmd* aCmd);
  void executeGo22(Ris::CmdLineCmd* aCmd);

  void executeGo3(Ris::CmdLineCmd* aCmd);
  void executeGo4(Ris::CmdLineCmd* aCmd);
  void executeGo5(Ris::CmdLineCmd* aCmd);
  void executeGo6(Ris::CmdLineCmd* aCmd);

  void executeParms(Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

