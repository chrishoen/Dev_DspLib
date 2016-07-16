#ifndef _DSPTHREEMATRIX_H_
#define _DSPTHREEMATRIX_H_
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
   // Matrix components
   double mValues[3][3];

   // Constructor
   ThreeMatrix();
   ThreeMatrix(
      double aA11,double aA12,double aA13,
      double aA21,double aA22,double aA23,
      double aA31,double aA32,double aA33);
   ThreeMatrix(double aValues[3][3]);

   // Assign values
   void set(
      double aA11,double aA12,double aA13,
      double aA21,double aA22,double aA23,
      double aA31,double aA32,double aA33);
   void set(double aValues[3][3]);
   void setZero();
   void setIdentity();

   // Access components
   double& e(int aRow,int aCol);
   double& operator()(int aRow,int aCol);
   double get(int aRow,int aCol) const;
   void show(char* aLabel=0);

   // Get rows and columns
   ThreeVector getRow(int aRow);
   ThreeVector getCol(int aCol);

   // Transpose
   ThreeMatrix transpose();

   // Set to a rotation matrix
   void setRotateX   (double aAngle);
   void setRotateY   (double aAngle);
   void setRotateZ   (double aAngle);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators

// Scalar multilply, divide
ThreeMatrix operator*(double aLeft, ThreeMatrix& aRight);
ThreeMatrix operator*(ThreeMatrix& aLeft,double aRight);
ThreeMatrix operator/(ThreeMatrix& aLeft,double aRight);

// Matrix sum, difference
ThreeMatrix operator+(ThreeMatrix& aLeft,ThreeMatrix& aRight);
ThreeMatrix operator-(ThreeMatrix& aLeft,ThreeMatrix& aRight);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators

// Matrix multiply
ThreeVector operator*(ThreeMatrix& aLeft,ThreeVector& aRight);
ThreeMatrix operator*(ThreeMatrix& aLeft,ThreeMatrix& aRight);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators

// Transpose
ThreeMatrix transpose(ThreeMatrix& aA);

//******************************************************************************

}//namespace
#endif



