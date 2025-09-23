#include "stdafx.h"

#include "risThreadsProcess.h"
#include "risBaseDir.h"
#include "dspPaths.h"
#include "Parms.h"
#include "MainInit.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("CDiffTest Program****************************************BEGIN\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Program.

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

   // Initialize print filters.
   Prn::setFilter(Prn::ThreadRun1,  true);
   Prn::setFilter(Prn::ThreadRun2,  false);
   Prn::setFilter(Prn::ThreadRun3,  true);
   Prn::setFilter(Prn::ThreadRun4,  true);

   Prn::setFilter(Prn::ProcRun1,    true);
   Prn::setFilter(Prn::ProcRun2,    true);
   Prn::setFilter(Prn::ProcRun3,    false);
   Prn::setFilter(Prn::ProcRun4,    true);

   Prn::setFilter(Prn::ViewRun1,    true);
   Prn::setFilter(Prn::ViewRun2,    true);
   Prn::setFilter(Prn::ViewRun3,    false);
   Prn::setFilter(Prn::ViewRun4,    true);

   Prn::setFilter(Prn::DspRun1,    true);
   Prn::setFilter(Prn::DspRun2,    true);
   Prn::setFilter(Prn::DspRun3,    false);
   Prn::setFilter(Prn::DspRun4,    false);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read parameters file.

   gParms.reset();
   gParms.readSection("default");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize program resources.

void main_finalize()
{
   // Finalize print facility.
   Prn::finalizePrint();

   // Done.
   printf("\n");
   printf("CDiffTest Program****************************************END\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
