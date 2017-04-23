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
#include <stdarg.h>
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

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Min,Max

int dsp_imin_n(int aN, ...)
{
    va_list ap;
    int a;

    va_start(ap, aN);
    for (int i = 0; i < aN; i++)
    {
       int x = va_arg(ap, int);
       if (i==0) a = x;
       else      a = dsp_imin(a,x);
    }
    va_end(ap);
    return a;
}

int dsp_imax_n(int aN, ...)
{
    va_list ap;
    int a;

    va_start(ap, aN);
    for (int i = 0; i < aN; i++)
    {
       int x = va_arg(ap, int);
       if (i==0) a = x;
       else      a = dsp_imax(a,x);
    }
    va_end(ap);
    return a;
}

double dsp_fmin_n(int aN, ...)
{
    va_list ap;
    double a;

    va_start(ap, aN);
    for (int i = 0; i < aN; i++)
    {
       double x = va_arg(ap, double);
       if (i==0) a = x;
       else      a = dsp_fmin(a,x);
    }
    va_end(ap);
    return a;
}

double dsp_fmax_n(int aN, ...)
{
    va_list ap;
    double a;

    va_start(ap, aN);
    for (int i = 0; i < aN; i++)
    {
       double x = va_arg(ap, double);
       if (i==0) a = x;
       else      a = dsp_fmax(a,x);
    }
    va_end(ap);
    return a;
}
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Min,Max

int    dsp_ibound(int aA, int aLowerBound, int aUpperBound)
{
   if (aA < aLowerBound) return aLowerBound;
   if (aA > aUpperBound) return aUpperBound;
   return aA;
}

bool dsp_is_inbounds(int aA, int aLowerBound, int aUpperBound)
{
   if (aA < aLowerBound) return false;
   if (aA > aUpperBound) return false;
   return true;
}

bool dsp_is_inbounds(double aA, double aLowerBound, double aUpperBound)
{
   if (aA < aLowerBound) return false;
   if (aA > aUpperBound) return false;
   return true;
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

long long dsp_factorial(long long aN)
{
   // Guard.
   if (aN<=0) return 1; 

   long long tA = 1;

   for (long long i = 1; i <= aN; i++)
   {
      tA *= i;
   }
   return tA;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate binomial coefficints.

long long dsp_binomial(long long aN, long long aK)
{
   // Guard.
   if (aK >  aN) return 0; 
   if (aK < 0) return 0; 
   if (aN < 0) return 0; 

   long long tA = 1;
   long long tF = 1;

   for (long long i = 1; i <= aK; i++)
   {
      tA *= (aN + 1 - i);
      tF *= i;
   }
   return tA/tF;
}

