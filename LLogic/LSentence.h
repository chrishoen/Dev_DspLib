#ifndef _LSENTENCE_H_
#define _LSENTENCE_H_

/*==============================================================================
==============================================================================*/
#include "LBool.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
class LSentence
{
public:
   //--------------------------------------------------------------
   // Support
   static const int cNullN = -1;
   static const LSentence cNull;
   //--------------------------------------------------------------
   // Members

   int mN;
   LBool mX;

   int mRefN;
   LBool mRefX;

   //--------------------------------------------------------------
   // Constructor

   LSentence()
   {
      mN    = cNullN;
      mRefN = cNullN;
   }

   LSentence(int aN)
   {
      mN = aN;
   }

   LSentence(int aN,LBool aX)
   {
      mN = aN;
      mX = aX;
   }

   //--------------------------------------------------------------
   // Set reference

   void setRef(LSentence* aRef)
   {
      mX    = LBool::cTrue;
      mRefN = aRef->mN;
      mRefX = aRef->mX;
   }

};

#endif

