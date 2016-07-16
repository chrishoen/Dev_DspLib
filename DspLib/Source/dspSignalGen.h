#ifndef _DSPSIGNALGEN_H_
#define _DSPSIGNALGEN_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspSignal.h"

namespace Dsp
{
namespace SignalGen
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

   void constant (Signal* aS);
   void impulse  (Signal* aS);
   void step     (Signal* aS);
   void ramp     (Signal* aS);
   void sinusoid (Signal* aS);

//******************************************************************************
}//namespace
}//namespace

#endif
