#ifndef _DSPPDWSEQUENCE_H_
#define _DSPPDWSEQUENCE_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "dspPdw.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class PdwSequence
{
public:

   //--------------------------------------------------------------------------
   // Constructor

   PdwSequence();
  ~PdwSequence();

   //--------------------------------------------------------------------------
   // Reset paramters to defaults.

   void reset();

   //--------------------------------------------------------------------------
   // Parameters

   double  mFs;
   double  mTs;
   double  mFm;
   double  mTm;
   double  mDuration;
   int     mNumSamples;
   int     mNs;
   int     mNm;
   int     mNm1;
   int     mNm2;
   double  mDCm;

   static const int cMaxStringSize=400;

   char mPdwFileName  [cMaxStringSize];
   char mPlotFileName [cMaxStringSize];

   void setPdwFileName  (char* aFileName);
   void setPlotFileName (char* aFileName);
   
   //--------------------------------------------------------------------------
   // Initialize, using parameters.

   void initialize();

   //--------------------------------------------------------------------------
   // Members

   static const int cMaxNumOfPdws=10000;
   Pdw* mPdwArray;
   int mPdwCount;

   //--------------------------------------------------------------------------
   // Put a Pdw to the PdwArray.

   void putPdw(Pdw* aPdw);

   //--------------------------------------------------------------------------
   // Write signal to a csv file.

   void writeToTextFile();

   //--------------------------------------------------------------------------
   // Support.

   void show();
};

//******************************************************************************
}//namespace

#endif

