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

ThreeMatrix::ThreeMatrix()
{
   mRows   = 0;
   mCols   = 0;
   mValues = 0;
}

ThreeMatrix::~ThreeMatrix()
{
   if (mValues) delete mValues;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ThreeMatrix::initialize(
      int     aRows,
      int     aCols)
{
   mRows   = aRows;
   mCols   = aCols;
   int tAlloc = mRows*mCols;
   mValues = new double[tAlloc];
   for (int i = 0; i < tAlloc; i++) mValues[i] = 0.0;
}

void ThreeMatrix::initialize(
      int     aRows,
      int     aCols,
      double* aValues)
{
   mRows   = aRows;
   mCols   = aCols;
   int tAlloc = mRows*mCols;
   mValues = new double[tAlloc];
   for (int i = 0; i < tAlloc; i++) mValues[i] = aValues[i];
}

void ThreeMatrix::reset()
{
   int tAlloc = mRows*mCols;
   for (int i = 0; i < tAlloc; i++) mValues[i] = 0.0;
}

void ThreeMatrix::setValues(
      double* aValues)
{
   int tAlloc = mRows*mCols;
   for (int i = 0; i < tAlloc; i++) mValues[i] = aValues[i];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

double& ThreeMatrix::e (int aRow,int aCol)
{
   int tIndex = (aRow-1)*mCols + (aCol-1);
   return mValues[tIndex];
}

double& ThreeMatrix::operator() (int aRow,int aCol)
{
   int tIndex = (aRow-1)*mCols + (aCol-1);
   return mValues[tIndex];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ThreeMatrix::show(char* aLabel)
{
   if (aLabel==0)
   {
      for (int i=1;i<=mRows;i++)
      {
         for (int j=1;j<=mCols;j++)
         {
            printf("%11.6f ",e(i,j));
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
            printf("%11.6f ",e(i,j));
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
ThreeVector ThreeMatrix::operator*(ThreeVector& aRight)
{
   ThreeVector tVector(mRows);

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

void ThreeMatrix::setRotateX(double aAngle)
{
   if (mRows != 3) return;
   if (mCols != 3) return;

   double tS = dsp_sin_deg(aAngle);
   double tC = dsp_cos_deg(aAngle);

   double tV[3][3] = {{ 1.0, 0.0, 0.0},
                      { 0.0,  tC, -tS},
                      { 0.0,  tS,  tC}};

   setValues(&tV[0][0]);
}

void ThreeMatrix::setRotateY(double aAngle)
{
   if (mRows != 3) return;
   if (mCols != 3) return;

   double tS = dsp_sin_deg(aAngle);
   double tC = dsp_cos_deg(aAngle);

   double tV[3][3] = {{  tC, 0.0,  tS},
                      { 0.0, 1.0, 0.0},
                      { -tS, 0.0,  tC}};

   setValues(&tV[0][0]);
}

void ThreeMatrix::setRotateZ(double aAngle)
{
   if (mRows != 3) return;
   if (mCols != 3) return;

   double tS = dsp_sin_deg(aAngle);
   double tC = dsp_cos_deg(aAngle);

   double tV[3][3] = {{  tC, -tS, 0.0},
                      {  tS,  tC, 0.0},
                      { 0.0, 0.0, 1.0}};

   setValues(&tV[0][0]);
}
//******************************************************************************
//******************************************************************************
//******************************************************************************

// Vector add
void add (ThreeVector& aY, ThreeVector& aX1, ThreeVector& aX2)
{
   for (int i=1;i<=aY.mRows;i++)
   {
      aY.e(i) = aX1.e(i) + aX2.e(i);
   }
}

// Vector add
void addTo (ThreeVector& aY, ThreeVector& aX)
{
   for (int i=1;i<=aY.mRows;i++)
   {
      aY.e(i) += aX.e(i);
   }
}

// Vector subtract
void subtract (ThreeVector& aY, ThreeVector& aX1, ThreeVector& aX2)
{
   for (int i=1;i<=aY.mRows;i++)
   {
      aY.e(i) = aX1.e(i) - aX2.e(i);
   }
}

// Vector subtract
void subtractFrom (ThreeVector& aY, ThreeVector& aX)
{
   for (int i=1;i<=aY.mRows;i++)
   {
      aY.e(i) -= aX.e(i);
   }
}

// Vector multiply
void multiply  (ThreeVector& aY, ThreeVector& aX, double aA)
{
   for (int i=1;i<=aY.mRows;i++)
   {
      aY.e(i) = aX.e(i) * aA;
   }
}

// Matrix Vector multiply
void multiply (ThreeVector& aY, ThreeMatrix& aA, ThreeVector& aX)
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

//******************************************************************************
//******************************************************************************
//******************************************************************************

// Matrix Matrix add
void add (ThreeMatrix& aC, ThreeMatrix& aA, ThreeMatrix& aB)
{
   if (aA.mRows != aA.mCols) return;
   if (aB.mRows != aB.mCols) return;
   if (aC.mRows != aC.mCols) return;
   if (aA.mRows != aB.mRows) return;
   if (aA.mRows != aC.mRows) return;

   int tN = aA.mRows;
   for (int i = 1; i <= tN; i++)
   {
      for (int j = 1; j <= tN; j++)
      {
         aC.e(i, j) = aA.e(i, j) * aB.e(i, j);
      }
   }
}

// Matrix Matrix multiply
void multiply (ThreeMatrix& aC, ThreeMatrix& aA, ThreeMatrix& aB)
{
   if (aA.mRows != aA.mCols) return;
   if (aB.mRows != aB.mCols) return;
   if (aC.mRows != aC.mCols) return;
   if (aA.mRows != aB.mRows) return;
   if (aA.mRows != aC.mRows) return;

   int tN = aA.mRows;
   for (int i = 1; i <= tN; i++)
   {
      for (int j = 1; j <= tN; j++)
      {
         double tSum = 0.0;
         for (int k = 1; k <= tN; k++)
         {
            tSum += aA.e(i, k) * aB.e(k, j);
         }
         aC.e(i, j) = tSum;
      }
   }
}

// Matrix Transpose 
void transpose (ThreeMatrix& aC, ThreeMatrix& aA)
{
   if (aA.mRows != aA.mCols) return;
   if (aC.mRows != aC.mCols) return;
   if (aA.mRows != aC.mRows) return;

   int tN = aA.mRows;
   for (int i = 1; i <= tN; i++)
   {
      for (int j = 1; j <= tN; j++)
      {
         aC.e(i, j) = aA.e(j, i);
      }
   }
}



}//namespace

