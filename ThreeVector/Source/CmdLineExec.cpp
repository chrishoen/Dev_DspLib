
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"

#include "dspThreeVector.h"
#include "dspThreeMatrix.h"
#include "dspThreeFunctions.h"

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

   if(aCmd->isCmd("Go11"    ))  executeGo11 (aCmd);
   if(aCmd->isCmd("Go12"    ))  executeGo12 (aCmd);
   if(aCmd->isCmd("Go13"    ))  executeGo13 (aCmd);
   if(aCmd->isCmd("Go14"    ))  executeGo14 (aCmd);
   if(aCmd->isCmd("Go15"    ))  executeGo15 (aCmd);
   if(aCmd->isCmd("Go16"    ))  executeGo16 (aCmd);
   if(aCmd->isCmd("Go17"    ))  executeGo17 (aCmd);
   if(aCmd->isCmd("Go18"    ))  executeGo18 (aCmd);
   if(aCmd->isCmd("Go19"    ))  executeGo19 (aCmd);

   if(aCmd->isCmd("Go21"    ))  executeGo21 (aCmd);
   if(aCmd->isCmd("Go22"    ))  executeGo22 (aCmd);
   if(aCmd->isCmd("Go23"    ))  executeGo23 (aCmd);
   if(aCmd->isCmd("Go24"    ))  executeGo24 (aCmd);
   if(aCmd->isCmd("Go25"    ))  executeGo25 (aCmd);
   if(aCmd->isCmd("Go26"    ))  executeGo26 (aCmd);
   if(aCmd->isCmd("Go27"    ))  executeGo27 (aCmd);
   if(aCmd->isCmd("Go28"    ))  executeGo28 (aCmd);
   if(aCmd->isCmd("Go29"    ))  executeGo29 (aCmd);

   if(aCmd->isCmd("Go31"    ))  executeGo31 (aCmd);
   if(aCmd->isCmd("Go32"    ))  executeGo32 (aCmd);
   if(aCmd->isCmd("Go33"    ))  executeGo33 (aCmd);

   if(aCmd->isCmd("Go41"    ))  executeGo41 (aCmd);
   if(aCmd->isCmd("Go42"    ))  executeGo42 (aCmd);
   if(aCmd->isCmd("Go43"    ))  executeGo43 (aCmd);

}


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo41(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeMatrix tRx;
   Dsp::ThreeMatrix tRy;
   Dsp::ThreeMatrix tRz;
   Dsp::ThreeMatrix tR01;
   Dsp::ThreeMatrix tR10;
   Dsp::ThreeVector tG0;
   Dsp::ThreeVector tG1;

   tRx.setRotateX(45.0);
   tRy.setRotateY( 0.0);
   tRz.setRotateY( 0.0);

   tR01 = tRx*tRy;
   tR10 = tR01.transpose();

   tR01.show("tR01");
   tR10.show("tR10");


   tG0.set(0.0,0.0,-1.0);
   tG1 = tR10*tG0;

   tG0.show("tG0");
   tG1.show("tG1");

   double tA = Dsp::calcAngleBetween(tG0,tG1);
   Prn::print(0,"AngleBetween %11.6f",tA);
}

//******************************************************************************

void CmdLineExec::executeGo42(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeMatrix tRx;
   Dsp::ThreeMatrix tRy;
   Dsp::ThreeMatrix tRz;
   Dsp::ThreeMatrix tR01;
   Dsp::ThreeMatrix tR10;
   Dsp::ThreeVector tE0y;
   Dsp::ThreeVector tE1y;

   tRx.setRotateX(45.0);
   tRy.setRotateY( 0.0);
   tRz.setRotateY( 0.0);

   tR01 = tRx*tRy;
   tR10 = tR01.transpose();

   tR01.show("tR01");
   tR10.show("tR10");


   tE0y.set(0.0,1.0,0.0);
   tE1y = tR10*tE0y;

   tE0y.show("tE0y");
   tE1y.show("tE1y");

   double tA = Dsp::calcAngleBetween(tE1y,tE0y);
   Prn::print(0,"AngleBetween %11.6f",tA);

   double tTilt = Dsp::calcTiltFromUnitVector(tE1y);
   Prn::print(0,"TiltAngle    %11.6f",tTilt);
}

//******************************************************************************

void CmdLineExec::executeGo43(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo31(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeMatrix tRx;
   Dsp::ThreeMatrix tRy;
   Dsp::ThreeMatrix tRz;
   Dsp::ThreeMatrix tR01;
   Dsp::ThreeMatrix tR10;
   Dsp::ThreeVector tG0;
   Dsp::ThreeVector tG1;

   tRx.setRotateX(45.0);
   tRy.setRotateY( 0.0);
   tRz.setRotateY( 0.0);

   tR01 = tRx*tRy;
   tR10 = tR01.transpose();

   tR01.show("tR01");
   tR10.show("tR10");


   tG0.set(0.0,0.0,-1.0);
   tG1 = tR10*tG0;

   tG0.show("tG0");
   tG1.show("tG1");
}

//******************************************************************************

void CmdLineExec::executeGo32(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeMatrix tRx;
   Dsp::ThreeMatrix tRy;
   Dsp::ThreeMatrix tRz;
   Dsp::ThreeMatrix tTT1;
   Dsp::ThreeMatrix tTT2;

   tRx.setRotateX(30.0);
   tRy.setRotateY(-60.0);
   tRz.setRotateZ(-30.0);

   tTT1 = tRx*tRy*tRz*tRz.transpose()*tRy.transpose()*tRx.transpose();
   tTT2 = (tRx*tRy*tRz*tRz)*((tRx*tRy*tRz*tRz).transpose());
   
   tRx.show("tRx");
   tRy.show("tRy");
   tRz.show("tRz");

   tTT1.show("tTT1");
   tTT2.show("tTT2");
}

//******************************************************************************

void CmdLineExec::executeGo33(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeMatrix tRx;
   Dsp::ThreeMatrix tRy;
   Dsp::ThreeMatrix tRz;
   Dsp::ThreeMatrix tR01;
   Dsp::ThreeMatrix tR10;
   Dsp::ThreeVector tG0;
   Dsp::ThreeVector tG1;

   tRx.setRotateX(45.0);
   tRy.setRotateY( 0.0);
   tRz.setRotateY( 0.0);

   tR01 = tRx*tRy;
   tR10 = tR01.transpose();

   tR01.show("tR01");
   tR10.show("tR10");


   tG0.set(0.0,0.0,-1.0);
   tG1 = tR10*tG0;

   tG0.show("tG0");
   tG1.show("tG1");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo21(Ris::CmdLineCmd* aCmd)
{
   double tAV[3][3] = 
   {{  11.0, 12.0, 13.0 },
    {  21.0, 22.0, 23.0 },
    {  31.0, 32.0, 33.0 }};

   Dsp::ThreeMatrix tX1(tAV);
   tX1.show("tX");

   Dsp::ThreeMatrix tX2(
      11.0, 12.0, 13.0,
      21.0, 22.0, 23.0,
      31.0, 32.0, 33.0);

   tX2.show("tX2");
}

//******************************************************************************

void CmdLineExec::executeGo22(Ris::CmdLineCmd* aCmd)
{
   double tAV[3][3] = 
   {{  11.0, 12.0, 13.0 },
    {  21.0, 22.0, 23.0 },
    {  31.0, 32.0, 33.0 }};

   Dsp::ThreeMatrix tX1;
   tX1.set(tAV);
   tX1.show("tX1");

   Dsp::ThreeMatrix tX2;
   tX2.set(
      11.0, 12.0, 13.0,
      21.0, 22.0, 23.0,
      31.0, 32.0, 33.0);

   tX2.show("tX2");
}

//******************************************************************************

void CmdLineExec::executeGo23(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeMatrix tX1(
      11.0, 12.0, 13.0,
      21.0, 22.0, 23.0,
      31.0, 32.0, 33.0);

   tX1(1,1) *= 2.0;
   tX1(2,1) *= 2.0;
   tX1(3,1) *= 2.0;

   tX1.show("tX2");
}

//******************************************************************************

void CmdLineExec::executeGo24(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeMatrix tX1(
      11.0,  0.0,  0.0,
      21.0,  0.0,  0.0,
      31.0,  0.0,  0.0);

   Dsp::ThreeMatrix tX2(
       0.0, 21.0,  0.0,
       0.0, 22.0,  0.0,
       0.0, 23.0,  0.0);

   Dsp::ThreeMatrix tX3(
       0.0,  0.0, 31.0,
       0.0,  0.0, 32.0,
       0.0,  0.0, 33.0);

   Dsp::ThreeMatrix tX4 = tX1 + tX2 + tX3;
   tX4.show("tX4");
}

//******************************************************************************

void CmdLineExec::executeGo25(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeMatrix tX1(
      11.0, 12.0, 13.0,
      21.0, 22.0, 23.0,
      31.0, 32.0, 33.0);

   Dsp::ThreeMatrix tX2 = tX1*2.0;
   tX2.show("tX2");

   Dsp::ThreeMatrix tX3 = 2.0*tX1;
   tX3.show("tX3");
}

//******************************************************************************

void CmdLineExec::executeGo26(Ris::CmdLineCmd* aCmd)
{
   Dsp::ThreeMatrix tX1(
      11.0,  0.0,  0.0,
      21.0,  0.0,  0.0,
      31.0,  0.0,  0.0);

   Dsp::ThreeMatrix tX2(
       0.0, 21.0,  0.0,
       0.0, 22.0,  0.0,
       0.0, 23.0,  0.0);

   Dsp::ThreeMatrix tX3(
       0.0,  0.0, 31.0,
       0.0,  0.0, 32.0,
       0.0,  0.0, 33.0);

   Dsp::ThreeMatrix tX4 = 2.0*(tX1 + tX2 - tX3);
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

   tX1(1) *= 2.0;
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
   Dsp::ThreeVector tX1(1.0,0.0,0.0);
   Dsp::ThreeVector tX2(0.0,1.0,0.0);
   Dsp::ThreeVector tX3 = tX1 & tX1;
   Dsp::ThreeVector tX4 = tX1 & tX2;
   tX1.show("tX1");
   tX2.show("tX2");
   tX3.show("tX3");
   tX4.show("tX4");
}

//******************************************************************************

void CmdLineExec::executeGo18(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo19(Ris::CmdLineCmd* aCmd)
{
}

