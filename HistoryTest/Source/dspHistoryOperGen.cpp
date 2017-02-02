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
#include "dspHistoryOperFilterPH.h"
#include "dspHistoryOperFilterSG.h"

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
   switch (mParms.mOperType)
   {
   //*******************************************************************************
   case HistoryOperParms::cOperIdentity:
   {
      HistoryOperIdentity tOper(mParms);
      tOper.operate(aX, aY);
   }
   break;
   //*******************************************************************************
   case HistoryOperParms::cOperSmoother:
   {
      HistoryOperFilterSG tOper(mParms);
      tOper.operate(aX, aY);
   }
   break;
   //*******************************************************************************
   case HistoryOperParms::cOperDerivOne:
   {
      HistoryOperFilterPH tOper(mParms);
      tOper.operate(aX, aY);
   }
   break;
   }
}
}//namespace