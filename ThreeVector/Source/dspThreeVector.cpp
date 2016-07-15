/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "dsp_trig_functions.h"
#include "dspThreeVector.h"

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// 
ThreeVector::ThreeVector()
{
   mValues[0] = 0.0;
   mValues[1] = 0.0;
   mValues[2] = 0.0;
}


ThreeVector::ThreeVector(const double* aValues)
{
   for (int i=0;i<3;i++) mValues[i] = aValues[i];
}


//******************************************************************************
//******************************************************************************
//******************************************************************************

void ThreeVector::setValues(const double* aValues)
{
   for (int i=0;i<3;i++) mValues[i] = aValues[i];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

double& ThreeVector::e (int aRow)
{
   return mValues[aRow-1];
}

double& ThreeVector::operator() (int aRow)
{
   return mValues[aRow-1];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ThreeVector::show(char* aLabel)
{
   if (aLabel==0)
   {
      for (int i = 1; i <= 3; i++) printf("%11.6f\n",e(i));
   }
   else
   {
      for (int i=1 ; i <= 3; i++) printf("%s %11.6f\n", aLabel,e(i));
   }
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Add two vectors
ThreeVector ThreeVector::operator+(ThreeVector& aRight)
{
   ThreeVector tVector;

   for (int i = 1; i <= 3; i++)
   {
      tVector.e(i) = e(i) + aRight.e(i);
   }

   return tVector;
}

// Subtract two vectors
ThreeVector ThreeVector::operator-(ThreeVector& aRight)
{
   ThreeVector tVector;

   for (int i = 1; i <= 3; i++)
   {
      tVector.e(i) = e(i) - aRight.e(i);
   }

   return tVector;
}

// Multiply a vector by a scalar
ThreeVector ThreeVector::operator*(double aRight)
{
   ThreeVector tVector;

   for (int i = 1; i <= 3; i++)
   {
      tVector.e(i) = e(i) * aRight;
   }

   return tVector;
}

// Divide a vector by a scalar
ThreeVector ThreeVector::operator/(double aRight)
{
   ThreeVector tVector;

   for (int i = 1; i <= 3; i++)
   {
      tVector.e(i) = e(i) / aRight;
   }

   return tVector;
}

// Inner product of two vectors
double ThreeVector::operator*(ThreeVector& aRight)
{
   double tSum=0.0;

   for (int i = 1; i <= 3; i++)
   {
      tSum += e(i) * aRight.e(i);
   }

   return tSum;
}

// Length of a vector
double ThreeVector::length()
{
   double tSum=0.0;

   for (int i = 1; i <= 3; i++)
   {
      tSum += e(i) * e(i);
   }

   return sqrt(tSum);
}

// Return a normalized vector
ThreeVector ThreeVector::normalize()
{
   double tLength = this->length();
   if (tLength==0.0) return *this;
   return *this/tLength;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

