
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"

#include "dspThreeVector.h"

#include "CmdLineExec.h"

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
   if(aCmd->isCmd("GO1"    ))  executeGo1 (aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2 (aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3 (aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4 (aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5 (aCmd);
   if(aCmd->isCmd("GO6"    ))  executeGo6 (aCmd);
   if(aCmd->isCmd("GO7"    ))  executeGo7 (aCmd);
   if(aCmd->isCmd("GO8"    ))  executeGo8 (aCmd);
   if(aCmd->isCmd("GO9"    ))  executeGo9 (aCmd);
}

//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   double tAV[3] = { 201.0,202.0,203.0 };
   Dsp::ThreeVector tX1(tAV);
   tX1.show("tX");

   Dsp::ThreeVector tX2(201.0,202.0,203.0);
   tX2.show("tX2");
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   double tAV[3] = { 201.0,202.0,203.0 };
   Dsp::ThreeVector tX;
   tX.set(tAV);
   tX.show("tX");

   tX.set(201.0,202.0,203.0 );
   tX.show("tX");
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   tX1.show("tX1");

   tX1.e(1) *= 2.0;
   tX1(2) *= 2.0;
   tX1.show("tX1");
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   Dsp::ThreeVector tX2(201.0,202.0,203.0);
   Dsp::ThreeVector tX3(301.0,302.0,303.0);
   Dsp::ThreeVector tX4 = tX1 + tX2 + tX3;
   tX4.show("tX4");
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   double tS=2.0;
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   Dsp::ThreeVector tX2 = tX1*2.0;
   tX2.show("tX2");
}

//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
   double tS=2.0;
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   Dsp::ThreeVector tX2 = 2.0*tX1;
   tX2.show("tX2");
}

//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo9(Ris::CmdLineCmd* aCmd)
{
}

