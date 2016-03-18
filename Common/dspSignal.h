#ifndef _DSPSIGNAL_H_
#define _DSPSIGNAL_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a signal as a time series of samples.

class Signal
{
public:

   //--------------------------------------------------------------------------
   // Members.

   double* mX;            // Array of samples
   double  mFs;           // Sampling frequency
   double  mTs;           // Sampling period
   double  mFp;           // Carrier frequency 
   double  mTp;           // Carrier period
   double  mFm;           // Modulation frequency
   double  mTm;           // Modulation period
   double  mDuration;     // Time duration of signal
   int     mNumSamples;   // Number of samples in array
   int     mNs;           // Number of samples in array
   int     mNp;           // Number of samples in a carrier    period
   int     mNp1;          // Number of samples in a carrier    period sub interval 1
   int     mNp2;          // Number of samples in a carrier    period sub interval 2
   int     mNm;           // Number of samples in a modulation period 
   int     mNm1;          // Number of samples in a modulation period sub interval 1
   int     mNm2;          // Number of samples in a modulation period sub interval 2
   double  mDCp;          // Carrier    index = Np1/Np
   double  mDCm;          // Modulation index = Nm1/Nm

   //--------------------------------------------------------------------------
   // Constructor and initialization.
   // Create an new Signal, set some of the members, call initialize to 
   // set other members and allocate memory.

   Signal();
  ~Signal();
   void initialize();

   //--------------------------------------------------------------------------
   // Normalize the X value series.

   void normalize();

   //--------------------------------------------------------------------------
   // Write signal to a csv file.

   void writeToTextFile(char* aFileName);

   //--------------------------------------------------------------------------
   // Support.

   void show();
};

//******************************************************************************
}//namespace

#endif

