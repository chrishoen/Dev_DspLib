#include "stdafx.h"

#include "Special_Parms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void main_initialize(int argc,char** argv)
{
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

   Prn::print(0,"Test**********************************************BEGIN");

   // Read parms files.
   gSpecial_Parms.reset();
   gSpecial_Parms.readSection("Default");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void main_finalize()
{
   Prn::print(0,"Test**********************************************END");

   // Close print facility.
   Prn::finalizePrint();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
