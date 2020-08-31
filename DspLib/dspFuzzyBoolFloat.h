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

class FuzzyBoolFloat
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constants.

   static float fMin(float lhs, float rhs) { return lhs < rhs ? lhs : rhs; }
   static float fMax(float lhs, float rhs) { return lhs > rhs ? lhs : rhs; }
   static float fAbs(float x) { return x >= 0 ? x : -x; }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Fuzzy Lucasiewicz boolean value. It has a value 0 <= x <=1
   // Zero corresponds to false, one corresponds to true, 0.5 corresponds
   // to half true.
   float mX;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   FuzzyBoolFloat()
   {
      mX = 0.0;
   }

   // Constructor.
   FuzzyBoolFloat(float aX)
   {
      mX = aX;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Operator NOT
   FuzzyBoolFloat operator !()
   {
      return FuzzyBoolFloat(1.0f - this->mX);
   }

   // Operator AND
   friend FuzzyBoolFloat operator &&(const FuzzyBoolFloat& lhs, const FuzzyBoolFloat& rhs)
   {
      return FuzzyBoolFloat(fMin(lhs.mX, rhs.mX));
   }

   // Operator OR
   friend FuzzyBoolFloat operator ||(const FuzzyBoolFloat& lhs, const FuzzyBoolFloat& rhs)
   {
      return FuzzyBoolFloat(fMax(lhs.mX, rhs.mX));
   }

   // Operator EQUIVALENCE
   friend FuzzyBoolFloat operator %=(const FuzzyBoolFloat& lhs, const FuzzyBoolFloat& rhs)
   {
      return FuzzyBoolFloat(1.0f - fAbs(lhs.mX - rhs.mX));
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Compare with a threshold to return a crisp boolean.
   bool crisp(float aThreshold)
   {
      return this->mX >= aThreshold;
   }

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


