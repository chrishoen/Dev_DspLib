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
#include "my_functions.h"

#include "dspRVector.h"

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

RVector::RVector()
{
   mRows   = 0;
   mValues = 0;
}

RVector::RVector(int aRows)
{
   initialize(aRows);
}

RVector::RVector(const RVector& aOther)
{
   mRows   = aOther.mRows;
   int tAlloc = mRows;
   mValues = new double[tAlloc];
   for (int i=1;i<=mRows;i++) mValues[i-1]=aOther.mValues[i-1];
}

RVector& RVector::operator=(const RVector& aOther)
{
   mRows   = aOther.mRows;
   int tAlloc = mRows;
   if (mValues==0)
   {
      mValues = new double[tAlloc];
   }
   for (int i=1;i<=mRows;i++) mValues[i-1]=aOther.mValues[i-1];
   return *this;
}

RVector::~RVector()
{
   if (mValues) delete mValues;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void RVector::initialize(
      int     aRows)

{
   mRows   = aRows;
   int tAlloc = mRows;
   mValues = new double[tAlloc];
   for (int i=1;i<=mRows;i++) mValues[i-1]=0.0;
}

void RVector::initialize(
      int     aRows,
      double* aValues)
{
   mRows   = aRows;
   int tAlloc = mRows;
   mValues = new double[tAlloc];
   for (int i=1;i<=mRows;i++) mValues[i-1]=aValues[i-1];
}

void RVector::reset()
{
   for (int i=1;i<=mRows;i++) mValues[i-1]=0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

double& RVector::e (int aRow)
{
   return mValues[aRow-1];
}

double& RVector::operator() (int aRow)
{
   return mValues[aRow-1];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void RVector::show(char* aLabel)
{
   if (aLabel==0)
   {
      for (int i=1;i<=mRows;i++) printf("%10.8f\n",e(i));
   }
   else
   {
      for (int i=1;i<=mRows;i++) printf("%s %10.8f\n", aLabel,e(i));
   }
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Add two vectors
RVector RVector::operator+(RVector& aRight)
{
   RVector tVector(mRows);

   for (int i=1;i<=mRows;i++)
   {
      tVector.e(i) = e(i) + aRight.e(i);
   }

   return tVector;
}

// Subtract two vectors
RVector RVector::operator-(RVector& aRight)
{
   RVector tVector(mRows);

   for (int i=1;i<=mRows;i++)
   {
      tVector.e(i) = e(i) - aRight.e(i);
   }

   return tVector;
}

// Multiply a vector by a scalar
RVector RVector::operator*(double aRight)
{
   RVector tVector(mRows);

   for (int i=1;i<=mRows;i++)
   {
      tVector.e(i) = e(i) * aRight;
   }

   return tVector;
}

// Divide a vector by a scalar
RVector RVector::operator/(double aRight)
{
   RVector tVector(mRows);

   for (int i=1;i<=mRows;i++)
   {
      tVector.e(i) = e(i) / aRight;
   }

   return tVector;
}

// Inner product of two vectors
double RVector::operator*(RVector& aRight)
{
   double tSum=0.0;

   for (int i=1;i<=mRows;i++)
   {
      tSum += e(i) * aRight.e(i);
   }

   return tSum;
}

// Length of a vector
double RVector::length()
{
   double tSum=0.0;

   for (int i=1;i<=mRows;i++)
   {
      tSum += e(i) * e(i);
   }

   return sqrt(tSum);
}

// Return a normalized vector
RVector RVector::normalize()
{
   return *this/this->length();
}

// Compare two vectors for equality
bool RVector::isCloseTo(RVector& aRight,double aThreshold)
{
   return (*this-aRight).length() < aThreshold;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

RMatrix::RMatrix()
{
   mRows   = 0;
   mCols   = 0;
   mValues = 0;
}

RMatrix::~RMatrix()
{
   if (mValues) delete mValues;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void RMatrix::initialize(
      int     aRows,
      int     aCols,
      double* aValues)
{
   mRows   = aRows;
   mCols   = aCols;
   int tAlloc = mRows*mCols;
   mValues = new double[tAlloc];
   for (int i=0;i<tAlloc;i++) mValues[i]=aValues[i];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

double& RMatrix::e (int aRow,int aCol)
{
   int tIndex = (aRow-1)*mCols + (aCol-1);
   return mValues[tIndex];
}

double& RMatrix::operator() (int aRow,int aCol)
{
   int tIndex = (aRow-1)*mCols + (aCol-1);
   return mValues[tIndex];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void RMatrix::show(char* aLabel)
{
   if (aLabel==0)
   {
      for (int i=1;i<=mRows;i++)
      {
         for (int j=1;j<=mCols;j++)
         {
            printf("%10.8f ",e(i,j));
         }
         printf("\n");
      }
   }
   else
   {
      for (int i=1;i<=mRows;i++)
      {
         printf("%s ",aLabel);
         for (int j=1;j<=mCols;j++)
         {
            printf("%10.8f ",e(i,j));
         }
         printf("\n");
      }
   }
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Matrix Vector multiply
RVector RMatrix::operator*(RVector& aRight)
{
   RVector tVector(mRows);

   for (int i=1;i<=mRows;i++)
   {
      double tSum=0.0;
      for (int j=1;j<=mCols;j++)
      {
         tSum += e(i,j) * aRight.e(j);
      }
      tVector.e(i) = tSum;
   }

   return tVector;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Vector add
void add (RVector& aY, RVector& aX1, RVector& aX2)
{
   for (int i=1;i<=aY.mRows;i++)
   {
      aY.e(i) = aX1.e(i) + aX2.e(i);
   }
}

// Vector add
void addTo (RVector& aY, RVector& aX)
{
   for (int i=1;i<=aY.mRows;i++)
   {
      aY.e(i) += aX.e(i);
   }
}

// Vector subtract
void subtract (RVector& aY, RVector& aX1, RVector& aX2)
{
   for (int i=1;i<=aY.mRows;i++)
   {
      aY.e(i) = aX1.e(i) - aX2.e(i);
   }
}

// Vector subtract
void subtractFrom (RVector& aY, RVector& aX)
{
   for (int i=1;i<=aY.mRows;i++)
   {
      aY.e(i) -= aX.e(i);
   }
}

// Vector multiply
void multiply  (RVector& aY, RVector& aX, double aA)
{
   for (int i=1;i<=aY.mRows;i++)
   {
      aY.e(i) = aX.e(i) * aA;
   }
}

// Matrix Vector multiply
void multiply (RVector& aY, RMatrix& aA, RVector& aX)
{
   for (int i=1;i<=aA.mRows;i++)
   {
      double tSum = 0.0;
      for (int j=1;j<=aA.mCols;j++)
      {
         tSum += aA.e(i,j) * aX.e(j);
      }
      aY.e(i) = tSum;
   }
}

}//namespace

