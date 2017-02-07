#pragma once

/*==============================================================================
History delay estimator
==============================================================================*/
#include "dspGoldSearch.h"
#include "dspHistory.h"

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
// Signal history delay estimator. Estimate the delay between two similar 
// signals. This performs a golden section search using a least squares error
// function. It finds then delay between two signals that gives the minimum
// least squared error of the difference between them. This inherits from
// the search base class to implement the search, providing an override for
// the error function that is evaluated during the search.

class HistoryDelayEstimator : public Dsp::GoldSearchBase
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.
   // These are stored from the search function and read by the error function.

   // Two signal histories that are compared.
   History* mHistory1;
   History* mHistory2;

   // Evaluation sampling frequency.
   double   mSearchFs;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.
   // Output variables.

   double mDelayEstimate;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructor and initialization.

   // Constructor.
   typedef Dsp::GoldSearchBase BaseClass;
   HistoryDelayEstimator();
   void reset();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Perform the search.

   // Perform the search. Find the delay that minimizes the error function.
   double search(
      History* aHistory1,
      History* aHistory2,
      double   aSearchFs,
      double   aSearchDelay,
      double   aSearchTolerance,
      int      aSearchMaxIterations);

   // f(x). Error function. x is the variable delay.
   // Return the sum of the square of the difference between the two
   // histories, one is evaluated at time t and the other is evaluated at
   // time t + delay.
   double function(double aX) override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // More.

};

//******************************************************************************
}//namespace

