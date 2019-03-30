
#include "stdafx.h"

#include "dspLut.h"

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
   if(aCmd->isCmd("GO1"    ))  executeGo1(aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2(aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
}

//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,102.0);
   double tX=aCmd->argDouble(1);

   double tT[4] = {200.0,
                   201.0,
                   202.0,
                   203.0};

   Dsp::Lut1D tLut;
   tLut.initialize(4,100.0,1.0,&tT[0]);

   double tV=tLut.lookup(tX);
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,101.5);
   aCmd->setArgDefault(2,201.5);

   double tX=aCmd->argDouble(1);
   double tY=aCmd->argDouble(2);

   double tT[4][3] = {{1.0,2.0,3.0},
                      {2.0,3.0,4.0},
                      {3.0,4.0,5.0},
                      {4.0,5.0,6.0}};

   Dsp::Lut2D tLut;
   tLut.initialize(
      4,3,
      100.0,200.0,
      1.0,1.0,
      &tT[0][0]);

   double tV=tLut.lookup(tX,tY);
   Prn::print(0,"%6.2f",tV);
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{

   Prn::print(0,"\x1B[37m\x1B[41m");
   Prn::print(0,"ABCDEFGH");
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
}

