#ifndef _DSPLUT_H_
#define _DSPLUT_H_
/*==============================================================================

lookup tables
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <stdlib.h>
#include "my_functions.h"
#include "prnPrint.h"

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class  Lut1D
{
public:
   void initialize(
      int     aRows,
      double  aFirstX, 
      double  aDeltaX,
      double* aVTable);

   double lookup(double aX);

   double* mVTable;
   int mRows;

   double mFirstX;
   double mLastX;
   double mDeltaX;
};

//******************************************************************************

class  Lut2D
{
public:
   void initialize(
      int     aRows,
      int     aCols,
      double  aFirstX, 
      double  aFirstY, 
      double  aDeltaX,
      double  aDeltaY,
      double* aVTable);

   double lookup(int aRow,int aCol);
   double lookup(double aX,double aY);

   double* mVTable;
   int mRows;
   int mCols;

   double mFirstX;
   double mLastX;
   double mDeltaX;
   double mFirstY;
   double mLastY;
   double mDeltaY;
};

//******************************************************************************

}//namespace
#endif


