#ifndef _DSPFILTERFILTERS_H_
#define _DSPFILTERFILTERS_H_
/*==============================================================================

filters
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{
namespace Filter
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Sliding window average, calculates expectation (mean)
// and uncertainty (standard deviation)

class MovingAverage
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members.

   double  mX;         // Input value
   double  mEX;        // Expectation (mean)
   double  mUX;        // Uncertainty (standard deviation)
   double  mMean;      // Expectation (mean)
   double  mStdDev;    // Uncertainty (standard deviation)

   // Members
   int  mSize;
   int  mCount;
   int  mIndex;
   int  mK;

   double* mEArray;
   double  mESum;
   double* mUArray;
   double  mUSum;
   bool    mValid;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Methods.

   // Constructor and initialize.
   MovingAverage();
   ~MovingAverage();

   void initialize(int aSize);
   void finalize();
   void reset();
   void show();

   // Put input value.
   void put(double aX);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Shift register of doubles, it shifts to the right, the left end element
// is the most recent and the right end element is the latest.

class ShiftRegister
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members.

   double  mX;         // Input value
   int     mSize;      // Array size
   int     mIndex;     // Index of left end
   int     mCount;     // Number of occupied elements
   int     mK;         // Number of shifts
   bool    mValid;     // Valid
   double* mArray;     // Value array

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Methods.

   // Constructors and initialization.
   ShiftRegister();
  ~ShiftRegister();
   void reset(); 

   // Allocate memory and initialize.
   void initialize(int aSize);
   // Initialize, but reuse memory.
   void reinitialize();
   // Deallocate memory.
   void finalize();
   // Show.
   void show();

   // Shift right and put input value at the left end.
   void shiftRight(double aX);

   // Set the left end value
   void setLeft(double aX);

   // Get value
   double get(int    aIndex);
   double getLeft();
   double getRight();

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// FIRFilter, see wikipedia or matlab for definition
// H(z)=B(z)

class FIRFilter
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members.

   double         mX;       // Input value
   double         mY;       // Output value
   int            mBSize;   // B array size
   ShiftRegister  mXSR;     // History array
   bool           mValid;   // History valid
   double*        mBArray;  // B coefficient array

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members.

   // Constructors and initialization.
   FIRFilter();
  ~FIRFilter();
   void reset(); 

   // Allocate memory and initialize.
   void initialize(int aBSize);
   // Deallocate memory.
   void finalize();
   // Show.
   void show();

   // Put input value.
   double put(double aX);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// FIRTestFilter, sanity test for FIRFilter

class FIRTestFilter : public FIRFilter
{
public:
   // Initialize
   void initialize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// IIRFilter, see wikipedia or matlab for definition
// H(z)=B(z)/A(z)

class IIRFilter
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members.

   double         mX;       // Input value
   double         mY;       // Output value
   int            mBSize;   // B array size
   int            mASize;   // A array size
   ShiftRegister  mYSR;     // History array
   ShiftRegister  mXSR;     // History arrays
   bool           mValid;   // History valid
   double*        mBArray;  // B coefficient array
   double*        mAArray;  // A coefficient array

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Methods.

   // Constructors and initialization.
   IIRFilter();
  ~IIRFilter();
   void reset(); 

   // Allocate memory and initialize.
   void initialize(int aBSize, int aASize);
   void initialize(int aBSize, int aASize, double aBArray[], double aAArray[]);
   // Deallocate memory.
   void finalize();
   // Show.
   void show();

   // Put input value
   double put(double aX);

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// IIRTestFilter, sanity test for IIRFilter

class IIRTestFilter : public IIRFilter
{
public:
   // Initialize
   void initialize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// MovingDerivative

class MovingDerivative : public FIRFilter
{
public:
   // Initialize
   void initialize(int aOrder, double aDeltaTime);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This filter characterizes an input signal by calculating expectations and
// uncertainties of the signal and its time derivative.

class CharacterFilter1
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members.

   // Output values
   double           mX;    // Input value
   double           mV;    // Derivative of input 
   double           mEX;   // Input expectation
   double           mUX;   // Input uncertainty
   double           mEV;   // Derivative expectation
   double           mUV;   // Derivative uncertainty

   MovingAverage    mXMA;   // Moving average of input
   MovingDerivative mXMD;   // Moving derivative of input
   MovingAverage    mVMA;   // Moving average of derivative of input

   int              mK;     // Update count

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Methods.

   // Constructors and initialize.
   void initialize(double aDeltaTime);
   void reset();
   void show();
   // Valid
   bool mValid;

   // Put input value
   void put(double aX);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// TestSignal. This gives a sinusoidal test signal

class TestSignal
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Members.

   double mBias;
   double mAmplitude;
   double mPhase;
   double mFs;
   double mF;
   double mDT;
   double mT;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Methods.

   // Constructors and initialize.
   TestSignal();

   void initialize(
      double aBias,
      double aAmplitude,
      double aPhase,
      double aFs,
      double aF);

   // Advance sinusoid.
   double advance();
};

}//namespace
}//namespace
#endif

