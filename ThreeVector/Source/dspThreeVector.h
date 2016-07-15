#ifndef _DSPTHREEVECTOR_H_
#define _DSPTHREEVECTOR_H_
/*==============================================================================

real vector space
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class ThreeVector
{
public:
   // Dimension
   static const int cDim = 3;

   // Vector components
   double mValues[3];

   // Constructor
   ThreeVector();
   ThreeVector(const double* aValues);

   // Assign values
   void setValues(const double* aValues);

   // Access components
   double& e(int aRow);
   double& operator()(int aRow);
   void show(char* aLabel=0);

   // Add two vectors
   ThreeVector operator+(ThreeVector& aRight);

   // Subtract two vectors
   ThreeVector operator-(ThreeVector& aRight);

   // Multiply a vector by a scalar
   ThreeVector operator*(double aRight);

   // Divide a vector by a scalar
   ThreeVector operator/(double aRight);

   // Inner product of two vectors
   double   operator*(ThreeVector& aRight);

   // Length of a vector
   double   length();

   // Return a normalized vector
   ThreeVector normalize();

};

//******************************************************************************

}//namespace
#endif



