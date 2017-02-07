/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dsp_math.h"
#include "dspStatistics.h"
#include "dspGoldSearch.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor

GoldSearchBase::GoldSearchBase()
{
   reset();
}

void GoldSearchBase::reset()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Perform the search.

double GoldSearchBase::search(
      double aXAinitial,
      double aXBinitial,
      double aTolerance,
      int    aMaxIterations)
{
  double a   = aXAinitial;
  double b   = aXBinitial;
  double tol = aTolerance;

  double gr = (sqrt(5) + 1) / 2;

  double c = b - (b - a) / gr;
  double d = a + (b - a) / gr; 

  int tCount = 0;

  printf("GSS %10.6f %10.6f %10.6f %10.6f %10.6f\n", a,b,c,d,tol);
  printf("\n");

  double fmin_1;

  while (1)
  {
     printf("GSS %3d $$ %10.6f %10.6f %10.6f %10.6f\n", tCount,a,b,c,d);

     if (fabs(c - d) <= tol)
     {
        double x = (b + a) / 2;
        printf("GSS PASS %d $$ %10.6f\n", tCount,x);
        return x;
     }

     if (++tCount > aMaxIterations)
     {
        printf("GSS FAIL\n");
        return 0.0;
     }

     double fc = function(c);
     double fd = function(d);

#if 0
     // Check in case not unimodal.
     double fmin = fc < fd ? fc : fd;
     if (tCount > 1)
     {
         if (fmin > fmin_1) 
         {
            double x = (b + a) / 2;
            printf("GSS ABORT %d $$ %10.6f\n", tCount,x);
            return x;
         }
     }
     fmin_1 = fmin;
#endif
     if (fc < fd)
     {
        b = d;
     }
     else
     {
        a = c;
     }

     c = b - (b - a) / gr;
     d = a + (b - a) / gr; 
  }

}
   
}//namespace