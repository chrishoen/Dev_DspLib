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
   mMinMaxMean.reset();
}

//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("R"      ))  reset();

   if(aCmd->isCmd("Put"    ))  executePut(aCmd);
   if(aCmd->isCmd("Get"    ))  executeGet(aCmd);
   if(aCmd->isCmd("Tail"   ))  executeTail(aCmd);
   if(aCmd->isCmd("PutM"   ))  executePutMMM(aCmd);
   if(aCmd->isCmd("Show"   ))  executeShow(aCmd);

   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executePut(Ris::CmdLineCmd* aCmd)
{
   int tValue = aCmd->argInt(1);
   mWindow.doPut(tValue);
}

//******************************************************************************
//******************************************************************************
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
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeTail(Ris::CmdLineCmd* aCmd)
{
      int tValue = mWindow.elementAtTail();
      Prn::print(0, "TAIL %d", tValue);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executePutMMM(Ris::CmdLineCmd* aCmd)
{
   float tValue = aCmd->argFloat(1);
   mMinMaxMean.doPut(tValue);

   Prn::print(0, "MinMax %5.2f $ min = %5.2f max = %5.2f mean = %5.2f",
       tValue, mMinMaxMean.mMin, mMinMaxMean.mMax, mMinMaxMean.mMean);
}       

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   int tN = aCmd->argInt(1);
   Prn::print(0, "MOD %d $ %d", tN, tN % 4);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeShow(Ris::CmdLineCmd* aCmd)
{
   //mWindow.show();
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

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}


