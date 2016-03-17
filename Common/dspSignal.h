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

class Signal
{
public:

   //--------------------------------------------------------------------------
   // Members

   char    mName[100];
   double* mX;
   double  mFs;
   double  mTs;
   double  mFp;
   double  mTp;
   double  mFm;
   double  mTm;
   double  mDuration;
   int     mNumSamples;
   int     mNs;
   int     mNp;
   int     mNp1;
   int     mNp2;
   int     mNm;
   int     mNm1;
   int     mNm2;
   double  mDCp;
   double  mDCm;
   double  mM1;
   double  mAlpha;

   //--------------------------------------------------------------------------
   // Constructor and initialization.
   // Create an new Signal, set some of the members, call initialize to 
   // set other members and allocate memory.

   Signal();
   void initialize();

   //--------------------------------------------------------------------------
   // Normalize the X value series.

   void normalize();

   //--------------------------------------------------------------------------
   // Support.

   void show();

   void writeToTextFile(char* aFileName);

};

//******************************************************************************
}//namespace

#endif

