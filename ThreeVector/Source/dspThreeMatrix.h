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
   void setZero();
   void setIdentity();

   // Access components
   double& e(int aRow);
   double& operator()(int aRow);
   double get(int aRow) const;
   void show(char* aLabel=0);
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

//******************************************************************************

}//namespace
#endif



