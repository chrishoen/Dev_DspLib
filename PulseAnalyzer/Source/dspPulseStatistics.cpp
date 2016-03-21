/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <math.h>
#include "my_functions.h"
#include "prnPrint.h"
#include "dspPdwFreeList.h"
#include "dspPulseStatistics.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

PulseStatistics::PulseStatistics()
{
   reset();
}

void PulseStatistics::reset()
{
   mFs = 10000.0;
   mTs = 1.0 / mFs;
   mWindowTimeSize  = 0.100;
   mWindowNumSample = (int)(round(mFs * mWindowTimeSize));
}

void PulseStatistics::initialize()
{
   mTs = 1.0 / mFs;
   mWindowNumSample = (int)(round(mFs * mWindowTimeSize));

   mCount = 0;
   mAmplitude.reset();
   mPulseWidth.reset();
   mPulseDensity.initialize(mWindowNumSample);
}

void PulseStatistics::finalize()
{
   mPulseDensity.finalize();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Add a pdw to the statistics.

void PulseStatistics::addPdw(Pdw* aPdw)
{
   mCount++;
   mAmplitude.add  (aPdw->mAmplitude);
   mPulseWidth.add (aPdw->mPulseWidth);

   mAmplitude.calculate ();
   mPulseWidth.calculate ();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Subtract a pdw from the statistics.

void PulseStatistics::subtractPdw(Pdw* aPdw)
{
   mCount--;
   mAmplitude.subtract  (aPdw->mAmplitude);
   mPulseWidth.subtract (aPdw->mPulseWidth);

   mAmplitude.calculate ();
   mPulseWidth.calculate ();
}

void PulseStatistics::putPulseDensity(double aX)
{
   mPulseDensity.put(aX);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace