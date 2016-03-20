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
   enum { MaxFilterSize = 200 };

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Sliding window average, calculates expectation (mean)
// and uncertainty (standard deviation)

class MovingAverage
{
public:
   // Initialize
   void initialize(int aSize); 
   void reset(); 
   void show();
   // Valid
   bool mValid;

   // Put input value
   void put(double aX);

   // Input value
   double mX;
   // Output expectation (mean)
   double mE;
   // Output uncertainty (standard deviation)
   double mU;

   // Members
   int mSize;
   int mCount;
   int mIndex;
   int mK;

   double mEArray[MaxFilterSize];
   double mESum;
   double mUArray[MaxFilterSize];
   double mUSum;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Shift register of doubles, it shifts to the right, the left end element
// is the most recent and the right end element is the latest.

class ShiftRegister
{
public:
   // Initialize
   void initialize(int aSize);
   void reset(); 
   void show();
   // Valid
   bool mValid;

   // Shift right and put input value at the left end.
   void shiftRight(double aX);

   // Set the left end value
   void setLeft(double aX);

   // Input value
   double mX;

   // Get value
   double get(int    aIndex);
   double getLeft();
   double getRight();

   // Members

   // Array size
   int mSize;
   // Index of left end
   int mIndex;
   // Number of occupied elements
   int mCount;
   // Number of shifts
   int mK;

   // Value array
   enum { MaxShiftRegisterSize = 1000 };
   double mArray[MaxShiftRegisterSize];
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// FIRFilter, see wikipedia or matlab for definition

class FIRFilter
{
public:
   // Initialize
   void initialize(int aSize); 
   void reset(); 
   void show();
   // Valid
   bool mValid;

   // Put input value
   double put(double aX);

   // Input value
   double mX;

   // Output value
   double mY;

   // Value array
   ShiftRegister mXSR;

   // Coefficient array
   double mBArray[MaxFilterSize];
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

class IIRFilter
{
public:
   // Initialize
   void initialize(int aBSize, int aASize);
   void initialize(int aBSize, int aASize, double aBArray[], double aAArray[]);
   void show();
   // Valid
   bool mValid;

   // Put input value
   double put(double aX);

   // Input value
   double mX;

   // Output value
   double mY;

   // Sizes
   int mBSize;
   int mASize;

   // Value arrays
   ShiftRegister mYSR;
   ShiftRegister mXSR;

   // Coefficient arrays
   double mBArray[MaxFilterSize];
   double mAArray[MaxFilterSize];
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
   void initialize(int aOrder,double aDeltaTime); 
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This filter characterizes an input signal by calculating expectations and
// uncertainties of the signal and its time derivative.

class CharacterFilter1
{
public:
   // Initialize
   void initialize(double aDeltaTime); 
   void reset(); 
   void show();
   // Valid
   bool mValid;

   // Put input value
   void put(double aX);

   // Output values
   double mX;       // Input value
   double mV;       // Derivative of input 
   double mEX;      // Input expectation
   double mUX;      // Input uncertainty
   double mEV;      // Derivative expectation
   double mUV;      // Derivative uncertainty

   // Averages and derivatives
   MovingAverage    mXMA;   // Moving average of input
   MovingDerivative mXMD;   // Moving derivative of input
   MovingAverage    mVMA;   // Moving average of derivative of input

   // Members
   int mK;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// TestSignal. This gives a sinusoidal test signal

class TestSignal
{
public:
   TestSignal();

   // Initialize
   void initialize(
      double aBias,
      double aAmplitude,
      double aPhase,
      double aFs,
      double aF);

   // Advance sinusoid
   double advance();

   // Members
   double mBias;
   double mAmplitude;
   double mPhase;
   double mFs;
   double mF;
   double mDT;
   double mT;

};

}//namespace
}//namespace
#endif

