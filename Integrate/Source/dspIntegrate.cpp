/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <math.h>
#include <random>

#include "dspIntegrate.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

double integrate1(
   std::function<double(double)> aFn,
   int aNumPoints,
   double aX1Lower, double aX1Upper)
{
   if (aNumPoints<1)aNumPoints=1;

   double tDeltaX1 = (aX1Upper-aX1Lower)/aNumPoints;
   double tX1=aX1Lower;
   double tSumX1 = 0.0;

   for (int i1 = 0; i1 < aNumPoints; i1++)
   {
      tSumX1 += aFn(tX1)*tDeltaX1;
      tX1    += tDeltaX1;
   }

   return tSumX1;

}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

double integrate2(
   std::function<double(double,double)> aFn,
   int aNumPoints,
   double aX1Lower, double aX1Upper,
   double aX2Lower, double aX2Upper)
{
   if (aNumPoints<1)aNumPoints=1;

   double tDeltaX1 = (aX1Upper-aX1Lower)/aNumPoints;
   double tX1=aX1Lower;
   double tSumX1 = 0.0;

   for (int i1 = 0; i1 < aNumPoints; i1++)
   {
      double tDeltaX2 = (aX2Upper-aX2Lower)/aNumPoints;
      double tX2=aX2Lower;
      double tSumX2 = 0.0;

      for (int i2 = 0; i2 < aNumPoints; i2++)
      {
         tSumX2 += aFn(tX1,tX2)*tDeltaX2;
         tX2 += tDeltaX2;
      }

      tSumX1 += tSumX2*tDeltaX1;
      tX1    += tDeltaX1;
   }

   return tSumX1;
}
   
}//namespace
