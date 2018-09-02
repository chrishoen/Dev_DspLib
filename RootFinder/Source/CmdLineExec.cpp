#include "stdafx.h"

#include "risProgramTime.h"
#include "Special_Parms.h"
#include "SysEquations.h"
#include "SysEquationsTwo.h"
#include "dspRootFinder.h"
#include "dspRootFinderTwo.h"

#include "CmdLineExec.h"

using namespace std;

// change203
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
   if(aCmd->isCmd("GO11"   ))  executeGo11(aCmd);
   if(aCmd->isCmd("GO12"   ))  executeGo12(aCmd);
   if(aCmd->isCmd("GO21"   ))  executeGo21(aCmd);
   if(aCmd->isCmd("GO22"   ))  executeGo22(aCmd);

   if(aCmd->isCmd("GO3"    ))  executeGo3(aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4(aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5(aCmd);
   if(aCmd->isCmd("GO6"    ))  executeGo6(aCmd);

   if(aCmd->isCmd("Parms"  ))  executeParms(aCmd);
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

void CmdLineExec::executeGo11(Ris::CmdLineCmd* aCmd)
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

   Prn::print(0, "NumSteps %10d", tRootFinder.mNumSteps);
   Prn::print(0, "Root     %10.6f %10.6f", tX(0), tX(1));
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo12(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0,"Start");
   Ris::ProgramTimeMarker tMarker;
   tMarker.doStart();

   for (int i = 0; i < 10*1000; i++)
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
   }

   tMarker.doStop();
   Prn::print(0,"Elapsed %10.2f",tMarker.mElapsed);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void CmdLineExec::executeGo21(Ris::CmdLineCmd* aCmd)
{
   Dsp::RootFinderTwo<2> tRootFinder;

   SysEquationsTwo  tFunction(gSpecial_Parms);

   //Set the dimension of tXInitial, tX and tWeight, then intialize them.
   Eigen::Matrix<double,2,1>   tXInitial;
   Eigen::Matrix<double,2,1>   tWeight;
   double                      tAccuracy = 0.001;
   int                         tMaxSteps = 100;
   Eigen::Matrix<double,2,1>   tX;

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

   Prn::print(0, "NumSteps %10d", tRootFinder.mNumSteps);
   Prn::print(0, "Root     %10.6f %10.6f", tX(0), tX(1));
}

void CmdLineExec::executeGo22(Ris::CmdLineCmd* aCmd)
{
   Prn::print(0,"Start");
   Ris::ProgramTimeMarker tMarker;
   tMarker.doStart();

   SysEquationsTwo  tFunction(gSpecial_Parms);

   for (int i = 0; i < 10*1000; i++)
   {
      Dsp::RootFinderTwo<2> tRootFinder;
      SysEquationsTwo       tFunction(gSpecial_Parms);

      //Set the dimension of tXInitial, tX and tWeight, then intialize them.
      Eigen::Matrix<double,2,1>   tXInitial;
      Eigen::Matrix<double,2,1>   tWeight;
      double                      tAccuracy = 0.001;
      int                         tMaxSteps = 100;
      Eigen::Matrix<double,2,1>   tX;

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

