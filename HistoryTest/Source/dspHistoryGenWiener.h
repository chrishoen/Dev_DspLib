#ifndef _DSPHISTORYGENWIENER_H_
#define _DSPHISTORYGENWIENER_H_

/*==============================================================================
Signal history generator with a wiener process.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risCmdLineExec.h"

#include "dspHistoryGenParms.h"
#include "dspHistoryGenBaseGN.h"
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
// This class provides a generator for a signal history that evolves according
// to an integrated wiener process. The signal history is implemented by low
// pass filtering gaussian noise with a butterworth filter with a specified
// cutoff frequency. The history is then normalized to have a specified
// expectation and uncertainty.
 
class HistoryGenWiener : public HistoryGenBaseGN
{
public:
   typedef HistoryGenBaseGN BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Input parameters.
   HistoryGenParms mParms;

   // Low pass butterworth filter.
   Filter::ButterworthLP mFilter;

   //--------------------------------------------------------------------------
   // Constructor.

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   HistoryGenWiener();
   HistoryGenWiener(HistoryGenParms& aParms);
   void reset();
   void show();

   // Generate the signal history according to the parameters.
   void generateHistoryType1(History& aHistory);   
   void generateHistoryType2(History& aHistory);


};

//******************************************************************************
}//namespace

#endif

