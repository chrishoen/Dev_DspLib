
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
   if(aCmd->isCmd("RESET"  ))   reset();

   if(aCmd->isCmd("GO11"    ))  executeGo11 (aCmd);
   if(aCmd->isCmd("GO12"    ))  executeGo12 (aCmd);
   if(aCmd->isCmd("GO13"    ))  executeGo13 (aCmd);
   if(aCmd->isCmd("GO14"    ))  executeGo14 (aCmd);
   if(aCmd->isCmd("GO15"    ))  executeGo15 (aCmd);
   if(aCmd->isCmd("GO16"    ))  executeGo16 (aCmd);
   if(aCmd->isCmd("GO17"    ))  executeGo17 (aCmd);
   if(aCmd->isCmd("GO18"    ))  executeGo18 (aCmd);
   if(aCmd->isCmd("GO19"    ))  executeGo19 (aCmd);

   if(aCmd->isCmd("GO21"    ))  executeGo21 (aCmd);
   if(aCmd->isCmd("GO22"    ))  executeGo22 (aCmd);
   if(aCmd->isCmd("GO23"    ))  executeGo23 (aCmd);
   if(aCmd->isCmd("GO24"    ))  executeGo24 (aCmd);
   if(aCmd->isCmd("GO25"    ))  executeGo25 (aCmd);
   if(aCmd->isCmd("GO26"    ))  executeGo26 (aCmd);
   if(aCmd->isCmd("GO27"    ))  executeGo27 (aCmd);
   if(aCmd->isCmd("GO28"    ))  executeGo28 (aCmd);
   if(aCmd->isCmd("GO29"    ))  executeGo29 (aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo21(Ris::CmdLineCmd* aCmd)
{
   double tAV[3] = { 201.0,202.0,203.0 };
   Dsp::ThreeVector tX1(tAV);
   tX1.show("tX");

   Dsp::ThreeVector tX2(201.0,202.0,203.0);
   tX2.show("tX2");
}

//******************************************************************************

void CmdLineExec::executeGo22(Ris::CmdLineCmd* aCmd)
{
   double tAV[3] = { 201.0,202.0,203.0 };
   Dsp::ThreeVector tX;
   tX.set(tAV);
   tX.show("tX");

   tX.set(201.0,202.0,203.0 );
   tX.show("tX");
}

//******************************************************************************

void CmdLineExec::executeGo23(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   tX1.show("tX1");

   tX1.e(1) *= 2.0;
   tX1(2) *= 2.0;
   tX1.show("tX1");
}

//******************************************************************************

void CmdLineExec::executeGo24(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   Dsp::ThreeVector tX2(201.0,202.0,203.0);
   Dsp::ThreeVector tX3(301.0,302.0,303.0);
   Dsp::ThreeVector tX4 = tX1 + tX2 + tX3;
   tX4.show("tX4");
}

//******************************************************************************

void CmdLineExec::executeGo25(Ris::CmdLineCmd* aCmd)
{
   double tS=2.0;
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   Dsp::ThreeVector tX2 = tX1*2.0;
   tX2.show("tX2");

   Dsp::ThreeVector tX3 = 2.0*tX1;
   tX3.show("tX3");
}

//******************************************************************************

void CmdLineExec::executeGo26(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   Dsp::ThreeVector tX2(201.0,202.0,203.0);
   Dsp::ThreeVector tX3(301.0,302.0,303.0);
   Dsp::ThreeVector tX4 = 2.0*(tX1 + tX2 - tX3);
   tX4.show("tX4");

   tX4.setNormalize();
   tX4.show("tX4");
}

//******************************************************************************

void CmdLineExec::executeGo27(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo28(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo29(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo11(Ris::CmdLineCmd* aCmd)
{
   double tAV[3] = { 201.0,202.0,203.0 };
   Dsp::ThreeVector tX1(tAV);
   tX1.show("tX");

   Dsp::ThreeVector tX2(201.0,202.0,203.0);
   tX2.show("tX2");
}

//******************************************************************************

void CmdLineExec::executeGo12(Ris::CmdLineCmd* aCmd)
{
   double tAV[3] = { 201.0,202.0,203.0 };
   Dsp::ThreeVector tX;
   tX.set(tAV);
   tX.show("tX");

   tX.set(201.0,202.0,203.0 );
   tX.show("tX");
}

//******************************************************************************

void CmdLineExec::executeGo13(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   tX1.show("tX1");

   tX1.e(1) *= 2.0;
   tX1(2) *= 2.0;
   tX1.show("tX1");
}

//******************************************************************************

void CmdLineExec::executeGo14(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   Dsp::ThreeVector tX2(201.0,202.0,203.0);
   Dsp::ThreeVector tX3(301.0,302.0,303.0);
   Dsp::ThreeVector tX4 = tX1 + tX2 + tX3;
   tX4.show("tX4");
}

//******************************************************************************

void CmdLineExec::executeGo15(Ris::CmdLineCmd* aCmd)
{
   double tS=2.0;
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   Dsp::ThreeVector tX2 = tX1*2.0;
   tX2.show("tX2");

   Dsp::ThreeVector tX3 = 2.0*tX1;
   tX3.show("tX3");
}

//******************************************************************************

void CmdLineExec::executeGo16(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeVector tX1(101.0,102.0,103.0);
   Dsp::ThreeVector tX2(201.0,202.0,203.0);
   Dsp::ThreeVector tX3(301.0,302.0,303.0);
   Dsp::ThreeVector tX4 = 2.0*(tX1 + tX2 - tX3);
   tX4.show("tX4");

   tX4.setNormalize();
   tX4.show("tX4");
}

//******************************************************************************

void CmdLineExec::executeGo17(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo18(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo19(Ris::CmdLineCmd* aCmd)
{
}

