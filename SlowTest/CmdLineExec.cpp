#include "stdafx.h"


#include "CmdLineExec.h"

#include "risThreadsThreads.h"
#include "risTimeMarker.h"

#include "dspSlowTestParms.h"

#include "someTimerThread.h"
using namespace Some;

//******************************************************************************
//******************************************************************************
//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("S"))     gTimerThread->mSuspendFlag = true;
   if (aCmd->isCmd("R"))     gTimerThread->mSuspendFlag = false;
   if (aCmd->isCmd("VAL"))   executeValue(aCmd);
   if (aCmd->isCmd("DEL"))   executeDelta(aCmd);
   if (aCmd->isCmd("GO1"))   executeGo1(aCmd);
   if (aCmd->isCmd("GO2"))   executeGo2(aCmd);
   if (aCmd->isCmd("GO3"))   executeGo3(aCmd);
   if (aCmd->isCmd("GO3"))   executeGo3(aCmd);
   if (aCmd->isCmd("PARMS")) executeParms(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeValue(Ris::CmdLineCmd* aCmd)
{
   gTimerThread->mValue = aCmd->argDouble(1);
   gTimerThread->mDelta = aCmd->argDouble(2);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeDelta(Ris::CmdLineCmd* aCmd)
{
   gTimerThread->mDelta = aCmd->argDouble(1);
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

void CmdLineExec::executeGo2 (Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo3 (Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   // Read parameters files.
   Dsp::gSlowTestParms.reset();
   Dsp::gSlowTestParms.readSection("default");
   Dsp::gSlowTestParms.show();
}

