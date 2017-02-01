/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dsp_functions.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Min,Max

double dsp_fmin (double aA,double aB) {return aA > aB ? aB : aA;}
double dsp_fmax (double aA,double aB) {return aA > aB ? aA : aB;}

int    dsp_imin (int aA,int aB) {return aA > aB ? aB : aA;}
int    dsp_imax (int aA,int aB) {return aA > aB ? aA : aB;}

int    my_ibound(int aA, int aLowerBound, int aUpperBound)
{
   if (aA < aLowerBound) return aLowerBound;
   if (aA > aUpperBound) return aUpperBound;
   return aA;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Close to

bool dsp_closeto (double aA,double aB,double aResolution)
{
   return (fabs(aA - aB) <= aResolution);
}

bool dsp_closeto (double aA,double aB,int aResolution)
{
   switch (aResolution)
   {
      case  6  : return (fabs(aA - aB) <= 1000000.0);
      case  5  : return (fabs(aA - aB) <= 100000.0);
      case  4  : return (fabs(aA - aB) <= 10000.0);
      case  3  : return (fabs(aA - aB) <= 1000.0);
      case  2  : return (fabs(aA - aB) <= 100.0);
      case  1  : return (fabs(aA - aB) <= 10.0);
      case  0  : return (fabs(aA - aB) <= 1.0);
      case -1  : return (fabs(aA - aB) <= 0.1);
      case -2  : return (fabs(aA - aB) <= 0.01);
      case -3  : return (fabs(aA - aB) <= 0.001);
      case -4  : return (fabs(aA - aB) <= 0.0001);
      case -5  : return (fabs(aA - aB) <= 0.00001);
      case -6  : return (fabs(aA - aB) <= 0.000001);
      case -7  : return (fabs(aA - aB) <= 0.0000001);
      case -8  : return (fabs(aA - aB) <= 0.00000001);
      default  : return (fabs(aA - aB) <= 0.01);
   }
   return false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Round to nearest integer

int dsp_round (double aA)
{
   return lround(aA);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate binomial coefficints.

int dsp_binomial(int aN, int aK)
{
   // Guard.
   if (aK >  aN) return 0; 
   if (aN < 0)   return 0; 
   if (aK < 0)   return 0; 

   // Return recursive sum.
   if (aK == 0)  return 1;
   if (aK == aN) return 1;
   return dsp_binomial(aN - 1, aK - 1) + dsp_binomial(aN - 1, aK);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate two raised to the Nth.

int dsp_two_to_the(int aN)
{
   if (aN==0) return 1;

   int tA = 2;
   for (int i=1;i<=aN-1;i++) tA *= 2;
   return tA;
}

