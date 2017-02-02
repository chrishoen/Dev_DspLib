/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dspHistoryOperIdentity.h"
#include "dspHistoryOperFilterHolob.h"
#include "dspHistoryOperFilterSavGol.h"

#include "dspHistoryOperGen.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryOperGen::HistoryOperGen(HistoryOperParms& aParms)
{
   mParms = aParms;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryOperGen::show()
{
   mParms.show("HistoryOperGen");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Operate on the signal history according to the parameters. This is a jump 
// table that selects one of the concrete history operators according to
// the operator type parameter and uses it to operate on a history to produce
// a new history.

void HistoryOperGen::operate(History& aX, History& aY)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Select on linear operator type.

   switch (mParms.mOperType)
   {
   //***************************************************************************
   case HistoryOperParms::cOperIdentity:
   {
      printf("OPERATOR IDENTITY\n");

      HistoryOperIdentity tOper(mParms);
      tOper.operate(aX, aY);

      return;
   }
   break;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Select on filter structure.

   switch (mParms.mFiltStruct)
   {
   //*******************************************************************************
   case HistoryOperParms::cFiltStructSavGol:
   {
      printf("OPERATOR SAVGOL   %10s %3d\n",mParms.asStringOperType(),mParms.mFilterOrder);

      HistoryOperFilterSavGol tOper(mParms);
      tOper.operate(aX, aY);

      return;
   }
   break;
   //*******************************************************************************
   case HistoryOperParms::cFiltStructHolob:
   {
      printf("OPERATOR HOLOB    %10s %3d\n",mParms.asStringOperType(),mParms.mFilterOrder);

      HistoryOperFilterHolob tOper(mParms);
      tOper.operate(aX, aY);

      return;
   }
   break;
   }
}
}//namespace