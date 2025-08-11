/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnPaths.h"
#include "PulseParms.h"
#include "PulseProc.h"

#define  _PULSEGEN_CPP_
#include "PulseGen.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

PulseGen::PulseGen()
{
   resetVars();
}
void PulseGen::resetVars()
{
   mSampleCountMax = 0;
   mSampleTime = 0;
   mSampleCount = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Generate a sample history csv file of pulses based on a command line
// script file.

void PulseGen::doGenerate()
{
   Prn::print(0, "PulseGen::doGenerate BEGIN");

   // Initialixe.
   resetVars();
   mSampleCount = 0;

   // Open the script file.
   if (!mScript.doOpen(Cmn::get_filepath_from_id(Cmn::cFile_PulseGenScript)))
   {
      printf("Tester2 file not found\n");
      return;
   }

   // Initialize.
   gPulseProc.initialize();


   // Loop to read the script file and execute commands.
   Ris::CmdLineCmd* tCmd = new Ris::CmdLineCmd;
   while (true)
   {
      // Read a line from the script file and parse it into a command.
      if (mScript.doRead(tCmd))
      {
         // Test for an exit command.
         if (tCmd->isCmd("EXIT")) break;
         // Execute the command.
         execute(tCmd);
         if (mSampleCount >= mSampleCountMax)
         {
            break;
         }
         // Test for a bad command.
         if (tCmd->isBadCmd())
         {
            printf("Script bad cmd ********************\n");
            break;
         }
      }
   }

   // Finalize.
   gPulseProc.finalize();

   // Done.
   delete tCmd;
   mScript.doClose();
   Prn::print(0, "PulseGen::doGenerate END %d", mSampleCount);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute a command line command from the script file. It calls one of
// the following specific command execution functions.

void PulseGen::execute(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isCmd("Init"))       executeInit(aCmd);
   if (aCmd->isCmd("StepHi"))     executeStepHi(aCmd);
   if (aCmd->isCmd("StepLo"))     executeStepLo(aCmd);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute init variables commands.

void PulseGen::executeInit(Ris::CmdLineCmd* aCmd)
{
   if (aCmd->isArgString(1, "SampleCountMax"))
   {
      mSampleCountMax = aCmd->argInt(2);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Execute set value variables commands.

void PulseGen::doSetOutputValue(bool aPulseFlag)
{
   gPulseProc.processPulse(aPulseFlag);
   mSampleTime += (float)gPulseParms.mFilterDT;
   mSampleCount++;
}

void PulseGen::executeStepHi(Ris::CmdLineCmd* aCmd)
{
   int tLoopCount = aCmd->argInt(1);
   for (int i = 0; i < tLoopCount; i++)
   {
      if (mSampleCount >= mSampleCountMax)
      {
         mScript.doExitLoop();
         break;
      }
      doSetOutputValue(true);
   }
}

void PulseGen::executeStepLo(Ris::CmdLineCmd* aCmd)
{
   int tLoopCount = aCmd->argInt(1);
   for (int i = 0; i < tLoopCount; i++)
   {
      if (mSampleCount >= mSampleCountMax)
      {
         mScript.doExitLoop();
         break;
      }
      doSetOutputValue(false);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

