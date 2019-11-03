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

   Dsp::FuzzyBool tY1 = !tX2;
   Dsp::FuzzyBool tY2 = tX1 && tX2;
   Dsp::FuzzyBool tY3 = tX1 || tX2;
   Dsp::FuzzyBool tY4 = tX1 && !tX2;

   Prn::print(0, "X1 %5.3f", tX1.mX);
   Prn::print(0, "X2 %5.3f", tX2.mX);
   Prn::print(0, "");

   Prn::print(0, "Y1 %5.3f", tY1.mX);
   Prn::print(0, "Y2 %5.3f", tY2.mX);
   Prn::print(0, "Y3 %5.3f", tY3.mX);
   Prn::print(0, "Y4 %5.3f", tY4.mX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Dsp::FuzzyBool tX1(0.50);

   Prn::print(0, "%s %s",
      my_string_from_bool(tX1.crisp(0.49)),
      my_string_from_bool(tX1.crisp(0.51)));
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0.45);
   aCmd->setArgDefault(2, 0.55);

   Dsp::FuzzyBool tX1(aCmd->argDouble(1));
   Dsp::FuzzyBool tX2(aCmd->argDouble(2));

   Dsp::FuzzyBool tY1 = tX1 %= tX2;

   Prn::print(0, "X1 %5.3f", tX1.mX);
   Prn::print(0, "X2 %5.3f", tX2.mX);
   Prn::print(0, "Y1 %5.3f", tY1.mX);
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1, 0.90);
   aCmd->setArgDefault(2, 0.80);

   Dsp::FuzzyBool tX1(aCmd->argDouble(1));
   Dsp::FuzzyBool tX2(aCmd->argDouble(2));

   Dsp::FuzzyBool tY1 = tX1 && !tX2;
   bool tC1 = (tY1 = tX1 && !tX2).crisp(0.5);

   Prn::print(0, "X1 %5.3f", tX1.mX);
   Prn::print(0, "X2 %5.3f", tX2.mX);
   Prn::print(0, "Y1 %5.3f", tY1.mX);
   Prn::print(0, "C1 %5s", my_string_from_bool(tC1));
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

