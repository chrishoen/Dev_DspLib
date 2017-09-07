#include <stdlib.h>
#include <stdio.h>

#include "MainInit.h"
#include "prnPrint.h"
#include "risCmdLineConsole.h"
#include "CmdLineExec.h"

//******************************************************************************
int main(int argc,char** argv)
{
   //--------------------------------------------------------------------
   // Begin program

   main_initialize(argc,argv);

   //--------------------------------------------------------------------
   // Start user command line executive,
   // Wait for user to exit

   CmdLineExec* exec = new CmdLineExec;
   Ris::gCmdLineConsole.execute(exec);
   delete exec;

   //--------------------------------------------------------------------
   // End program

   main_finalize();
   return 0;
}
