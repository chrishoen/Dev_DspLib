#pragma once

/*==============================================================================
Dsp namespace:
Fuzzy boolean class.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************


namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Class that encapsulates a fuzzy Lucasiewicz boolean variable. 
// It has a value 0 <= x <=1. Zero corresponds to false, one corresponds to
// true, 0.5 corresponds to half true. And, Or, Not operations are provided.

class FuzzyBool
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static double fMin(double lhs, double rhs) { return lhs < rhs ? lhs : rhs; }
   static double fMax(double lhs, double rhs) { return lhs > rhs ? lhs : rhs; }
   static double fAbs(double x) { return x >= 0 ? x : -x; }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Fuzzy Lucasiewicz boolean value. It has a value 0 <= x <=1
   // Zero corresponds to false, one corresponds to true, 0.5 corresponds
   // to half true.
   double mX;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   FuzzyBool()
   {
      mX = 0.0;
   }

   // Constructor.
   FuzzyBool(double aX)
   {
      mX = aX;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Operator NOT
   FuzzyBool operator !()
   {
      return FuzzyBool(1.0 - this->mX);
   }

   // Operator AND
   friend FuzzyBool operator &&(const FuzzyBool& lhs, const FuzzyBool& rhs)
   {
      return FuzzyBool(fMin(lhs.mX, rhs.mX));
   }

   // Operator OR
   friend FuzzyBool operator ||(const FuzzyBool& lhs, const FuzzyBool& rhs)
   {
      return FuzzyBool(fMax(lhs.mX, rhs.mX));
   }

   // Operator EQUIVALENCE
   friend FuzzyBool operator %=(const FuzzyBool& lhs, const FuzzyBool& rhs)
   {
      return FuzzyBool(1.0 - fAbs(lhs.mX - rhs.mX));
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Compare with a threshold to return a crisp boolean.
   bool crisp(double aThreshold)
   {
      return this->mX >= aThreshold;
   }

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


