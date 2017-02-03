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

#include "dspHistoryFilterCDiffGen.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

HistoryFilterCDiffGen::HistoryFilterCDiffGen(HistoryFilterParms& aParms)
{
   mParms = aParms;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void HistoryFilterCDiffGen::show()
{
   mParms.show("HistoryFilterCDiffGen");
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

void HistoryFilterCDiffGen::operate(History& aX, History& aY)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Select on linear operator type.

   switch (mParms.mFilterType)
   {
   //***************************************************************************
   case HistoryFilterParms::cFilterCDiffIdentity:
   {
      printf("OPERATOR IDENTITY\n");

      HistoryFilterCDiffIdentity tFilter(mParms);
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