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

ThreeMatrix::ThreeMatrix(const double aValues[3][3])
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


void ThreeMatrix::set(const double aValues[3][3])
{
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         mValues[i][j] = aValues[i][j];
      }
   }
}

void ThreeMatrix::setZero()
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
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         if (i == j)
         {
            mValues[i][j] = 1.0;
         }
         else
         {
            mValues[i][j] = 0.0;
         }
      }
   }
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
         printf("%s ",aLabel);
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
// Scalar multiply, divide

ThreeMatrix operator*(double aLeft, const ThreeMatrix& aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      for (int j = 1; j <= 3; j++)
      {
         tMatrix.e(i, j) = aLeft*aRight.get(i, j);
      }
   }

   return tMatrix;
}

ThreeMatrix operator*(const ThreeMatrix& aLeft,double aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      for (int j = 1; j <= 3; j++)
      {
         tMatrix.e(i, j) = aLeft.get(i, j)*aRight;
      }
   }

   return tMatrix;
}

ThreeMatrix operator/(const ThreeMatrix& aLeft,double aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      for (int j = 1; j <= 3; j++)
      {
         tMatrix.e(i, j) = aLeft.get(i, j) / aRight;
      }
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
      for (int j = 1; j <= 3; j++)
      {
         tMatrix.e(i, j) = aLeft.get(i, j) + aRight.get(i, j);
      }
   }

   return tMatrix;
}

// Subtract two matrices
ThreeMatrix operator-(const ThreeMatrix& aLeft,const ThreeMatrix& aRight)
{
   ThreeMatrix tMatrix;

   for (int i=1; i<=3; i++)
   {
      for (int j = 1; j <= 3; j++)
      {
         tMatrix.e(i, j) = aLeft.get(i, j) - aRight.get(i, j);
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
}//namespace

