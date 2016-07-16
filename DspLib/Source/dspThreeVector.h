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
   ThreeVector(const double aValues[3]);

   // Assign values
   void set(double aV1,double aV2,double aV3);
   void set(const double aValues[3]);
   void setZero();

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
ThreeVector operator*(double aLeft, const ThreeVector& aRight);
ThreeVector operator*(const ThreeVector& aLeft,double aRight);
ThreeVector operator/(const ThreeVector& aLeft,double aRight);

// Vector sum, difference
ThreeVector operator+(const ThreeVector& aLeft,const ThreeVector& aRight);
ThreeVector operator-(const ThreeVector& aLeft,const ThreeVector& aRight);

// Inner product
double operator*(const ThreeVector& aLeft,const ThreeVector& aRight);

//******************************************************************************

}//namespace
#endif



