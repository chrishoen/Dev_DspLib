#pragma once

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a base class that provides a golden section search.

class GoldSearchBase
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Search variables.
   double mXAinitial;
   double mXBinitial;

   double mTolerance;
   int    mMaxIterations;

   double mA,mB,mC,mD;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor and initialization.

   // Constructor.
   GoldSearchBase();
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Write to the history.

   // Perform the search.
   double search(
      double aXAinitial,
      double aXBinitial,
      double aTolerance,
      int MaxIterations);


   // Abstract f(x), supplied by inheritors.
   virtual double function(double aX)=0;
      
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // More.

   void show();
};

//******************************************************************************
}//namespace

