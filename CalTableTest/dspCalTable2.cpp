/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <iostream>
#include <fstream>

#include "json.h"
#include "risFileFunctions.h"

#include "dspCalTable2.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Consructor.

CalTable2::CalTable2()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize from a json file.

void CalTable2::initialize()
{
   // Read from the json file into a json value.
   const char* tFilePath = "c:\\aaa_prime\\CalTable2\\TestCalTable2.json";
   Json::Value tRoot;
   Ris::doReadJsonFromFile(tRoot, tFilePath);
   
   // Extract the two arrays into two json array values.
   Json::Value tXArray = tRoot["XArray"];
   Json::Value tYArray = tRoot["YArray"];

   // Extract the two json array values into the two array vectors.
   mXArray.clear();
   mYArray.clear();
   for (unsigned i = 0; i < tXArray.size(); i++)
   {
      mXArray.push_back(tXArray[i].asDouble());
      mYArray.push_back(tYArray[i].asDouble());
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

// Show.
void CalTable2::show()
{
   for (int i = 0; i < mXArray.size(); i++)
   {
      Prn::print(0, "%2d %.2f %.2f", i, mXArray[i], mYArray[i]);
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get an interpolated y value from an input x value.

double CalTable2::getYfromX(double aX)
{
   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Find the bin that X is located in.
   
   // Locals.
   int tBeginIndex = 0;
   int tEndIndex = (int)mXArray.size() - 1;

   // If X is less than the begin X then return the begin Y.
   if (aX <= mXArray[tBeginIndex]) return mYArray[tBeginIndex];

   // If X is greater than the end X then return the end Y.
   if (aX >= mXArray[tEndIndex]) return mYArray[tEndIndex];

   // Loop to find the index that X is at.
   int tIndex = 0;
   while (true)
   {
      // Guard. Exit the loop. This shouldn't happen.
      if (tIndex == tEndIndex) break;

      // If X is contained in the current bin then exit.
      if (aX >= mXArray[tIndex] && aX <= mXArray[tIndex + 1]) break;

      // Advance.
      tIndex++;
   }

   Prn::print(0, "Found X %d", tIndex);

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // Interpolate the Y from the X.

   // Locals.
   double tX0 = mXArray[tIndex];
   double tX1 = mXArray[tIndex + 1];
   double tY0 = mYArray[tIndex];
   double tY1 = mYArray[tIndex + 1];

   // Calculate the linear interpolation.
   double tY = tY0 + (aX - tX0) * (tY1 - tY0) / (tX1 - tX0);

   return tY;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

