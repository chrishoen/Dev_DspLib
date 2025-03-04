#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risBaseDir.h"
#include "dspPaths.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("MinMax Program****************************************BEGIN\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Program.

   // Enter process.
   Ris::Threads::enterProcessHigh();

   // Set the program current working directory and the base 
   // directory to the program bin directory.
   Ris::chdirBaseDirectoryToBin();

   // Initialize file paths.
   Dsp::initialize_paths();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize print facility.

   // Initialize print.
   Prn::resetPrint();
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::Show1, true);
   Prn::setFilter(Prn::Show2, false);
   Prn::setFilter(Prn::Show3, false);
   Prn::setFilter(Prn::Show4, false);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize program resources.

void main_finalize()
{
   // Finalize print facility.
   Prn::finalizePrint();

   // Exit process.
   Ris::Threads::exitProcess();

   // Done.
   printf("\n");
   printf("MinMax Program****************************************END\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
