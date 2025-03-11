/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "prnPrint.h"

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
// Operate on the signal history according to the parameters. This is a jump 
// table that selects one of the concrete history operators according to
// the operator type parameter and uses it to operate on a history to produce
// a new history.

void HistoryFilterOperator::operate(History& aX, History& aY1,History& aY2,History& aY3)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Select on filter type.

   switch (mParms.mFilterType)
   {
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   case HistoryFilterParms::cFilterCausal:
   {
      Prn::print(Prn::DspRun2,"OPERATOR CAUSAL XY1Y2Y3 %s",mParms.asStringCausalType()); 

      HistoryFilterCausal tFilter(mParms);
      tFilter.operate(aX, aY1, aY2, aY3);

      return;
   }
   break;
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   case HistoryFilterParms::cFilterNoncausal:
   {
      Prn::print(Prn::DspRun2,"OPERATOR NONCAUSAL XY1Y2Y3 %s",mParms.asStringCausalType()); 

      HistoryFilterNoncausal tFilter(mParms);
      tFilter.operate(aX, aY1, aY2, aY3);

      return;
   }
   break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace