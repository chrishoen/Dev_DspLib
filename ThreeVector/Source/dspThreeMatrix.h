#ifndef _DSPTHREEMATRIX_H_
#define _DSPTHREEMATRIX_H_
/*==============================================================================

Matrixs and matrices on R3.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class ThreeMatrix
{
public:
   // Matrix components
   double mValues[3];

   // Constructor
   ThreeMatrix();
   ThreeMatrix(double aV1,double aV2,double aV3);
   ThreeMatrix(const double* aValues);

   // Assign values
   void set(double aV1,double aV2,double aV3);
   void set(const double* aValues);

   // Access components
   double& e(int aRow);
   double& operator()(int aRow);
   double get(int aRow) const;
   void show(char* aLabel=0);

   // Length of a matrix
   double length();

   // Return a normalized matrix
   ThreeMatrix normalize();

   // Set
   void setZero();
   void setNormalize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators

// Scalar multilply, divide
ThreeMatrix operator*(double aLeft, const ThreeMatrix& aRight);
ThreeMatrix operator*(const ThreeMatrix& aLeft,double aRight);
ThreeMatrix operator/(const ThreeMatrix& aLeft,double aRight);

// Matrix sum, difference
ThreeMatrix operator+(const ThreeMatrix& aLeft,const ThreeMatrix& aRight);
ThreeMatrix operator-(const ThreeMatrix& aLeft,const ThreeMatrix& aRight);

// Inner product
double operator*(const ThreeMatrix& aLeft,const ThreeMatrix& aRight);

//******************************************************************************

}//namespace
#endif



