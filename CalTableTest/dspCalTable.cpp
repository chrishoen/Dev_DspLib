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

#include "dspCalTable.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Consructor.

CalTable::CalTable()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize from a json file.

void CalTable::initialize()
{
   // Read from the json file into a root json value.
   const char* tFilePath = "c:\\aaa_prime\\CalTable\\TestCalTable.json";
   Json::Value tRoot;
   Ris::doReadJsonFromFile(tRoot, tFilePath);

   std::cout << tRoot << std::endl;

   // Extract the table json value from the root json value.
   Json::Value tTable = tRoot["Table"];
   std::cout << tTable << std::endl;

   // Extract the table vector from the table json value.
   mTable.clear();
   for (unsigned i = 0; i < tTable.size(); i++)
   {
      std::pair<double, double> tPair;
      tPair.first = tTable[i]["X"].asDouble();
      tPair.second = tTable[i]["Y"].asDouble();
      mTable.push_back(tPair);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Helpers.

// Show.
void CalTable::show()
{
   for (int i = 0; i < mTable.size(); i++)
   {
      Prn::print(0, "%2d %.2f %.2f", i, mTable[i].first, mTable[i].second);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get an interpolated y value from an input x value.

double CalTable::getYfromX(double aX)
{
#if 0
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
#endif
   return 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

