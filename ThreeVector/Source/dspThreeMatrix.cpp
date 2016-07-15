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
#include "dspThreeMatrix.h"

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// 
ThreeMatrix::ThreeMatrix()
{
   mValues[0] = 0.0;
   mValues[1] = 0.0;
   mValues[2] = 0.0;
}

ThreeMatrix::ThreeMatrix(double aV1,double aV2,double aV3)
{
   mValues[0] = aV1;
   mValues[1] = aV2;
   mValues[2] = aV3;
}

ThreeMatrix::ThreeMatrix(const double* aValues)
{
   for (int i=0;i<3;i++) mValues[i] = aValues[i];
}


//******************************************************************************
//******************************************************************************
//******************************************************************************

void ThreeMatrix::set(double aV1,double aV2,double aV3)
{
   mValues[0] = aV1;
   mValues[1] = aV2;
   mValues[2] = aV3;
}

void ThreeMatrix::set(const double* aValues)
{
   for (int i=0;i<3;i++) mValues[i] = aValues[i];
}

void ThreeMatrix::setZero()
{
   for (int i=0;i<3;i++) mValues[i] = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Access components.

double& ThreeMatrix::e (int aRow)
{
   return mValues[aRow-1];
}

double& ThreeMatrix::operator() (int aRow)
{
   return mValues[aRow-1];
}

double ThreeMatrix::get(int aRow) const
{
   return mValues[aRow-1];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void ThreeMatrix::show(char* aLabel)
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

// Length of a matrix
double ThreeMatrix::length()
{
   double tSum=0.0;

   for (int i=1; i<=3; i++)
   {
      tSum += e(i) * e(i);
   }

   return sqrt(tSum);
}

// Return a normalized matrix
ThreeMatrix ThreeMatrix::normalize()
{
   double tLength = this->length();
   if (tLength==0.0) return *this;
   return *this/tLength;
}

void ThreeMatrix::setNormalize()
{
   double tLength = length();
   for (int i=0; i<3; i++) mValues[i] /= tLength;
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Scalar multiply, divide

ThreeMatrix operator*(double aLeft, const ThreeMatrix& aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      tMatrix.e(i) = aLeft*aRight.get(i);
   }

   return tMatrix;
}

ThreeMatrix operator*(const ThreeMatrix& aLeft,double aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      tMatrix.e(i) = aLeft.get(i)*aRight;
   }

   return tMatrix;
}

ThreeMatrix operator/(const ThreeMatrix& aLeft,double aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      tMatrix.e(i) = aLeft.get(i)/aRight;
   }

   return tMatrix;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Matrix sum, difference

// Add two matrices
ThreeMatrix operator+(const ThreeMatrix& aLeft,const ThreeMatrix& aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      tMatrix.e(i) = aLeft.get(i) + aRight.get(i);
   }

   return tMatrix;
}

// Subtract two matrices
ThreeMatrix operator-(const ThreeMatrix& aLeft,const ThreeMatrix& aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      tMatrix.e(i) = aLeft.get(i) - aRight.get(i);
   }

   return tMatrix;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Inner product

double operator*(const ThreeMatrix& aLeft,const ThreeMatrix& aRight)
{
   double tSum=0.0;

   for (int i=1; i<=3; i++)
   {
      tSum += aLeft.get(i) * aRight.get(i);
   }

   return tSum;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

