#pragma once

/*==============================================================================
Program command line executive.
==============================================================================*/

#include "risCmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class is the program command line executive. It processes user
// command line inputs and executes them. It inherits from the command line
// command executive base class, which provides an interface for executing
// command line commands. It provides an override execute function that is
// called by a console executive when it receives a console command line input.
// The execute function then executes the command.

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Pause mode.
   int mPauseMode;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor.

   CmdLineExec();
   void reset() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Base class override. Execute a command line command. It calls one of
   // the following specific command execution functions. This is called by
   // the owner of this object to pass command line commands to it. 
   void execute(Ris::CmdLineCmd* aCmd) override;

   // Base class override. Show help.
   void executeHelp(Ris::CmdLineCmd* aCmd) override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   void executeGo1(Ris::CmdLineCmd* aCmd);
   void executeGo2(Ris::CmdLineCmd* aCmd);
   void executeGo3(Ris::CmdLineCmd* aCmd);
   void executeGo4(Ris::CmdLineCmd* aCmd);
   void executeGo5(Ris::CmdLineCmd* aCmd);

   void executeAlpha1    (Ris::CmdLineCmd* aCmd);
   void executeAlpha2    (Ris::CmdLineCmd* aCmd);
   void executeAlpha3    (Ris::CmdLineCmd* aCmd);
   void executeSliding2  (Ris::CmdLineCmd* aCmd);
   void executeSliding3  (Ris::CmdLineCmd* aCmd);
   void executeAbsDev    (Ris::CmdLineCmd* aCmd);
   void executeBias      (Ris::CmdLineCmd* aCmd);

   void executeTest1   (Ris::CmdLineCmd* aCmd);
   void executeTest2   (Ris::CmdLineCmd* aCmd);
   void executeTest3   (Ris::CmdLineCmd* aCmd);

   void executePlotA   (Ris::CmdLineCmd* aCmd);
   void executePlotSM  (Ris::CmdLineCmd* aCmd);
   void executePlotB   (Ris::CmdLineCmd* aCmd);
   void executeParms   (Ris::CmdLineCmd* aCmd);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

