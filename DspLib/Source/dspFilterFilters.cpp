/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include "dsp_functions.h"
#include "dsp_math.h"

#include <math.h>
#include <string.h>

#include "dspFilterFilters.h"

namespace Dsp
{
namespace Filter
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

MovingAverage::MovingAverage()
{
   mEArray = 0;
   mUArray = 0;
   finalize();
}

MovingAverage::~MovingAverage()
{
   finalize();
}

void MovingAverage::initialize(int aSize)
{
   finalize();
   mSize=aSize;
   mEArray = new double[aSize];
   mUArray = new double[aSize];

   mX=0.0;
   mEX=0.0;
   mUX=0.0;
   mCount=0;
   mK=0;
   mIndex=mSize-1;
   for(int i=0;i<mSize;i++)
   {
      mEArray[i]=0.0;
      mUArray[i]=0.0;
   }
   mESum=0;
   mUSum=0;
   mValid=false;
}

//******************************************************************************

void MovingAverage::finalize() 
{
   if (mEArray)
   {
      delete[] mEArray;
      mEArray=0;
   }
   if (mUArray)
   {
      delete[] mUArray;
      mUArray=0;
   }
}

//******************************************************************************
void MovingAverage::reset()
{
   mX=0.0;
   mEX=0.0;
   mUX=0.0;
   mCount=0;
   mK=0;
   mIndex=mSize-1;
   for(int i=0;i<mSize;i++)
   {
      mEArray[i]=0.0;
      mUArray[i]=0.0;
   }
   mESum=0;
   mUSum=0;
   mValid=false;
}

//******************************************************************************

void MovingAverage::put(double aX)
{
   // Adjust index
   if (++mIndex==mSize) mIndex=0;

   // Subtract old value from sum
   mESum -= mEArray[mIndex];
   mUSum -= mUArray[mIndex];

   // Add new value to sum
   mX = aX;
   double tXsquared = aX*aX;

   mESum += mX;
   mEArray[mIndex]=mX;

   mUSum += tXsquared;
   mUArray[mIndex]=tXsquared;

   // Calculate expectation from sum
   // Calculate uncertainty from sum
   if (mCount==mSize)
   {
      mEX = mESum/double(mSize);

      double tEU = mUSum/double(mSize);
      mUX = sqrt(fabs(tEU*tEU - mEX*mEX));
      mValid=true;
   }
   else
   {
      mCount++;
      mValid=false;
   }
   
   // Nicknames
   mMean   = mEX;
   mStdDev = mUX;

   // Update
   mK++;
}

//******************************************************************************

void MovingAverage::show()
{
   printf("%3d %3d %3d $$ %8.3f $$ %8.3f %8.3f $$ %8.3f %8.3f\n",
      mK,
      mIndex,
      mCount,
      mX,
      mESum,
      mUSum,
      mEX,
      mUX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void ShiftRegister::initialize(int aSize)
{
   if (aSize > MaxShiftRegisterSize) aSize = MaxShiftRegisterSize;
   if (aSize < 0) aSize=0;
   mSize=aSize;
   reset();
}

//******************************************************************************

void ShiftRegister::reset() 
{
   mX=0.0;
   mCount=0;
   mIndex=mSize-1;
   mK = 0;
#if 0
   for(int i=0;i<mSize;i++)
   {
      mArray[i]=0.0;
   }
#endif
   mValid=false;
}

//******************************************************************************

void ShiftRegister::shiftRight(double aX)
{
   // Adjust index to the right
   mIndex = dsp_index_add(mIndex, 1, mSize);

   // Add new value to array
   mX=aX;
   mArray[mIndex]=aX;

   // Calculate number of elements
   if (mCount==mSize)
   {
      mValid=true;
   }
   else
   {
      mCount++;
      mValid=false;
   }
   
   // Update
   mK++;
}

//******************************************************************************

void ShiftRegister::setLeft(double aX)
{
   // Set array left end value
   mArray[mIndex]=aX;
}

//******************************************************************************

double ShiftRegister::get(int aOffset)
{
   // Guard
   if (!mValid) return 0.0;

   // Get index
   int tGetIndex = dsp_index_sub(mIndex, aOffset, mSize);

   // Return array value at index
   return mArray[tGetIndex];
}

//******************************************************************************

double ShiftRegister::getLeft()
{
   // Guard
   if (!mValid) return 0.0;

   // Return array value at index
   return mArray[mIndex];
}

//******************************************************************************

double ShiftRegister::getRight()
{
   // Guard
   if (!mValid) return 0.0;

   // Get index of right end
   int tGetIndex = dsp_index_sub(mIndex, (mSize - 1), mSize);

   // Return array value at index
   return mArray[tGetIndex];
}


//******************************************************************************

void ShiftRegister::show()
{
   printf("ShiftRegister:                   %3d %8.3f $$",mIndex,mX);
   for (int j=0;j<mSize;j++)
   {
      printf("%8.3f ", get(j));
   }
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void FIRFilter::initialize(int aSize)
{
   for (int i=0;i<mXSR.mSize;i++) mBArray[i]=0.0;
   mXSR.initialize(aSize);
   reset();
}

//******************************************************************************

void FIRFilter::reset() 
{
   mXSR.reset();
}

//******************************************************************************

double FIRFilter::put(double aX)
{
   // Put input value
   mX = aX;
   mXSR.shiftRight(mX);

   // Guard
   if (!mXSR.mValid)
   {
      mY=0.0;
      return 0.0;
   }

   // Valid
   mValid=true;

   // Calculate sum
   double tXSum=0.0;
   for (int i=0;i<mXSR.mSize;i++)
   {
      tXSum += mXSR.get(i) * mBArray[i];
   }
   mY = tXSum;

   // Return sum
   return mY;
}

//******************************************************************************

void FIRFilter::show()
{
   printf("%3d $$ %8.3f %8.3f\n",
      mXSR.mK,
      mX,
      mY);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void FIRTestFilter::initialize()
{
   FIRFilter::initialize(4);
   FIRFilter::mBArray[0]=0.25;
   FIRFilter::mBArray[1]=0.25;
   FIRFilter::mBArray[2]=0.25;
   FIRFilter::mBArray[3]=0.25;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void IIRFilter::initialize(int aBSize, int aASize)
{
   mBSize = aBSize;
   mASize = aASize;
   for (int i = 0; i<aBSize; i++) mBArray[i] = 0.0;
   for (int i = 0; i<aASize; i++) mAArray[i] = 0.0;
   mXSR.initialize(aBSize);
   mYSR.initialize(aASize);
}

void IIRFilter::initialize(int aBSize, int aASize, double aBArray[], double aAArray[])
{
   mBSize = aBSize;
   mASize = aASize;
   for (int i=0; i<aBSize; i++) mBArray[i] = aBArray[i];
   for (int i=0; i<aASize; i++) mAArray[i] = aAArray[i];

   mXSR.initialize(aBSize);
   mYSR.initialize(aASize);
}

//******************************************************************************

double IIRFilter::put(double aX)
{
   // Store input value
   mX = aX;

   // Put input value into X shift register
   mXSR.shiftRight(mX);

   // Advance Y shift register with zero at left end
   mYSR.shiftRight(0.0);

   // Store valid
   mValid = mXSR.mValid;

   // Calculate X sum
   double tXSum=0.0;
   for (int i = 0; i<mXSR.mSize; i++)
   {
      tXSum += mXSR.get(i) * mBArray[i];
   }

   // Calculate Y sum
   double tYSum=0.0;
   for (int i=0;i<mYSR.mSize;i++)
   {
      tYSum += mYSR.get(i) * mAArray[i];
   }

   // Calculate Y 
   mY = tXSum - tYSum;

   // Put Y into Y shift register left end
   mYSR.setLeft(mY);

   // Return Y
   return mY;
}

//******************************************************************************

void IIRFilter::show()
{
   printf("%3d $$ %8.3f %8.3f\n",
      mXSR.mK,
      mX,
      mY);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void IIRTestFilter::initialize()
{
   IIRFilter::initialize(1,4);

   IIRFilter::mAArray[0]=0.25;

   IIRFilter::mBArray[0]=0.25;
   IIRFilter::mBArray[1]=0.25;
   IIRFilter::mBArray[2]=0.25;
   IIRFilter::mBArray[3]=0.25;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void MovingDerivative::initialize(int aOrder,double aDeltaTime)
{
   FIRFilter::initialize(aOrder);

   if (aOrder==3)
   {
      FIRFilter::initialize(3);

      double tDenom = 2.0*aDeltaTime;

      FIRFilter::mBArray[0] =  -1.0/tDenom;
      FIRFilter::mBArray[1] =   4.0/tDenom;
      FIRFilter::mBArray[2] =  -3.0/tDenom;
   }

   if (aOrder==5)
   {
      FIRFilter::initialize(5);

      double tDenom = 12.0*aDeltaTime;

      FIRFilter::mBArray[0] =   3.0/tDenom;
      FIRFilter::mBArray[1] =  10.0/tDenom;
      FIRFilter::mBArray[2] = -18.0/tDenom;
      FIRFilter::mBArray[3] =   6.0/tDenom;
      FIRFilter::mBArray[4] =  -1.0/tDenom;
   }
}

//******************************************************************************
//*****************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

void CharacterFilter1::initialize(double aDeltaTime)
{
   mXMA.initialize(10);
   mXMD.initialize(5,aDeltaTime);
   mVMA.initialize(10);
   reset();
}

//******************************************************************************

void CharacterFilter1::reset() 
{
   // Output values
   mX=0.0;
   mV=0.0;
   mEX=0.0;
   mUX=0.0;
   mEV=0.0;
   mUV=0.0;
   mK=0;

   // Averages and derivatives
   mXMA.reset();
   mXMD.reset();
   mVMA.reset();
}

//******************************************************************************

void CharacterFilter1::put(double aX)
{
   // Update filters
   mXMA.put(aX);
   mXMD.put(aX);
   mVMA.put(mXMD.mY);

   // Update output values
   mX  = aX;
   mV  = mXMD.mY;
   mEX = mXMA.mEX;
   mUX = mXMA.mUX;
   mEV = mVMA.mEX;
   mUV = mVMA.mUX;

   // Update
   mK++;
}

//******************************************************************************

void CharacterFilter1::show()
{
// mXMA.show();
// return;

   printf("%3d %8.3f %8.3f $$ %8.3f %8.3f $$ %8.3f %8.3f $$ \n",
      mK,
      mX,
      mV,
      mEX,
      mUX,
      mEV,
      mUV);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
TestSignal::TestSignal()
{
   mBias      = 0.0;
   mAmplitude = 0.0;
   mPhase     = 0.0;
   mFs        = 0.0;
   mF         = 0.0;
   mDT        = 0.0;
   mT         = 0.0;
}

//******************************************************************************
void TestSignal::initialize(
   double aBias,
   double aAmplitude,
   double aPhase,
   double aFs,
   double aF)
{
   mBias      = aBias;
   mAmplitude = aAmplitude;
   mPhase     = aPhase;
   mFs        = aFs;
   mF         = aF;
   mDT        = 1 / mFs;
   mT         = 0.0;
}

//******************************************************************************
double TestSignal::advance()
{
   // Sinusoid
   double tY = mBias + sin(DSP_2PI*mF*mT + mPhase);
   // Advance time
   mT += mDT;
   // Done
   return tY;
}

}//namespace
}//namespace

