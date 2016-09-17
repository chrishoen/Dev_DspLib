#ifndef _DSPFILTERBUTTERWORTH_H_
#define _DSPFILTERBUTTERWORTH_H_
/*==============================================================================

filters
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspFilterFilters.h"

namespace Dsp
{
namespace Filter
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Butterworth low pass IIR filter
//
// N        Filter order 2,4,6..
// Fs       Sampling frequency
// Fc       Cutoff frequency

class ButterworthLP : public IIRFilter
{
public:
   // Initialize
   void initialize(int aNOrder, double aFs, double aFc);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Butterworth band pass IIR filter
//
// N        Filter order 2,4,6..
// Fs       Sampling frequency
// Fc1      Cutoff frequency
// Fc2      Cutoff frequency

class ButterworthBP : public IIRFilter
{
public:
   // Initialize
   void initialize(int aNOrder, double aFs, double aFc1, double aFc2);
};

}//namespace
}//namespace
#endif

