#include "stdafx.h"

#include "logFiles.h"
#include "risThreadsProcess.h"

#include "Parms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void main_initialize(int argc,char** argv)
{
   // Enter process.
   Ris::Threads::enterProcessHigh();

   // Initialize print facility.
   Prn::resetPrint();
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::ThreadRun1,  true);
   Prn::setFilter(Prn::ThreadRun2,  false);
   Prn::setFilter(Prn::ThreadRun3,  true);
   Prn::setFilter(Prn::ThreadRun4,  true);

   Prn::setFilter(Prn::ProcRun1,    true);
   Prn::setFilter(Prn::ProcRun2,    true);
   Prn::setFilter(Prn::ProcRun3,    false);
   Prn::setFilter(Prn::ProcRun4,    true);

   Prn::setFilter(Prn::ViewRun1,    true, 1);
   Prn::setFilter(Prn::ViewRun2,    true, 1);
   Prn::setFilter(Prn::ViewRun3,    false,1);
   Prn::setFilter(Prn::ViewRun4,    true, 1);

   Prn::setFilter(Prn::DspRun1,    true);
   Prn::setFilter(Prn::DspRun2,    true);
   Prn::setFilter(Prn::DspRun3,    false);
   Prn::setFilter(Prn::DspRun4,    false);

   Prn::print(0,"HistoryTest***************************************PROGRAM BEGIN");

   // Open settings file.
   gParms.readSection("default");

   // Open log files.
   Log::reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void main_finalize()
{
   Prn::print(0,"HistoryTest***************************************PROGRAM END");

   // Close log files.
   Log::closeAllFiles();

   // Close print.
   Prn::finalizePrint();


   // Exit process.
   Ris::Threads::exitProcess();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
