#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "prnPrint.h"
#include "risProgramTime.h"
#include "CmdLineExec.h"
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

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Dsp::RootFinder tRootFinder;

   SysEquations  tFunction(gSpecial_Parms);

   //Set the dimension of tXInitial, tX and tWeight, then intialize them
   Eigen::VectorXd    tXInitial = Eigen::VectorXd(2);
   Eigen::VectorXd    tWeight = Eigen::VectorXd(2);
   double             tAccuracy = 0.001;
   int                tMaxSteps = 100;
   Eigen::VectorXd    tX = Eigen::VectorXd(2);

   tXInitial(0) = gSpecial_Parms.mX0;
   tXInitial(1) = gSpecial_Parms.mY0;
   tWeight(0) = 0.1;
   tWeight(1) = 0.1;

   tX(0) = 0;
   tX(1) = 0;

   tRootFinder.findRoot(
      &tFunction,
      tXInitial,            // Input
      tWeight,              // Input
      tAccuracy,            // input        
      tMaxSteps,            // input        
      tX);                  // Output

   Prn::print(0, "Root   %10.6f %10.6f", tX(0), tX(1));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Dsp::RootFinder tRootFinder;

   Prn::print(0,"Start");
   Ris::ProgramTimeMarker tMarker;
   tMarker.doStart();

   SysEquations  tFunction(gSpecial_Parms);

   for (int i = 0; i < 10*1000; i++)
   {
      //Set the dimension of tXInitial, tX and tWeight, then intialize them
      Eigen::VectorXd    tXInitial = Eigen::VectorXd(2);
      Eigen::VectorXd    tWeight = Eigen::VectorXd(2);
      double             tAccuracy = 0.001;
      int                tMaxSteps = 100;
      Eigen::VectorXd    tX = Eigen::VectorXd(2);

      tXInitial(0) = gSpecial_Parms.mX0;
      tXInitial(1) = gSpecial_Parms.mY0;
      tWeight(0) = 0.1;
      tWeight(1) = 0.1;

      tX(0) = 0;
      tX(1) = 0;

      tRootFinder.findRoot(
         &tFunction,
         tXInitial,            // Input
         tWeight,              // Input
         tAccuracy,            // input        
         tMaxSteps,            // input        
         tX);                  // Output
   }

   tMarker.doStop();
   Prn::print(0,"Elapsed %10.2f",tMarker.mElapsed);
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

