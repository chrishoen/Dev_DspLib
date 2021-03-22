/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <algorithm>

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
   mValidFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize from a json file.

// Compare two pairs according to first values.
bool comparePairs(std::pair<double,double> p1, std::pair<double, double> p2)
{
   return (p1.first < p2.first);
} 

void CalTable::initialize(const char* aFilePath)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Read from the json file into a table vector.

   mValidFlag = false;

   try
   {
      // Read from the json file into a root json value.
      Json::Value tRoot;
      Ris::doReadJsonFromFile(tRoot, aFilePath);

      //std::cout << tRoot << std::endl;

      // Extract the table json value from the root json value.
      Json::Value tTable = tRoot["Table"];
      //std::cout << tTable << std::endl;

      // Extract the table vector from the table json value.
      mTable.clear();
      for (unsigned i = 0; i < tTable.size(); i++)
      {
         std::pair<double, double> tPair;
         tPair.first = tTable[i]["X"].asDouble();
         tPair.second = tTable[i]["Y"].asDouble();
         mTable.push_back(tPair);
      }

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Sort the table vector so that it is always monotonicaly increasing.

      std::sort(mTable.begin(), mTable.end(), comparePairs);

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Test that the table is monotonically increasing in X.

      // Test for monotonically increasing X.
      for (unsigned i = 0; i < mTable.size() - 1; i++)
      {
         if (mTable[i].first >= mTable[i + 1].first)
         {
            throw "NOT MONOTONIC INCREASE X";
         }
      }
   }
   catch (const char*& tString)
   {
      Prn::print(0, "CalTable EXCEPTION %s", tString);
      return;
   }
   catch (...)
   {
      Prn::print(0, "CalTable EXCEPTION");
      return;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   mValidFlag = true;
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
   Prn::print(0, "");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Get an interpolated y value from an input x value.

double CalTable::getYfromX(double aX)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Do this first.

   // Guard.
   if (!mValidFlag) return 0;

   // Locals.
   double tX0 = 0;
   double tX1 = 0;
   double tY0 = 0;
   double tY1 = 0;
   double tY = 0;
   int tBeginIndex = 0;
   int tEndIndex = (int)mTable.size() - 1;
   int tIndex = 0;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // If X is less than the begin X then extrapolate backwards.

   if (aX <= mTable[tBeginIndex].first)
   {
      tIndex = 0;
   }
      
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // If X is greater than the end X then extrapolate forwards.

   else if (aX >= mTable[tEndIndex].first)
   {
      tIndex = tEndIndex - 1;
   }
 
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // If X is located withing the table then find the bin that it is
   // located in.
   

   // If X is greater than the end X then return the end Y.
   else
   {

      // Loop to find the index that X is at.
      tIndex = 0;
      while (true)
      {
         // Guard. Exit the loop. This shouldn't happen.
         if (tIndex == tEndIndex) break;

         // If X is contained in the current bin then exit.
         if (aX >= mTable[tIndex].first && aX <= mTable[tIndex + 1].first) break;

         // Advance.
         tIndex++;
      }
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Interpolate the Y from the X.

   // Table bin values.
   tX0 = mTable[tIndex].first;
   tX1 = mTable[tIndex + 1].first;
   tY0 = mTable[tIndex].second;
   tY1 = mTable[tIndex + 1].second;

   // Calculate the linear interpolation.
   tY = tY0 + (aX - tX0) * (tY1 - tY0) / (tX1 - tX0);

   return tY;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

