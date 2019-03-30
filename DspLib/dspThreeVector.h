#pragma once

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
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Vector components.
   double mValues[3];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   ThreeVector();
   ThreeVector(double aV1,double aV2,double aV3);
   ThreeVector(double aValues[3]);
   ThreeVector(int aBasisCoordinate);

   // Assign values.
   void set(double aV1,double aV2,double aV3);
   void set(double aValues[3]);
   void setToZero();
   void setToBasisVector(int aBasisCoordinate);

   // Access components.
   double& e(int aRow);
   double& operator()(int aRow);
   double get(int aRow) const;
   double& x();
   double& y();
   double& z();
   void show(char* aLabel=0);
   void show2(char* aLabel=0);
   void show3(char* aLabel=0);

   // Length of a vector.
   double length();

   // Return a normalized vector.
   ThreeVector normalize();

   // Set.
   void setNormalize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operators

// Scalar multilply, divide.
ThreeVector operator*(double aLeft, const ThreeVector& aRight);
ThreeVector operator*(const ThreeVector& aLeft,double aRight);
ThreeVector operator/(const ThreeVector& aLeft,double aRight);

// Vector sum, difference.
ThreeVector operator+(const ThreeVector& aLeft, const ThreeVector& aRight);
ThreeVector operator-(const ThreeVector& aLeft, const ThreeVector& aRight);

// Inner product.
double operator*(const ThreeVector& aLeft, const ThreeVector& aRight);

// Cross product.
ThreeVector cross(const ThreeVector& aLeft, const ThreeVector& aRight);
ThreeVector operator&(const ThreeVector& aLeft, const ThreeVector& aRight);

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



