/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "dsp_math.h"
#include "dspThreeAxisAngle.h"

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// 
ThreeAxisAngle::ThreeAxisAngle()
{
   mAxisX = 0.0;
   mAxisY = 0.0;
   mAxisZ = 0.0;
   mAngle = 0.0;
}

ThreeAxisAngle::ThreeAxisAngle(double aAxisX,double aAxisY,double aAxisZ,double aAngle)
{
   mAxisX = aAxisX;
   mAxisX = aAxisY;
   mAxisX = aAxisZ;
   mAngle = aAngle;
}

void ThreeAxisAngle::set(double aAxisX,double aAxisY,double aAxisZ,double aAngle)
{
   mAxisX = aAxisX;
   mAxisX = aAxisY;
   mAxisX = aAxisZ;
   mAngle = aAngle;
}

void ThreeAxisAngle::setToZero()
{
   mAxisX = 0.0;
   mAxisY = 0.0;
   mAxisZ = 0.0;
   mAngle = 0.0;
}

void ThreeAxisAngle::setIdentity()
{
   mAxisX = 0.0;
   mAxisY = 0.0;
   mAxisZ = 0.0;
   mAngle = 0.0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show

void ThreeAxisAngle::show(char* aLabel)
{
   printf("%-10s ",aLabel);
   printf("%11.6f ",mAxisX);
   printf("%11.6f ",mAxisY);
   printf("%11.6f ",mAxisZ);
   printf("%11.6f ",deg(mAngle));
   printf("\n");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

