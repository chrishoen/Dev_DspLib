#pragma once

/*==============================================================================
Signal history linear operator: a smoother.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"

#include "dspHistoryOperParms.h"
#include "dspHistoryOperBase.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a linear operator on the set of signal histories: the 
// moving average operator. It's a smoother.
 
class HistoryOperSmoother : public HistoryOperBase
{
public:
   typedef HistoryOperBase BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HistoryOperSmoother(HistoryOperParms& aParms);
   void show();

   // Apply the linear operator from the input to the output. F:X->Y
   // This is smoother.
   void operate(History& aX,History& aY) override;
};

//******************************************************************************
}//namespace

