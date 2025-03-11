/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dspFilterAlphaStdDev.h"

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

AlphaStdDev::AlphaStdDev()
{
   resetVars();
}

void AlphaStdDev::resetVars()
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
void AlphaStdDev::initializeFromAlpha (double aAlpha)
{
   mXAlpha.initializeFromAlpha(aAlpha);
   mXSquareAlpha.initializeFromAlpha(aAlpha);
   resetVars();
}

// Initialize from sigma ratio, process sigma over noise sigma.
void AlphaStdDev::initializeFromSigmaRatio (double aSigmaRatio, double aDT)
{
   mXAlpha.initializeFromSigmaRatio(aSigmaRatio, aDT);
   mXSquareAlpha.initializeFromSigmaRatio(aSigmaRatio, aDT);
   resetVars();
}

// Initialize from step response time and threshold.
void AlphaStdDev::initializeFromStep(double aTs, double aStepTime, double aStepThresh)
{
   mXAlpha.initializeFromStep(aTs, aStepTime, aStepThresh);
   mXSquareAlpha.initializeFromStep(aTs, aStepTime, aStepThresh);
   resetVars();

}
// Set the first flag true.
void AlphaStdDev::setFirst()
{
   mXAlpha.setFirst();
   mXSquareAlpha.setFirst();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Put input value to calculate results in the output variables.

void AlphaStdDev::put(double aX)
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

void AlphaStdDev::show()
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

