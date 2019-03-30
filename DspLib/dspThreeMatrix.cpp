/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dsp_math.h"
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
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         mValues[i][j] = 0.0;
      }
   }
}

ThreeMatrix::ThreeMatrix(
   double aA11,double aA12,double aA13,
   double aA21,double aA22,double aA23,
   double aA31,double aA32,double aA33)
{
   e(1,1) = aA11; e(1,2) = aA12; e(1,3) = aA13;
   e(2,1) = aA21; e(2,2) = aA22; e(2,3) = aA23;
   e(3,1) = aA31; e(3,2) = aA32; e(3,3) = aA33;
}

ThreeMatrix::ThreeMatrix(double aValues[3][3])
{
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         mValues[i][j] = aValues[i][j];
      }
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ThreeMatrix::set(
   double aA11,double aA12,double aA13,
   double aA21,double aA22,double aA23,
   double aA31,double aA32,double aA33)
{
   e(1,1) = aA11; e(1,2) = aA12; e(1,3) = aA13;
   e(2,1) = aA21; e(2,2) = aA22; e(2,3) = aA23;
   e(3,1) = aA31; e(3,2) = aA32; e(3,3) = aA33;
}


void ThreeMatrix::set(double aValues[3][3])
{
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         mValues[i][j] = aValues[i][j];
      }
   }
}

void ThreeMatrix::setToZero()
{
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         mValues[i][j] = 0.0;
      }
   }
}

void ThreeMatrix::setIdentity()
{
   setToZero();
   e(1,1) = 1.0;
   e(2,2) = 1.0;
   e(3,3) = 1.0;
}

void ThreeMatrix::setDiagonal(double aA11,double aA22, double aA33)
{
   setToZero();
   e(1,1) = aA11;
   e(2,2) = aA22;
   e(3,3) = aA33;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Access components.

double& ThreeMatrix::e (int aRow,int aCol)
{
   return mValues[aRow-1][aCol-1];
}

double& ThreeMatrix::operator() (int aRow,int aCol)
{
   return mValues[aRow-1][aCol-1];
}

double ThreeMatrix::get(int aRow,int aCol) const
{
   return mValues[aRow-1][aCol-1];
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void ThreeMatrix::show(char* aLabel)
{
   if (aLabel==0)
   {
      for (int i=1;i<=3;i++)
      {
         for (int j=1;j<=3;j++)
         {
            printf("%11.6f ",e(i,j));
         }
         printf("\n");
      }
   }
   else
   {
      for (int i=1;i<=3;i++)
      {
         printf("%-10s ",aLabel);
         for (int j=1;j<=3;j++)
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
// Transpose

ThreeMatrix ThreeMatrix::transpose()
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      double tSum = 0.0;
      for (int j = 1; j <= 3; j++)
      {
         tMatrix(i,j) = get(j,i);
      }
   }

   return tMatrix;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Trace

double ThreeMatrix::trace()
{
   return e(1,1) + e(2,2) + e(3,3);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get rows and columns

ThreeVector ThreeMatrix::getRow(int aRow)
{
   ThreeVector tVector;

   for (int i=1; i<=3; i++)
   {
      tVector(i) = get(aRow,i);
   }

   return tVector;
}

ThreeVector ThreeMatrix::getCol(int aCol)
{
   ThreeVector tVector;

   for (int i=1; i<=3; i++)
   {
      tVector(i) = get(i,aCol);
   }

   return tVector;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void ThreeMatrix::setRotateX(double aAngle)
{
   double tS = sin(aAngle);
   double tC = cos(aAngle);

   set( 1.0, 0.0, 0.0,
        0.0,  tC, -tS,
        0.0,  tS,  tC);
}

void ThreeMatrix::setRotateY(double aAngle)
{
   double tS = sin(aAngle);
   double tC = cos(aAngle);

   set( tC, 0.0,  tS,
       0.0, 1.0, 0.0,
       -tS, 0.0,  tC);
}

void ThreeMatrix::setRotateZ(double aAngle)
{
   double tS = sin(aAngle);
   double tC = cos(aAngle);

   set( tC, -tS, 0.0,
        tS,  tC, 0.0,
       0.0, 0.0, 1.0);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Scalar multiply, divide

ThreeMatrix operator*(const double aLeft, const ThreeMatrix& aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      for (int j = 1; j <= 3; j++)
      {
         tMatrix(i, j) = aLeft*aRight.get(i, j);
      }
   }

   return tMatrix;
}

ThreeMatrix operator*(const ThreeMatrix& aLeft, const double aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      for (int j = 1; j <= 3; j++)
      {
         tMatrix(i, j) = aLeft.get(i, j)*aRight;
      }
   }

   return tMatrix;
}

ThreeMatrix operator/(const ThreeMatrix& aLeft, const double aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      for (int j = 1; j <= 3; j++)
      {
         tMatrix(i, j) = aLeft.get(i, j) / aRight;
      }
   }

   return tMatrix;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Matrix sum, difference

// Add two matrices
ThreeMatrix operator+(const ThreeMatrix& aLeft, const ThreeMatrix& aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      for (int j = 1; j <= 3; j++)
      {
         tMatrix(i, j) = aLeft.get(i, j) + aRight.get(i, j);
      }
   }

   return tMatrix;
}

// Subtract two matrices
ThreeMatrix operator-(const ThreeMatrix& aLeft, const ThreeMatrix& aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      for (int j = 1; j <= 3; j++)
      {
         tMatrix(i, j) = aLeft.get(i, j) - aRight.get(i, j);
      }
   }

   return tMatrix;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Matrix multiply

// Multiply a matrix and a vector
ThreeVector operator*(const ThreeMatrix& aLeft, const ThreeVector& aRight)
{
   ThreeVector tVector;

   for (int i=1; i<=3; i++)
   {
      double tSum = 0.0;
      for (int j = 1; j <= 3; j++)
      {
          tSum += aLeft.get(i, j)*aRight.get(j);
      }
      tVector(i) = tSum;
   }

   return tVector;
}

// Multiply a matrix and a matrix
ThreeMatrix operator*(const ThreeMatrix& aLeft, const ThreeMatrix& aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      for (int j = 1; j <= 3; j++)
      {
         double tSum = 0.0;
         for (int k = 1; k <= 3; k++)
         {
            tSum += aLeft.get(i, k)*aRight.get(k, j);
         }
         tMatrix(i,j) = tSum;
      }
   }

   return tMatrix;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Transpose

ThreeMatrix transpose(ThreeMatrix& aA)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      double tSum = 0.0;
      for (int j = 1; j <= 3; j++)
      {
         tMatrix(i,j) = aA(j,i);
      }
   }

   return tMatrix;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Identity

ThreeMatrix identity()
{
   ThreeMatrix tMatrix;
   tMatrix(1,1) = 1.0;
   tMatrix(2,2) = 1.0;
   tMatrix(3,3) = 1.0;
   return tMatrix;
}

ThreeMatrix diagonal(double aA11,double aA22,double aA33)
{
   ThreeMatrix tMatrix;
   tMatrix(1,1) = aA11;
   tMatrix(2,2) = aA22;
   tMatrix(3,3) = aA33;
   return tMatrix;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Rotation matrices

ThreeMatrix rotateX(double aAngle)
{
   ThreeMatrix tMatrix;
   tMatrix.setRotateX(aAngle);
   return tMatrix;
}

ThreeMatrix rotateY(double aAngle)
{
   ThreeMatrix tMatrix;
   tMatrix.setRotateY(aAngle);
   return tMatrix;
}

ThreeMatrix rotateZ(double aAngle)
{
   ThreeMatrix tMatrix;
   tMatrix.setRotateZ(aAngle);
   return tMatrix;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

