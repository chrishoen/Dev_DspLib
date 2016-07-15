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
   // Vector components
   double mValues[3];

   // Constructor
   ThreeVector();
   ThreeVector(double aV1,double aV2,double aV3);
   ThreeVector(const double* aValues);

   // Assign values
   void set(double aV1,double aV2,double aV3);
   void set(const double* aValues);

   // Access components
   double& e(int aRow);
   double& operator()(int aRow);
   double get(int aRow) const;
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
//******************************************************************************
//******************************************************************************
ThreeVector operator * ( double aLeft, const ThreeVector& aRight );

//******************************************************************************

}//namespace
#endif



