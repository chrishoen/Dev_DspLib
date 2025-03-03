/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspFilterAlphaAbsDev.h"

namespace Dsp
{
namespace Filter
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

AlphaAbsDev::AlphaAbsDev()
{
   resetVars();
}

void AlphaAbsDev::resetVars()
{
   mX = 0.0;
   mEX = 0.0;
   mUX = 0.0;
   mMean   = 0.0;
   mAbsDev = 0.0;
   mK = 0;
}

// Initialize from alpha.
void AlphaAbsDev::initializeFromAlpha (double aAlpha)
{
   mAlphaX.initializeFromAlpha(aAlpha);
   mAlphaAbsDev.initializeFromAlpha(aAlpha);
   resetVars();
}

// Initialize from lambda (tracking index).
void AlphaAbsDev::initializeFromLambda (double aLambda)
{
   mAlphaX.initializeFromLambda(aLambda);
   mAlphaAbsDev.initializeFromLambda(aLambda);
   resetVars();

}

// Initialize from step response time and threshold.
void AlphaAbsDev::initializeFromStep(double aTs, double aStepTime, double aStepThresh)
{
   mAlphaX.initializeFromStep(aTs, aStepTime, aStepThresh);
   mAlphaAbsDev.initializeFromStep(aTs, aStepTime, aStepThresh);
   resetVars();

}
// Set the first flag true.
void AlphaAbsDev::setFirst()
{
   mAlphaX.setFirst();
   mAlphaAbsDev.setFirst();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put input value to calculate results in the output variables.

void AlphaAbsDev::put(double aX)
{
   // These give moving averages (moving expectatons) of X and X the
   // absolute deviation of X 
   // E[X] and E[|X - E[X]|].
   mAlphaX.put(aX);
   mAlphaAbsDev.put(fabs(aX - mAlphaX.mXX));

   // X
   mX = aX;

   // Expectation (mean) of X is E[X]
   mEX = mAlphaX.mXX;

   // Absolute deviation of X is E[|X - E[X]|]
   mUX = mAlphaAbsDev.mXX;

   // Nicknames
   mMean   = mEX;
   mAbsDev = mUX;

   // Update
   mK++;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void AlphaAbsDev::show()
{
   printf("%3d %8.3f %8.3f %8.3f\n",
      mK,
      mX,
      mEX,
      mUX);
}


//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
}//namespace

