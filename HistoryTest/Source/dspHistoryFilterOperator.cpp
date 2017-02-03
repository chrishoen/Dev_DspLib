/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dspHistoryFilterCDiffIdentity.h"
#include "dspHistoryFilterCDiffHolob.h"
#include "dspHistoryFilterCDiffSavGol.h"
#include "dspHistoryFilterCausal.h"
#include "dspHistoryFilterNoncausal.h"

#include "dspHistoryFilterOperator.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryFilterOperator::HistoryFilterOperator(HistoryFilterParms& aParms)
{
   mParms = aParms;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryFilterOperator::show()
{
   mParms.show("HistoryFilterOperator");
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

void HistoryFilterOperator::operate(History& aX, History& aY)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Select on filter type.

   switch (mParms.mFilterType)
   {
   //***************************************************************************
   case HistoryFilterParms::cFilterIdentity:
   {
      printf("OPERATOR IDENTITY\n");

      HistoryFilterCDiffIdentity tFilter(mParms);
      tFilter.operate(aX, aY);

      return;
   }
   break;
   //***************************************************************************
   case HistoryFilterParms::cFilterCausal:
   {
      printf("OPERATOR CAUSAL %s\n",mParms.asStringCausalType()); 

      HistoryFilterCausal tFilter(mParms);
      tFilter.operate(aX, aY);

      return;
   }
   break;
   //***************************************************************************
   case HistoryFilterParms::cFilterNoncausal:
   {
      printf("OPERATOR NONCAUSAL\n");

      HistoryFilterNoncausal tFilter(mParms);
      tFilter.operate(aX, aY);

      return;
   }
   break;
   }



   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Select on filter structure.

   switch (mParms.mFilterMethod)
   {
   //*******************************************************************************
   case HistoryFilterParms::cMethodSavGol:
   {
      printf("OPERATOR SAVGOL   %10s %3d\n",mParms.asStringFilterType(),mParms.mFilterOrder);

      HistoryFilterCDiffSavGol tFilter(mParms);
      tFilter.operate(aX, aY);

      return;
   }
   break;
   //*******************************************************************************
   case HistoryFilterParms::cMethodHolob:
   {
      printf("OPERATOR HOLOB    %10s %3d\n",mParms.asStringFilterType(),mParms.mFilterOrder);

      HistoryFilterCDiffHolob tFilter(mParms);
      tFilter.operate(aX, aY);

      return;
   }
   break;
   }
}
}//namespace