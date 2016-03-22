#ifndef _DSPSAMPLE_H_
#define _DSPSAMPLE_H_

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

class Sample
{
public:

   //--------------------------------------------------------------------------
   // Constructors

   Sample();

   //--------------------------------------------------------------------------
   // Convert and store

   void put(double aTime,double aVolts);

   //--------------------------------------------------------------------------
   // Sample time and amplitude

   double  mTime;
   double  mVolts;
   double  mAmplitude;
   
};

//******************************************************************************
}//namespace

#endif

