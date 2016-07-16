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

  void executeGo11  (Ris::CmdLineCmd* aCmd);
  void executeGo12  (Ris::CmdLineCmd* aCmd);
  void executeGo13  (Ris::CmdLineCmd* aCmd);
  void executeGo14  (Ris::CmdLineCmd* aCmd);
  void executeGo15  (Ris::CmdLineCmd* aCmd);
  void executeGo16  (Ris::CmdLineCmd* aCmd);
  void executeGo17  (Ris::CmdLineCmd* aCmd);
  void executeGo18  (Ris::CmdLineCmd* aCmd);
  void executeGo19  (Ris::CmdLineCmd* aCmd);

  void executeGo21  (Ris::CmdLineCmd* aCmd);
  void executeGo22  (Ris::CmdLineCmd* aCmd);
  void executeGo23  (Ris::CmdLineCmd* aCmd);
  void executeGo24  (Ris::CmdLineCmd* aCmd);
  void executeGo25  (Ris::CmdLineCmd* aCmd);
  void executeGo26  (Ris::CmdLineCmd* aCmd);
  void executeGo27  (Ris::CmdLineCmd* aCmd);
  void executeGo28  (Ris::CmdLineCmd* aCmd);
  void executeGo29  (Ris::CmdLineCmd* aCmd);
  
  void executeGo31  (Ris::CmdLineCmd* aCmd);
  void executeGo32  (Ris::CmdLineCmd* aCmd);
  void executeGo33  (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
#endif

