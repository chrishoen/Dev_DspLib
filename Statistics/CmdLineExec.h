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

  void executeGo1  (Ris::CmdLineCmd* aCmd);
  void executeGo2  (Ris::CmdLineCmd* aCmd);
  void executeGo3  (Ris::CmdLineCmd* aCmd);
  void executeGo4  (Ris::CmdLineCmd* aCmd);
  void executeGo5  (Ris::CmdLineCmd* aCmd);
  void executeGo6  (Ris::CmdLineCmd* aCmd);
  void executeGo7  (Ris::CmdLineCmd* aCmd);
  void executeGo8  (Ris::CmdLineCmd* aCmd);
  void executeGo9  (Ris::CmdLineCmd* aCmd);
  void executeGo10 (Ris::CmdLineCmd* aCmd);
  void executeGo11 (Ris::CmdLineCmd* aCmd);
  void executeGo12 (Ris::CmdLineCmd* aCmd);
  void executeGo13 (Ris::CmdLineCmd* aCmd);

  bool mStepFlag;
};

//******************************************************************************
#endif

