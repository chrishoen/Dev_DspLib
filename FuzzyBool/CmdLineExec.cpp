#include "stdafx.h"

#include "CmdLineExec.h"
#include "dspFuzzyBool.h"

using namespace std;

//******************************************************************************
CmdLineExec::CmdLineExec()
{
}
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
   if(aCmd->isCmd("GO6"    ))  executeGo6(aCmd);
   if(aCmd->isCmd("GO7"    ))  executeGo7(aCmd);
   if(aCmd->isCmd("GO8"    ))  executeGo8(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Dsp::FuzzyBool tX1(0.50);
   Dsp::FuzzyBool tX2(0.75);

   Dsp::FuzzyBool tY1 = ~tX2;
   Dsp::FuzzyBool tY2 = tX1 & tX2;
   Dsp::FuzzyBool tY3 = tX1 | tX2;;

   Prn::print(0,"%5.3f %5.3f",      tX1.mX,tX2.mX);
   Prn::print(0,"%5.3f %5.3f %5.3f",tY1.mX,tY2.mX,tY3.mX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Dsp::FuzzyBool tX1(0.50);

   Prn::print(0, "%s %s",
      my_string_from_bool(tX1.crisp(0.51)),
      my_string_from_bool(tX1.crisp(0.49)));
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,0.45);
   aCmd->setArgDefault(2,0.55);

   Dsp::FuzzyBool tX1(aCmd->argInt(1));
   Dsp::FuzzyBool tX2(aCmd->argInt(2));

   Dsp::FuzzyBool tY1 = tX1 %= tX2;

   Prn::print(0,"X1 %5.3f", tX1.mX);
   Prn::print(0,"X2 %5.3f", tX2.mX);
   Prn::print(0,"Y1 %5.3f", tY1.mX);
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
}

