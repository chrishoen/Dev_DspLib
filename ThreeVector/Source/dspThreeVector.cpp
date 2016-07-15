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

ThreeVector::ThreeVector()
{
   mRows   = 0;
   mValues = 0;
}

ThreeVector::ThreeVector(int aRows)
{
   initialize(aRows);
}

ThreeVector::ThreeVector(const ThreeVector& aOther)
{
   mRows   = aOther.mRows;
   int tAlloc = mRows;
   mValues = new double[tAlloc];
   for (int i=1;i<=mRows;i++) mValues[i-1]=aOther.mValues[i-1];
}

ThreeVector& ThreeVector::operator=(const ThreeVector& aOther)
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

ThreeVector::~ThreeVector()
{
   if (mValues) delete mValues;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ThreeVector::initialize(
      int     aRows)
{
   mRows   = aRows;
   int tAlloc = mRows;
   mValues = new double[tAlloc];
   for (int i = 0; i < tAlloc; i++) mValues[i] = 0.0;
}

void ThreeVector::initialize(
      int     aRows,
      double* aValues)
{
   mRows   = aRows;
   int tAlloc = mRows;
   mValues = new double[tAlloc];
   for (int i = 0; i < tAlloc; i++) mValues[i] = aValues[i];
}

void ThreeVector::reset()
{
   int tAlloc = mRows;
   for (int i = 0; i < tAlloc; i++) mValues[i] = 0.0;
}

void ThreeVector::setValues(
      double* aValues)
{
   int tAlloc = mRows;
   for (int i = 0; i < tAlloc; i++) mValues[i] = aValues[i];
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
      for (int i=1;i<=mRows;i++) printf("%11.6f\n",e(i));
   }
   else
   {
      for (int i=1;i<=mRows;i++) printf("%s %11.6f\n", aLabel,e(i));
   }
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Add two vectors
ThreeVector ThreeVector::operator+(ThreeVector& aRight)
{
   ThreeVector tVector(mRows);

   for (int i=1;i<=mRows;i++)
   {
      tVector.e(i) = e(i) + aRight.e(i);
   }

   return tVector;
}

// Subtract two vectors
ThreeVector ThreeVector::operator-(ThreeVector& aRight)
{
   ThreeVector tVector(mRows);

   for (int i=1;i<=mRows;i++)
   {
      tVector.e(i) = e(i) - aRight.e(i);
   }

   return tVector;
}

// Multiply a vector by a scalar
ThreeVector ThreeVector::operator*(double aRight)
{
   ThreeVector tVector(mRows);

   for (int i=1;i<=mRows;i++)
   {
      tVector.e(i) = e(i) * aRight;
   }

   return tVector;
}

// Divide a vector by a scalar
ThreeVector ThreeVector::operator/(double aRight)
{
   ThreeVector tVector(mRows);

   for (int i=1;i<=mRows;i++)
   {
      tVector.e(i) = e(i) / aRight;
   }

   return tVector;
}

// Inner product of two vectors
double ThreeVector::operator*(ThreeVector& aRight)
{
   double tSum=0.0;

   for (int i=1;i<=mRows;i++)
   {
      tSum += e(i) * aRight.e(i);
   }

   return tSum;
}

// Length of a vector
double ThreeVector::length()
{
   double tSum=0.0;

   for (int i=1;i<=mRows;i++)
   {
      tSum += e(i) * e(i);
   }

   return sqrt(tSum);
}

// Return a normalized vector
ThreeVector ThreeVector::normalize()
{
   return *this/this->length();
}

// Compare two vectors for equality
bool ThreeVector::isCloseTo(ThreeVector& aRight,double aThreshold)
{
   return (*this-aRight).length() < aThreshold;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

