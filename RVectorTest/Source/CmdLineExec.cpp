
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"

#include "dspRVector.h"

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
   if(aCmd->isCmd("GO6"    ))  executeGo6(aCmd);
   if(aCmd->isCmd("GO7"    ))  executeGo7(aCmd);
   if(aCmd->isCmd("GO8"    ))  executeGo8(aCmd);
}

//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   double tT[3] = {201.0,
                   202.0,
                   203.0};

   Dsp::RVector tX;
   tX.initialize(3,&tT[0]);

   tX.show("tX");
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   double tT[3][3] = {{11.0,12.0,13.0},
                      {21.0,22.0,23.0},
                      {31.0,32.0,33.0}};
   Dsp::RMatrix tX;
   tX.initialize(3,3,&tT[0][0]);

   tX.show("tX");
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   // X1
   double tT1[3] = {101.0,
                    102.0,
                    103.0};

   Dsp::RVector tX1;
   tX1.initialize(3,&tT1[0]);

   tX1.show("tX1");

   // X2
   Dsp::RVector tX2(tX1);

   tX2.show("tX2");

   // X3
   Dsp::RVector tX3 = tX1;

   tX3.show("tX3");

   // X4
   Dsp::RVector tX4;
   tX4 = tX1;

   tX4.show("tX4");

   // X5
   Dsp::RVector tX5;
   tX5.initialize(3);
   tX5 = tX1;

   tX5.show("tX5");
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   // X1
   double tT1[3] = {101.0,
                    102.0,
                    103.0};

   Dsp::RVector tX1;
   tX1.initialize(3,&tT1[0]);

   tX1.show("tX1");

   // X2
   double tT2[3] = {201.0,
                    202.0,
                    203.0};

   Dsp::RVector tX2;
   tX2.initialize(3,&tT2[0]);

   tX2.show("tX2");

   // X3
   Dsp::RVector tX3(3);

   tX3 = tX1 + tX2;

   tX3.show("tX3");

   tX3 = tX1 + tX2;

   tX3.show("tX3");
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   // X1
   double tT1[3] = {101.0,
                    102.0,
                    103.0};

   Dsp::RVector tX1;
   tX1.initialize(3,&tT1[0]);

   tX1.show("tX1");

   // X2
   double tT2[3] = {201.0,
                    202.0,
                    203.0};

   Dsp::RVector tX2;
   tX2.initialize(3,&tT2[0]);

   tX2.show("tX2");

   // X3
   Dsp::RVector tX3(3);

   add(tX3,tX1,tX2);

   tX3.show("tX3");

}

//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
   double tAV[3][3] = {{11.0,12.0,13.0},
                       {21.0,22.0,23.0},
                       {31.0,32.0,33.0}};
   Dsp::RMatrix tA;
   tA.initialize(3,3,&tAV[0][0]);
   tA.show("tA");

   // X1
   double tT1[3] = {101.0,
                    102.0,
                    103.0};

   Dsp::RVector tX1;
   tX1.initialize(3,&tT1[0]);

   tX1.show("tX1");

   // X2
   Dsp::RVector tX2(3);

   multiply(tX2,tA,tX1);

   tX2.show("tX2");

}

//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
   double tAV[2][2] = {{1.0,0.0},
                       {0.0,2.0}};
   Dsp::RMatrix tA;
   tA.initialize(2,2,&tAV[0][0]);
   tA.show("tA");

   // X1
   double tT1[2] = {101.0,
                    102.0};

   Dsp::RVector tX1;
   tX1.initialize(2,&tT1[0]);
   tX1.show("tX1");

   // X2
   Dsp::RVector tX2(2);

   multiply(tX2,tA,tX1);

   tX2.show("tX2");
}

//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
}

