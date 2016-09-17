/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include "dsp_functions.h"
#include "dsp_math.h"

#include <math.h>
#include <string.h>

#include "dspButterworthCo.h"
#include "dspFilterButterworth.h"

namespace Dsp
{
namespace Filter
{


//******************************************************************************
//******************************************************************************
//******************************************************************************

void ButterworthLP::initialize(int aNOrder, double aFs, double aFc)
{
   // Get filter sizes.
   butterworthCoLPSize(aNOrder,&mBSize,&mASize);

   // Base class initialize.
   IIRFilter::initialize(mBSize,mASize);

   // Set filter coefficients.
   butterworthCoLP(aNOrder,aFs,aFc,&mBSize,&mASize,mBArray,mAArray);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ButterworthBP::initialize(int aNOrder, double aFs, double aFc1, double aFc2)
{
   // Get filter sizes.
   butterworthCoBPSize(aNOrder,&mBSize,&mASize);

   // Base class initialize.
   IIRFilter::initialize(mBSize,mASize);

   // Set filter coefficients.
   butterworthCoBP(aNOrder,aFs,aFc1,aFc2,&mBSize,&mASize,mBArray,mAArray);
}


}//namespace
}//namespace

