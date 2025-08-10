/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "cmnPaths.h"
#include "PulseParms.h"
#include "PlotWriter.h"
#include "PulseWriter.h"


#define  _PULSEPROC_CPP_
#include "PulseProc.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

PulseProc::PulseProc()
{
   resetVars();
}

void PulseProc::resetVars()
{
}

void PulseProc::initialize()
{
   resetVars();
   gPlotWriter.initialize();
   gPulseWriter.initialize();
}

void PulseProc::finalize()
{
   gPlotWriter.finalize();
   gPulseWriter.finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Process a pulse.

void PulseProc::processPulse(bool aPulseFlag)
{
   gPlotWriter.resetVars();
   gPulseWriter.resetVars();

   gPlotWriter.mPulseFlag = aPulseFlag;
   gPulseWriter.mPulseFlag = aPulseFlag;

   gPlotWriter.doWrite();
   gPulseWriter.doWrite();
}

