
#include "stdafx.h"

#include "risThreadsProcess.h"

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

   Prn::print(0,"Butterworth Program**************************************BEGIN");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void main_finalize()
{
   Prn::print(0, "Butterworth Program**************************************END");

   // Close print.
   Prn::finalizePrint();

   // Exit process.
   Ris::Threads::exitProcess();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
