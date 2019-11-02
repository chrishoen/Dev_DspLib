#ifndef _LBOOL_H_
#define _LBOOL_H_

/*==============================================================================
==============================================================================*/
#include <string.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************
class LBool
{
public:

   //---------------------------------------------------------------------------
   // Support

   static const int cTrueX;
   static const int cFalseX;
   static const int cNullX;

   static const LBool cNull;
   static const LBool cTrue;
   static const LBool cFalse;

   static int iMin (int lhs, int rhs) { return lhs < rhs ? lhs : rhs; }
   static int iMax (int lhs, int rhs) { return lhs > rhs ? lhs : rhs; }
   static int iAbs (int x) { return x >= 0 ? x : -x; }
   bool isNull() const {return mX==cNullX;}

   //---------------------------------------------------------------------------
   // Members

   int mX;

   //---------------------------------------------------------------------------
   // Constructor

   LBool()
   {
      mX = cNullX;
   }

   LBool(int aX)
   {
      mX = aX;
   }

   //---------------------------------------------------------------------------
   // String

   char* str(char* aString)
   {
      if (mX == cNullX) strcpy(aString, "NULL");
      else             sprintf(aString, "%3d",mX);
      return aString;
   }

   //---------------------------------------------------------------------------
   // Operator NOT

   LBool operator~()
   {
      if (isNull()) return cNull;
      return LBool(cTrueX - this->mX);
   }
 
   //---------------------------------------------------------------------------
   // Operator AND

   friend LBool operator &(const LBool& lhs,const LBool& rhs)
   {
      if (lhs.isNull()) return cNull;
      if (rhs.isNull()) return cNull;
      return LBool(iMin(lhs.mX,rhs.mX));
   }

   //---------------------------------------------------------------------------
   // Operator OR

   friend LBool operator |(const LBool& lhs,const LBool& rhs)
   {
      if (lhs.isNull()) return cNull;
      if (rhs.isNull()) return cNull;
      return LBool(iMax(lhs.mX,rhs.mX));
   }

   //---------------------------------------------------------------------------
   // Operator IMPLIES

   friend LBool operator >>(const LBool& lhs,const LBool& rhs)
   {
      if (lhs.isNull()) return cNull;
      if (rhs.isNull()) return cNull;
      return LBool(iMin(cTrueX,cTrueX - lhs.mX + rhs.mX));
   }

   //---------------------------------------------------------------------------
   // Operator EQUIVALENCE

   friend LBool operator %=(const LBool& lhs,const LBool& rhs)
   {
      if (lhs.isNull()) return cNull;
      if (rhs.isNull()) return cNull;
      return LBool(cTrueX - iAbs(lhs.mX - rhs.mX));
   }
};

#endif

