#pragma once

/*==============================================================================
Matrixs and matrices on R3.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspThreeVector.h"

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class ThreeMatrix
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Matrix components.
   double mValues[3][3];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   ThreeMatrix();
   ThreeMatrix(
      double aA11,double aA12,double aA13,
      double aA21,double aA22,double aA23,
      double aA31,double aA32,double aA33);
   ThreeMatrix(double aValues[3][3]);

   // Assign values.
   void set(
      double aA11,double aA12,double aA13,
      double aA21,double aA22,double aA23,
      double aA31,double aA32,double aA33);
   void set(double aValues[3][3]);
   void setToZero();
   void setIdentity();
   void setDiagonal(double aA11,double aA22, double aA33);

   // Access components.
   double& e(int aRow,int aCol);
   double& operator()(int aRow,int aCol);
   double get(int aRow,int aCol) const;
   void show(char* aLabel=0);

   // Get rows and columns.
   ThreeVector getRow(int aRow);
   ThreeVector getCol(int aCol);

   // Transpose
   ThreeMatrix transpose();

   // Trace.
   double trace();

   // Set to a rotation matrix.
   void setRotateX   (double aAngle);
   void setRotateY   (double aAngle);
   void setRotateZ   (double aAngle);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators

// Scalar multilply, divide.
ThreeMatrix operator*(const double aLeft, const ThreeMatrix& aRight);
ThreeMatrix operator*(const ThreeMatrix& aLeft, const double aRight);
ThreeMatrix operator/(const ThreeMatrix& aLeft, const double aRight);

// Matrix sum, difference.
ThreeMatrix operator+(const ThreeMatrix& aLeft, const ThreeMatrix& aRight);
ThreeMatrix operator-(const ThreeMatrix& aLeft, const ThreeMatrix& aRight);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators.

// Matrix multiply.
ThreeVector operator*(const ThreeMatrix& aLeft, const ThreeVector& aRight);
ThreeMatrix operator*(const ThreeMatrix& aLeft, const ThreeMatrix& aRight);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators.

ThreeMatrix transpose(ThreeMatrix& aA);
ThreeMatrix identity();
ThreeMatrix diagonal(double aA11,double aA22,double aA33);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Rotation matrices.

// Rotation matrices.
ThreeMatrix rotateX(double aAngle);
ThreeMatrix rotateY(double aAngle);
ThreeMatrix rotateZ(double aAngle);

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



