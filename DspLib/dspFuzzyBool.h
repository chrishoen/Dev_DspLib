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

template <typename real_t>
class FuzzyBool
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static real_t fMin(real_t lhs, real_t rhs) { return lhs < rhs ? lhs : rhs; }
   static real_t fMax(real_t lhs, real_t rhs) { return lhs > rhs ? lhs : rhs; }
   static real_t fAbs(real_t x) { return x >= 0 ? x : -x; }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Fuzzy Lucasiewicz boolean value. It has a value 0 <= x <=1
   // Zero corresponds to false, one corresponds to true, 0.5 corresponds
   // to half true.
   real_t mX;

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
   FuzzyBool(real_t aX)
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
      return FuzzyBool((real_t)1.0 - this->mX);
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
   bool crisp(real_t aThreshold)
   {
      return this->mX >= aThreshold;
   }

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


