#include "stdafx.h"

#include "risThreadsProcess.h"

#include "risBaseDir.h"
#include "risPortableCalls.h"
#include "someSlowTestParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize program resources.

void main_initialize(int argc,char** argv)
{
   printf("SlowTest Program********************************************BEGIN\n");
   printf("SlowTest Program********************************************BEGIN\n");
   printf("SlowTest Program********************************************BEGIN\n\n");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Set program directory.

   // Set the base directory global variable to the cproc directory path.
   if (Ris::portableIsWindows())
   {
      Ris::setBaseDirectory("c:/aaa_cproc");
   }
   else
   {
      Ris::setBaseDirectory("/opt/cproc");
   }

   // Set the program working directory to the cproc directory path.
   Ris::chdirToBaseDirectory();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Enter process.

   // Set program process for high priority.
   Ris::Threads::enterProcessHigh();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize thread services.

   TS::reset();
   TS::setProgramName("Thresholder");
   TS::setProgramPrintLevel(0);
   TS::initialize();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize print facility.

   // Initialize print.
   Prn::resetPrint();
   Prn::useConsole(1);
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::View11, true,  1);
   Prn::setFilter(Prn::View12, false, 1);
   Prn::setFilter(Prn::View13, false, 1);
   Prn::setFilter(Prn::View14, false, 1);

   Prn::setFilter(Prn::Show1, true);
   Prn::setFilter(Prn::Show2, true);
   Prn::setFilter(Prn::Show3, false);
   Prn::setFilter(Prn::Show4, false);
   Prn::setFilter(Prn::Show5, false);
   Prn::setFilter(Prn::Show6, false);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************

   // Read parameters files.
   Some::gSlowTestParms.reset();
   Some::gSlowTestParms.readSection("default");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize program resources.

   Prn::print(Prn::View11,"SlowTest Program********************************************BEGIN");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize program resourcs.

void main_finalize()
{
   // Finalize print facility.
   Prn::finalizePrint();

   // Exit process.
   Ris::Threads::exitProcess();

   // Finalize thread services.
   TS::finalize();

   // Done.
   printf("\n");
   printf("SlowTest Program********************************************END\n\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
