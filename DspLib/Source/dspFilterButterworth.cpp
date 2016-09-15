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

void ButterworthLP::initialize(int aN, double aFs, double aFc)
{
   butterworthCoLP(aN,aFs,aFc,&mBSize,&mASize,mBArray,mAArray);

   mXSR.initialize(mBSize);
   mYSR.initialize(mASize);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ButterworthBP::initialize(int aN, double aFs, double aFc1, double aFc2)
{
   butterworthCoBP(aN,aFs,aFc1,aFc2,&mBSize,&mASize,mBArray,mAArray);

   mXSR.initialize(mBSize);
   mYSR.initialize(mASize);
}


}//namespace
}//namespace

