#include "stdafx.h"
/*==============================================================================
* ProbeTest.
*
* This program generates Probeetic data sample and stroke test inputs that
* are used to exercise various program components.
*
* 1) Generate Probeetic data for samples and strokes and scans and send
*    them to shared memory ring buffers.
*
* It initializes program resources, launches a thread which writes to
* shared memory and which access some data sources and sinks. It also
* launches a monitor thread which is used to monitor program action.
* It then either runs a command line interface or waits for a termination
* signal. Upon termination, it shuts down the threads and finalizes
* program resources.
*
==============================================================================*/

#include "risThreadsProcess.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"
#include "MainInit.h"

#include "PulseParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize program resources.

   main_initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Execute console command line executive, wait for user to exit.

   CmdLineExec* tExec = new CmdLineExec;
   Ris::gCmdLineConsole.execute(tExec);
   delete tExec;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Finalize program resources.

   main_finalize();
   return 0;
}
