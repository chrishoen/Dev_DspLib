#ifndef _BUTTERWORTHCO_H_
#define _BUTTERWORTHCO_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************

// n filter order
// s sampling frequency
// f half power cutoff frequency

int butterworthco(
   int     aN,
   double  aFs, 
   double  aFc,
   int*    aNb,
   int*    aNa,
   double* aB,
   double* aA);


#endif

