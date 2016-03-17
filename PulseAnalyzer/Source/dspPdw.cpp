/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>

#include "dspPdw.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
Pdw::Pdw()
{
   reset();
}

void Pdw::reset()
{
   mSeqNum = 0;
   mToa = 0.0;
   mAmplitude = 0.0;
   mPulseWidth = 0.0;
}

   
}//namespace