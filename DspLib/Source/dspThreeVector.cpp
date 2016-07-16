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

ThreeVector::ThreeVector(double aV1,double aV2,double aV3)
{
   mValues[0] = aV1;
   mValues[1] = aV2;
   mValues[2] = aV3;
}

ThreeVector::ThreeVector(double aValues[3])
{
   for (int i=0;i<3;i++) mValues[i] = aValues[i];
}

ThreeVector::ThreeVector(int aBasisCoordinate)
{
   switch (aBasisCoordinate)
   {
   case  1: {mValues[0] =  1.0; mValues[1] =  0.0; mValues[2] =  0.0; } break;
   case  2: {mValues[0] =  0.0; mValues[1] =  1.0; mValues[2] =  0.0; } break;
   case  3: {mValues[0] =  0.0; mValues[1] =  0.0; mValues[2] =  1.0; } break;
   case -1: {mValues[0] = -1.0; mValues[1] =  0.0; mValues[2] =  0.0; } break;
   case -2: {mValues[0] =  0.0; mValues[1] = -1.0; mValues[2] =  0.0; } break;
   case -3: {mValues[0] =  0.0; mValues[1] =  0.0; mValues[2] = -1.0; } break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ThreeVector::set(double aV1,double aV2,double aV3)
{
   mValues[0] = aV1;
   mValues[1] = aV2;
   mValues[2] = aV3;
}

void ThreeVector::set(double aValues[3])
{
   for (int i=0;i<3;i++) mValues[i] = aValues[i];
}

void ThreeVector::setToZero()
{
   for (int i=0;i<3;i++) mValues[i] = 0.0;
}

void ThreeVector::setToBasisVector(int aBasisCoordinate)
{
   switch (aBasisCoordinate)
   {
   case  1: {mValues[0] =  1.0; mValues[1] =  0.0; mValues[2] =  0.0; } break;
   case  2: {mValues[0] =  0.0; mValues[1] =  1.0; mValues[2] =  0.0; } break;
   case  3: {mValues[0] =  0.0; mValues[1] =  0.0; mValues[2] =  1.0; } break;
   case -1: {mValues[0] = -1.0; mValues[1] =  0.0; mValues[2] =  0.0; } break;
   case -2: {mValues[0] =  0.0; mValues[1] = -1.0; mValues[2] =  0.0; } break;
   case -3: {mValues[0] =  0.0; mValues[1] =  0.0; mValues[2] = -1.0; } break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Access components.

double& ThreeVector::e (int aRow)
{
   return mValues[aRow-1];
}

double& ThreeVector::operator() (int aRow)
{
   return mValues[aRow-1];
}

double ThreeVector::get(int aRow) const
{
   return mValues[aRow-1];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void ThreeVector::show(char* aLabel)
{
   if (aLabel==0)
   {
      for (int i=1;i<=3;i++)
      {
            printf("%11.6f ",e(i));
      }
      printf("\n");
   }
   else
   {
      printf("%s ",aLabel);
      for (int i=1;i<=3;i++)
      {
         printf("%11.6f ",e(i));
      }
      printf("\n");
   }
   printf("\n");
}

void ThreeVector::show2(char* aLabel)
{
   if (aLabel==0)
   {
      for (int i=1; i<=3; i++) printf("%11.6f\n",e(i));
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

// Length of a vector
double ThreeVector::length()
{
   double tSum=0.0;

   for (int i=1; i<=3; i++)
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

void ThreeVector::setNormalize()
{
   double tLength = length();
   for (int i=0; i<3; i++) mValues[i] /= tLength;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Scalar multiply, divide

ThreeVector operator*(double aLeft, ThreeVector& aRight)
{
   ThreeVector tVector;

   for (int i=1; i<=3; i++)
   {
      tVector(i) = aLeft*aRight(i);
   }

   return tVector;
}

ThreeVector operator*(ThreeVector& aLeft,double aRight)
{
   ThreeVector tVector;

   for (int i=1; i<=3; i++)
   {
      tVector(i) = aLeft(i)*aRight;
   }

   return tVector;
}

ThreeVector operator/(ThreeVector& aLeft,double aRight)
{
   ThreeVector tVector;

   for (int i=1; i<=3; i++)
   {
      tVector(i) = aLeft(i)/aRight;
   }

   return tVector;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Vector sum, difference

// Add two vectors
ThreeVector operator+(ThreeVector& aLeft,ThreeVector& aRight)
{
   ThreeVector tVector;

   for (int i=1; i<=3; i++)
   {
      tVector(i) = aLeft(i) + aRight(i);
   }

   return tVector;
}

// Subtract two vectors
ThreeVector operator-(ThreeVector& aLeft,ThreeVector& aRight)
{
   ThreeVector tVector;

   for (int i=1; i<=3; i++)
   {
      tVector(i) = aLeft(i) - aRight(i);
   }

   return tVector;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Inner product

double operator*(ThreeVector& aLeft,ThreeVector& aRight)
{
   double tSum=0.0;

   for (int i=1; i<=3; i++)
   {
      tSum += aLeft(i) * aRight(i);
   }

   return tSum;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Cross product

ThreeVector cross(ThreeVector& aLeft,ThreeVector& aRight)
{
   ThreeVector tVector(
      (aLeft(2)*aRight(3) - aRight(2)*aLeft(3)),
     -(aLeft(1)*aRight(3) - aRight(1)*aLeft(3)),
      (aLeft(1)*aRight(2) - aRight(1)*aLeft(2)));

   return tVector;
}

ThreeVector operator&(ThreeVector& aLeft,ThreeVector& aRight)
{
   ThreeVector tVector(
      (aLeft(2)*aRight(3) - aRight(2)*aLeft(3)),
     -(aLeft(1)*aRight(3) - aRight(1)*aLeft(3)),
      (aLeft(1)*aRight(2) - aRight(1)*aLeft(2)));

   return tVector;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

