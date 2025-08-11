
#include "stdafx.h"
#include <windows.h>

#include "risSystemCalls.h"
#include "PulseParms.h"
#include "PulseGen.h"
#include "PulseProc.h"

#include "CmdLineExec.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

CmdLineExec::CmdLineExec()
{
}
void CmdLineExec::reset()
{
   mPauseMode = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override. Execute a command line command. It calls one of
// the following specific command execution functions. This is called by
// the owner of this object to pass command line commands to it. 

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("GO1"))       executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))       executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))       executeGo3(aCmd);
   if (aCmd->isCmd("GO4"))       executeGo4(aCmd);

   if (aCmd->isCmd("PG"))        executePulseGen(aCmd);
   if (aCmd->isCmd("PLOT"))      executePlot(aCmd);

   if (aCmd->isCmd("Show"))      executeShow(aCmd);
   if (aCmd->isCmd("Parms"))     executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executePulseGen (Ris::CmdLineCmd* aCmd)
{
   gPulseGen.doGenerate();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1 (Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executePlot(Ris::CmdLineCmd* aCmd)
{
   char* tPlotRun41  = "python C:/Prime/AAA_LinuxWriter/Python_Plots/Pulses3/plot_pulse41.py";

   aCmd->setArgDefault(1,"41");
   int tPlotSelect = aCmd->argInt(1);

   char* tPlotCmd = 0;
   switch(tPlotSelect)
   {
      case 41: tPlotCmd = tPlotRun41; break;
      default: printf("PYTHON NOT FOUND\n");
      return;
   }

   int tRet = Ris::doSystemCommand(tPlotCmd);
   Sleep(1000);
   SetForegroundWindow(GetConsoleWindow());
   
   Prn::print(0, "PLOT %d %s", tRet, tPlotCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   gPulseParms.reset();
   gPulseParms.readSection("default");
   gPulseParms.show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeHelp(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0, "help ***********************************");
   Prn::print(0, "");
   Prn::print(0, "PG       -- run pulse generator");
   Prn::print(0, "Plot     -- plot stroke detector");
   Prn::print(0, "parms    -- show program parms");
   Prn::print(0, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

