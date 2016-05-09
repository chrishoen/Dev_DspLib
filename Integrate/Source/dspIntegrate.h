#ifndef _DSPINTEGRATE_H_
#define _DSPINTEGRATE_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <functional>

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

   double integrate1 (
      std::function<double(double)> aFn,
      int aNumPoints,
      double aX1Lower,double aX1Upper);

   double integrate2 (
      std::function<double(double,double)> aFn,
      int aNumPoints,
      double aX1Lower,double aX1Upper,
      double aX2Lower,double aX2Upper);
   
//******************************************************************************
}//namespace

#endif

