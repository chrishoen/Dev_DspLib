/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dsp_math.h"
#include "dsp_functions.h"
#include "dspHistoryFilterCDiffSavGol.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryFilterCDiffSavGol::HistoryFilterCDiffSavGol(HistoryFilterParms& aParms)
{
   BaseClass::initialize(aParms);
   mBackAddFlag = true;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryFilterCDiffSavGol::show()
{
   BaseClass::show();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply the linear operator from the input to the output. F:X->Y

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents, based on the parms.

void HistoryFilterCDiffSavGol::calculateCoefficientsSmoother1()
{
   // Add the backward time terms.
   mBackAddFlag = true;

   // Locals.
   double tH = mParms.mH;

   int N = mParms.mFilterOrder;
   int M = (N-1)/2;

   // Calculate the coefficients.
   for (int k = 0; k <= M; k++)
   {
      double m1 = double(N);
      double m2 = double(N*N);
      double k2 = double(k*k);
      double tTerm1 = (3*m2-7-20*k2)/4.0;
      double tTerm2 = m1*(m2-4)/3.0;

      mC[k] = tTerm1/tTerm2;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents, based on the parms.

void HistoryFilterCDiffSavGol::calculateCoefficientsSmoother2()
{
   // Add the backward time terms.
   mBackAddFlag = true;

   // Locals.
   int N = mParms.mFilterOrder;
   int m = (N-1)/2;

   // Calculate coefficents.
   for (int k = 0; k <= m; k++)
   {
      double m1 = double(N);
      mC[k] = 1.0/m1;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents, based on the parms.

void HistoryFilterCDiffSavGol::calculateCoefficientsFirstDerivative1()
{
   // Subtract the backward time terms.
   mBackAddFlag = false;

   // Locals.
   double tH = mParms.mH;

   int N = mParms.mFilterOrder;
   int M = (N-1)/2;

   // Calculate the coefficients.
   for (int k = 0; k <= M; k++)
   {
      double m1 = double(N);
      double m2 = double(N*N);
      double m4 = double(N*N*N*N);
      double k1 = double(k);
      double k2 = double(k*k);
      double k3 = double(k*k*k);

      double tTermH = 1.0/tH;
      double tTerm1 = 5*(3*m4 - 18*m2 + 31)*k1 -28*(3*m2 - 7)*k3;
      double tTerm2 = m1*(m2 - 1)*(3*m4 - 39*m2 + 108)/15.0;

      mC[k] = tTermH*tTerm1/tTerm2;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents, based on the parms.

void HistoryFilterCDiffSavGol::calculateCoefficientsFirstDerivative2()
{
   // Subtract the backward time terms.
   mBackAddFlag = false;

   // Locals.
   double tH = mParms.mH;

   int N = mParms.mFilterOrder;
   int M = (N-1)/2;

   // Calculate the coefficients.
   for (int k = 0; k <= M; k++)
   {
      double m1 = double(N);
      double m2 = double(N*N);
      double k1 = double(k);

      double tTermH = 1.0 / tH;
      double tTerm1 = k1;
      double tTerm2 = m1*(m2 - 1) / 12.0;

      mC[k] = tTermH*tTerm1 / tTerm2;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate the central difference filter coefficents, based on the parms.

void HistoryFilterCDiffSavGol::calculateCoefficientsSecondDerivative1()
{
   // Add the backward time terms.
   mBackAddFlag = true;

   // Locals.
   double tH = mParms.mH;

   int N = mParms.mFilterOrder;
   int M = (N-1)/2;

   // Calculate the coefficients.
   for (int k = 0; k <= M; k++)
   {
      double m1 = double(N);
      double m2 = double(N*N);
      double k2 = double(k*k);

      double tTermH = 1.0/(tH*tH);
      double tTerm1 = 12*m1*k2 - m1*(m2-1);
      double tTerm2 = m2*(m2-1)*(m2-4)/30.0;

      mC[k] = tTermH*tTerm1/tTerm2;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Apply the linear operator from the input to the output. F:X->Y.
// This applies the central difference filter using the coefficients 
// calculated below.

void HistoryFilterCDiffSavGol::operate(History& aX, History& aY)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Calculate the central difference filter coefficents, based on the parms.
   switch (mParms.mFilterType)
   {
   case HistoryFilterParms::cFilterSmoother:
   {
      switch (mParms.mSelect)
      {
      case 1: calculateCoefficientsSmoother1();  break;
      case 2: calculateCoefficientsSmoother2();  break;
      }
   }
   break;
   case HistoryFilterParms::cFilterFirstDeriv:
   {
      switch (mParms.mSelect)
      {
      case 1: calculateCoefficientsFirstDerivative1();  break;
      case 2: calculateCoefficientsFirstDerivative2();  break;
      }
   }
   break;
   case HistoryFilterParms::cFilterSecondDeriv:
   {
      calculateCoefficientsSecondDerivative1();
   }
   break;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Create the destination history as clone of the source history that has
   // the same size and time array, but has a zero value array.
   BaseClass::createTimeClone(aX,aY);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Execute a loop to calculate the central difference sum to implement
   // the algorithm.

   // Locals
   int tP = aX.mNumSamples;
   int tN = mParms.mFilterOrder;
   int tM = (tN-1)/2;

   // For all of the samples in the source and destination arrays.
   for (int i = 0; i < tP; i++)
   {
      // For all of the coefficients (backward and forward are the same).
      double tSum = mC[0]*aX.mValue[i];
      for (int k = 1; k <= tM; k++)
      {
         // Calculate the forward  array index, trim at the end.
         int iF = dsp_imin(i + k,tP-1);
         // Calculate the backward array index, trim at the beginning.
         int iB = dsp_imax(i - k,0);
         // Accumulate the sum from forward  source samples and coefficients.
         tSum += mC[k]*aX.mValue[iF];
         // Accumulate the sum from backward source samples and coefficients.
         if (mBackAddFlag)
         {
            tSum += mC[k] * aX.mValue[iB];
         }
         else
         {
            tSum -= mC[k] * aX.mValue[iB];
         }
      }
      // Store the sum in the destination array.
      aY.mValue[i] = tSum;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace