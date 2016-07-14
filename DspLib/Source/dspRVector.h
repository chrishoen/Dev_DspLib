#ifndef _DSPRVECTOR_H_
#define _DSPRVECTOR_H_
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

class RVector
{
public:
   // Vector components
   double* mValues;
   int mRows;

   // Constructor
   RVector();
   RVector(int aRows);
   RVector(const RVector& aOther);
   RVector& operator=( const RVector& aOther );
   ~RVector();

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
   RVector operator+(RVector& aRight);

   // Subtract two vectors
   RVector operator-(RVector& aRight);

   // Multiply a vector by a scalar
   RVector operator*(double aRight);

   // Divide a vector by a scalar
   RVector operator/(double aRight);

   // Inner product of two vectors
   double   operator*(RVector& aRight);

   // Length of a vector
   double   length();

   // Return a normalized vector
   RVector normalize();

   // Return true if two vectors are close
   bool     isCloseTo(RVector& aRight,double aThreshold);
   

};

//******************************************************************************
//******************************************************************************
//******************************************************************************

class RMatrix
{
public:
   // Matrix components
   double* mValues;
   int mRows;
   int mCols;

   // Constructor
   RMatrix();
  ~RMatrix();

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
   RVector operator*(RVector& aRight);

   // Set matrix to a rotation matrix
   void setRotateX   (double aAngle);
   void setRotateY   (double aAngle);
   void setRotateZ   (double aAngle);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************

void add          (RVector& aY, RVector& aX1, RVector& aX2);  // Y  = X1 + X2
void addTo        (RVector& aY, RVector& aX);                 // Y += X 
void subtract     (RVector& aY, RVector& aX1, RVector& aX2);  // Y  = X1 - X2
void subtractFrom (RVector& aY, RVector& aX);                 // Y -= X
void multiply     (RVector& aY, RVector& aX,  double   aA);   // Y  = X*a 
void multiply     (RVector& aY, RMatrix& aA,  RVector& aX);   // Y  = A*X

void add          (RMatrix& aC, RMatrix& aA,  RMatrix& aB);   // C  = A + B
void multiply     (RMatrix& aC, RMatrix& aA,  RMatrix& aB);   // C  = A*B
void transpose    (RMatrix& aC, RMatrix& aA);                 // C  = Transpose[A]

//******************************************************************************

}//namespace
#endif



