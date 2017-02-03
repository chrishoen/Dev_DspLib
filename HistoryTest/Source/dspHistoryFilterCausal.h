#pragma once

/*==============================================================================
Signal history linear operator: the identity operator.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspHistoryFilterParms.h"
#include "dspHistory.h"
#include "dspFilterButterworth.h"

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
// This class provides a linear operator on the set of signal histories:  
// It applies some recursive filters causally.
 
class HistoryFilterCausal
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Parameters. These are read from a parms file.

   HistoryFilterParms mParms;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   Dsp::Filter::ButterworthLP mFilter;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HistoryFilterCausal(HistoryFilterParms& aParms);
   void show();

   // Apply the linear operator from the input to the output. F:X->Y
   // This is the identity operator.
   void operate(History& aX,History& aY);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Calculate the central difference filter coefficents, based on the parms.
   // This coefficients are used to calculate a smoothed output.
   void initializeFilter();
};

//******************************************************************************
}//namespace


