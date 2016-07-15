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
   double* mValues;
   int mRows;

   // Constructor
   ThreeVector();
   ThreeVector(int aRows);
   ThreeVector(const ThreeVector& aOther);
   ThreeVector& operator=( const ThreeVector& aOther );
   ~ThreeVector();

   // Initialize
   void initialize(
      int     aRows);

   void initialize(
      int     aRows,
      double* aValues);

   // Assign values
   void setValues(
      double* aValues);

   void reset();

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

   // Return true if two vectors are close
   bool     isCloseTo(ThreeVector& aRight,double aThreshold);
   

};

//******************************************************************************

}//namespace
#endif



