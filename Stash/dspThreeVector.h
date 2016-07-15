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
//******************************************************************************
//******************************************************************************

class ThreeMatrix
{
public:
   // Matrix components
   double* mValues;
   int mRows;
   int mCols;

   // Constructor
   ThreeMatrix();
  ~ThreeMatrix();

   // Initialize
   void initialize(
      int     aRows,
      int     aCols);

   // Initialize
   void initialize(
      int     aRows,
      int     aCols,
      double* aValues);

   // Assign values
   void setValues(
      double* aValues);

   void reset();

   // Access components
   double& e(int aRow,int aCol);
   double& operator()(int aRow,int aCol);
   void show(char* aLabel=0);

   // Operator
   ThreeVector operator*(ThreeVector& aRight);

   // Set matrix to a rotation matrix
   void setRotateX   (double aAngle);
   void setRotateY   (double aAngle);
   void setRotateZ   (double aAngle);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

void add          (ThreeVector& aY, ThreeVector& aX1, ThreeVector& aX2);  // Y  = X1 + X2
void addTo        (ThreeVector& aY, ThreeVector& aX);                 // Y += X 
void subtract     (ThreeVector& aY, ThreeVector& aX1, ThreeVector& aX2);  // Y  = X1 - X2
void subtractFrom (ThreeVector& aY, ThreeVector& aX);                 // Y -= X
void multiply     (ThreeVector& aY, ThreeVector& aX,  double   aA);   // Y  = X*a 
void multiply     (ThreeVector& aY, ThreeMatrix& aA,  ThreeVector& aX);   // Y  = A*X

void add          (ThreeMatrix& aC, ThreeMatrix& aA,  ThreeMatrix& aB);   // C  = A + B
void multiply     (ThreeMatrix& aC, ThreeMatrix& aA,  ThreeMatrix& aB);   // C  = A*B
void transpose    (ThreeMatrix& aC, ThreeMatrix& aA);                 // C  = Transpose[A]

//******************************************************************************

}//namespace
#endif



