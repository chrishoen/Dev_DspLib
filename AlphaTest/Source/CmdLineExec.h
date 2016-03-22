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

  void executeFilter11(Ris::CmdLineCmd* aCmd);
  void executeFilter12(Ris::CmdLineCmd* aCmd);
  void executeTrial11 (Ris::CmdLineCmd* aCmd);


  void executeGen51 (Ris::CmdLineCmd* aCmd);
  void executeGen52 (Ris::CmdLineCmd* aCmd);
  void executeGen53 (Ris::CmdLineCmd* aCmd);
  void executeGen54 (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
#endif

