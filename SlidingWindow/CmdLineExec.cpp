#include "stdafx.h"

#include "dspTextFile.h"

#include "CmdLineExec.h"

using namespace std;
//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
void CmdLineExec::reset()
{
   mWindow.reset();
}

//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("R"      ))  reset();

   if(aCmd->isCmd("Put"    ))  executePut(aCmd);
   if(aCmd->isCmd("Get"    ))  executeGet(aCmd);

   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
}


//******************************************************************************

void CmdLineExec::executePut(Ris::CmdLineCmd* aCmd)
{
   int tValue = aCmd->argInt(1);
   mWindow.doPut(tValue);
}

//******************************************************************************

void CmdLineExec::executeGet(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,1);
   int tLoop = aCmd->argInt(1);
   for (int i = 0; i < tLoop; i++)
   {
      int tValue = mWindow.elementAt(i);
      Prn::print(0, "GET %d $ %d", i, tValue);
   }
}

//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


