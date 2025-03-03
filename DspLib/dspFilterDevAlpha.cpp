/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspFilterDevAlpha.h"

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

StdDevAlpha::StdDevAlpha()
{
   resetVars();
}

void StdDevAlpha::resetVars()
{
   mX = 0.0;
   mEX = 0.0;
   mUX = 0.0;
   mVariance = 0.0;
   mMean   = 0.0;
   mStdDev = 0.0;
   mK = 0;
}

// Initialize from alpha.
void StdDevAlpha::initializeFromAlpha (double aAlpha)
{
   mXAlpha.initializeFromAlpha(aAlpha);
   mXSquareAlpha.initializeFromAlpha(aAlpha);
   resetVars();
}

// Initialize from lambda (tracking index).
void StdDevAlpha::initializeFromLambda (double aLambda)
{
   mXAlpha.initializeFromLambda(aLambda);
   mXSquareAlpha.initializeFromLambda(aLambda);
   resetVars();

}

// Initialize from step response time and threshold.
void StdDevAlpha::initializeFromStep(double aTs, double aStepTime, double aStepThresh)
{
   mXAlpha.initializeFromStep(aTs, aStepTime, aStepThresh);
   mXSquareAlpha.initializeFromStep(aTs, aStepTime, aStepThresh);
   resetVars();

}
// Set the first flag true.
void StdDevAlpha::setFirst()
{
   mXAlpha.setFirst();
   mXSquareAlpha.setFirst();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void StdDevAlpha::put(double aX)
{
   // These give moving averages (moving expectatons) of X and X squared.
   // E[X] and E[X^2].
   mXAlpha.put(aX);
   mXSquareAlpha.put(aX*aX);

   // X
   mX = aX;

   // Expectation (mean) of X is E[X]
   mEX = mXAlpha.mXX;

   // Variance of X is E[X^2] - E[X]^2
   mVariance = mXSquareAlpha.mXX - mEX*mEX;

   // Uncertainty (stddev) of X
   if (mVariance > 0.0f)
   {
      mUX = sqrt(mVariance);
   }
   else
   {
      mUX = 0.0f;
   }

   // Nicknames
   mMean   = mEX;
   mStdDev = mUX;

   // Update
   mK++;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void StdDevAlpha::show()
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

