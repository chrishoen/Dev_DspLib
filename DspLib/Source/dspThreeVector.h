#ifndef _DSPTHREEVECTOR_H_
#define _DSPTHREEVECTOR_H_
/*==============================================================================

Vectors and matrices on R3.
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
   ThreeVector(double aValues[3]);
   ThreeVector(int aBasisCoordinate);

   // Assign values
   void set(double aV1,double aV2,double aV3);
   void set(double aValues[3]);
   void setToZero();
   void setToBasisVector(int aBasisCoordinate);

   // Access components
   double& e(int aRow);
   double& operator()(int aRow);
   double get(int aRow) const;
   void show(char* aLabel=0);
   void show2(char* aLabel=0);

   // Length of a vector
   double length();

   // Return a normalized vector
   ThreeVector normalize();

   // Set
   void setNormalize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators

// Scalar multilply, divide
ThreeVector operator*(double aLeft, ThreeVector& aRight);
ThreeVector operator*(ThreeVector& aLeft,double aRight);
ThreeVector operator/(ThreeVector& aLeft,double aRight);

// Vector sum, difference
ThreeVector operator+(ThreeVector& aLeft,ThreeVector& aRight);
ThreeVector operator-(ThreeVector& aLeft,ThreeVector& aRight);

// Inner product
double operator*(ThreeVector& aLeft,ThreeVector& aRight);

// Cross product
ThreeVector cross(ThreeVector& aLeft, ThreeVector& aRight);
ThreeVector operator&(ThreeVector& aLeft, ThreeVector& aRight);

//******************************************************************************

}//namespace
#endif



