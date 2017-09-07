#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "prnPrint.h"
#include "CmdLineExec.h"
#include "TestFunctionObject.h"
#include "SysEquations.h"
#include "Special_Parms.h"
#include "dspRootFinder.h"

using namespace std;

// change203
//******************************************************************************
CmdLineExec::CmdLineExec()
{
   mX=101.123456;
   mT=0.1;
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

   if(aCmd->isCmd("Parms"  ))  executeParms(aCmd);

   if(aCmd->isCmd("X"      ))  mX=aCmd->argDouble(1);
   if(aCmd->isCmd("T"      ))  mT=aCmd->argDouble(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Dsp::RootFinder tRootFinder;

   TestFunctionObject  tTest;
   tTest.mC0 = gSpecial_Parms.mC0;
   tTest.mC1 = gSpecial_Parms.mC1;
   tTest.mC2 = gSpecial_Parms.mC2;


   //Set the dimension of tXInitial, tX and tWeight, then intialize them
   Eigen::VectorXd    tXInitial = Eigen::VectorXd(1);
   Eigen::VectorXd    tWeight   = Eigen::VectorXd(1);
   double             tAccuracy = 0.001;        
   int                tMaxSteps = 100;        
   Eigen::VectorXd    tX = Eigen::VectorXd(1);

   tXInitial(0) = 0.5;
   tWeight(0) =   0.1;
   tX(0) =        0;

   tRootFinder.findRoot(
      &tTest,
      tXInitial,            // Input
      tWeight,              // Input
      tAccuracy,            // input        
      tMaxSteps,            // input        
      tX);                  // Output

   Prn::print(0, "Root   %10.6f", tX(0));


}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Dsp::RootFinder tRootFinder;

   SysEquations  tTest;

   tTest.mX0 = gSpecial_Parms.mX0;
   tTest.mY0 = gSpecial_Parms.mY0;

   tTest.mA120 = gSpecial_Parms.mA120;
   tTest.mA121 = gSpecial_Parms.mA121;
   tTest.mA122 = gSpecial_Parms.mA122;
   tTest.mA340 = gSpecial_Parms.mA340;
   tTest.mA341 = gSpecial_Parms.mA341;
   tTest.mA342 = gSpecial_Parms.mA342;

   tTest.mB120 = gSpecial_Parms.mB120;
   tTest.mB121 = gSpecial_Parms.mB121;
   tTest.mB122 = gSpecial_Parms.mB122;
   tTest.mB340 = gSpecial_Parms.mB340;
   tTest.mB341 = gSpecial_Parms.mB341;
   tTest.mB342 = gSpecial_Parms.mB342;
  


   //Set the dimension of tXInitial, tX and tWeight, then intialize them
   Eigen::VectorXd    tXInitial = Eigen::VectorXd(2);
   Eigen::VectorXd    tWeight = Eigen::VectorXd(2);
   double             tAccuracy = 0.001;
   int                tMaxSteps = 100;
   Eigen::VectorXd    tX = Eigen::VectorXd(2);

   tXInitial(0) = tTest.mX0;
   tXInitial(1) = tTest.mY0;
   tWeight(0) = 0.1;
   tWeight(1) = 0.1;

   tX(0) = 0;
   tX(1) = 0;

   tRootFinder.findRoot(
      &tTest,
      tXInitial,            // Input
      tWeight,              // Input
      tAccuracy,            // input        
      tMaxSteps,            // input        
      tX);                  // Output

   Prn::print(0, "Root   %10.6f %10.6f", tX(0), tX(1));


}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Dsp::RootFinder tRootFinder;

   TestFunctionObject  tTest;
   tTest.mC0 = gSpecial_Parms.mC0;
   tTest.mC1 = gSpecial_Parms.mC1;
   tTest.mC2 = gSpecial_Parms.mC2;


   //Set the dimension of tXInitial, tX and tWeight, then intialize them
   Eigen::VectorXd    tXInitial = Eigen::VectorXd(1);
   Eigen::VectorXd    tWeight = Eigen::VectorXd(1);
   double             tAccuracy = 0.001;
   int                tMaxSteps = 100;
   Eigen::VectorXd    tX = Eigen::VectorXd(1);

   tXInitial(0) = 0.5;
   tWeight(0) = 0.1;
   tX(0) = 0;

   tRootFinder.findRoot(
      &tTest,
      tXInitial,            // Input
      tWeight,              // Input
      tAccuracy,            // input        
      tMaxSteps,            // input        
      tX);                  // Output

   Prn::print(0, "Root   %10.6f", tX(0));
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,true);

   bool tX = aCmd->argBool(1);

   Prn::print(0, "X %d",tX);

   tX ^= true;

   Prn::print(0, "X %d",tX);
}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,0.0);
   double tX = aCmd->argDouble(1);
   double tY = sqrt(tX);
   Prn::print(0, "XY   %10.6f %10.6f",tX,tY);
   Prn::print(0, "norm %10d",isnormal(tY));
}

//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeParms(Ris::CmdLineCmd* aCmd)
{
   gSpecial_Parms.reset();
   gSpecial_Parms.readSection("Default");
   gSpecial_Parms.show();
}

