#pragma once

/*==============================================================================
Description:
My math functions
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

//------------------------------------------------------------------------------
// Arithmentic

// Min,Max
double dsp_fmin (double aA,double aB);
double dsp_fmax (double aA,double aB);

int    dsp_imin (int aA,int aB);
int    dsp_imax (int aA,int aB);

int    dsp_imin_n  (int aN, ...);
int    dsp_imax_n  (int aN, ...);
double dsp_fmin_n  (int aN, ...);
double dsp_fmax_n  (int aN, ...);

int    my_ibound (int aA,int aLowerBound,int aUpperBound);

// Close to
bool dsp_closeto (double aA,double aB,double aResolution);
bool dsp_closeto (double aA,double aB,int aResolution);

// Round to nearest integer
int    dsp_round (double aA);

//------------------------------------------------------------------------------
// Index arithmetic

// Index arithmetic for queues, wraps around
inline int dsp_index_add(int aIndex, int aDelta, int aSize)
{
   aIndex += aDelta;
   if (aIndex >= aSize) aIndex -= aSize;
   return aIndex;

}
inline int dsp_index_sub(int aIndex, int aDelta, int aSize)
{
   aIndex -= aDelta;
   if (aIndex < 0 ) aIndex += aSize;
   return aIndex;

}

//------------------------------------------------------------------------------
// Calculate binomial coefficints.

long long dsp_factorial(long long aN);

long long dsp_binomial(long long aN, long long aK);



//******************************************************************************
//******************************************************************************
//******************************************************************************
