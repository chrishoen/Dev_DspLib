#ifndef _BUTTERWORTHCO_H_
#define _BUTTERWORTHCO_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************

// n filter order
// s sampling frequency
// f half power cutoff frequency

int butterworthco(int aN,double aFs, double aFc, bool aScale, char* aOutputfile);

#endif

