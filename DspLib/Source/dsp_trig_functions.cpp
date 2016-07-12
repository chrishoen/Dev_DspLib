/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dspDefs.h"
#include "dsp_trig_functions.h"


//******************************************************************************
//******************************************************************************
//******************************************************************************
// 

double dsp_cos_deg   (double x) { return cos (x*DSP_RAD); }
double dsp_sin_deg   (double x) { return sin (x*DSP_RAD); }
double dsp_tan_deg   (double x) { return tan (x*DSP_RAD); }

double dsp_acos_deg  (double x) { return DSP_DEG*acos(x); }
double dsp_asin_deg  (double x) { return DSP_DEG*asin(x); }
double dsp_atan_deg  (double x) { return DSP_DEG*atan(x); }

double dsp_atan2_deg(double y, double x) { return DSP_DEG*atan2(y, x); }


void dsp_format_180_deg (double* x)
{ 
   if (*x >=  180.0) *x -= 360.0;
   if (*x <  -180.0) *x += 360.0;
}

void dsp_format_360_deg (double* x)
{ 
   if (*x >=  360.0) *x -= 360.0;
   if (*x <     0.0) *x += 360.0;
}

