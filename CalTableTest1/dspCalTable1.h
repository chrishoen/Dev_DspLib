#pragma once

/*==============================================================================
calibration table
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a one dimensional calibration table. It contains a
// list of x,y pairs and provides a function that uses it to interpolate
// from x to y.

template <typename real_t, int NumElements>
class  CalTable1
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Table of calibration x,y pairs. These are set manually.
   real_t mTableX[NumElements];
   real_t mTableY[NumElements];

   // True if the calibration table is valid.
   bool mValidFlag;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Consructor.
   CalTable1()
   {
      reset();
   }
   // Reset, call before table values are manually set.
   void reset()
   {
      for (int i = 0; i < NumElements; i++)
      {
         mTableX[i] = 0;
         mTableY[i] = 0;
      }
      mValidFlag = false;
   }
   // Initialize, call after table values are manually set.
   void initialize()
   {
      mValidFlag = true;
   }


   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Get an interpolated y value from an input x value.
   real_t getYfromX(real_t aX)
   {
      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Do this first.

      // Guard.
      if (!mValidFlag) return 0;

      // Locals.
      real_t tX0 = 0;
      real_t tX1 = 0;
      real_t tY0 = 0;
      real_t tY1 = 0;
      real_t tY = 0;
      int tBeginIndex = 0;
      int tEndIndex = NumElements - 1;
      int tIndex = 0;

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // If X is less than the begin X then extrapolate backwards.

      if (aX <= mTableX[tBeginIndex])
      {
         tIndex = 0;
      }
         
      //************************************************************************
      //************************************************************************
      //************************************************************************
      // If X is greater than the end X then extrapolate forwards.

      else if (aX >= mTableX[tEndIndex])
      {
         tIndex = tEndIndex - 1;
      }
   
      //************************************************************************
      //************************************************************************
      //************************************************************************
      // If X is located withing the table then find the bin that it is
      // located in.
      

      // If X is greater than the end X then return the end Y.
      else
      {
         // Loop to find the index that X is at.
         tIndex = 0;
         while (true)
         {
            // Guard. Exit the loop. This shouldn't happen.
            if (tIndex == tEndIndex) break;

            // If X is contained in the current bin then exit.
            if (aX >= mTableX[tIndex] && aX <= mTableX[tIndex + 1]) break;

            // Advance.
            tIndex++;
         }
      }

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Interpolate the Y from the X.

      // Table bin values.
      tX0 = mTableX[tIndex];
      tX1 = mTableX[tIndex + 1];
      tY0 = mTableY[tIndex];
      tY1 = mTableY[tIndex + 1];

      // Calculate the linear interpolation.
      tY = tY0 + (aX - tX0) * (tY1 - tY0) / (tX1 - tX0);

      return tY;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



