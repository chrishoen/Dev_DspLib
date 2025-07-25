//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include "json.h"
#include "risFileFunctions.h"

#include "MyCalTable.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

MyCalTable::MyCalTable()
{
   mValidFlag = false;
   if (Ris::portableIsWindows())
   {
      strcpy(mFilePath, "c:\\aaa_prime\\CalTable\\TestCalTable.json");
   }
   else
   {
      strcpy(mFilePath, "/opt/files/hlccal.json");
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read json file and initialize the cal table.

void MyCalTable::initialize()
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
      Ris::doReadJsonFromFile(tRoot, mFilePath);

      //std::cout << tRoot << std::endl;

      // Extract the table json value from the root json value.
      Json::Value tTable = tRoot["Table"];
      //std::cout << tTable << std::endl;

      // Extract the table vector from the table json value.
      mTableData.clear();
      for (unsigned i = 0; i < tTable.size(); i++)
      {
         std::pair<double, double> tPair;
         tPair.first = tTable[i]["X"].asDouble();
         tPair.second = tTable[i]["Y"].asDouble();
         mTableData.push_back(tPair);
      }


      // Initialize the cal table with the table vector.
      mTable.initialize(mTableData);

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Sort the table vector so that it is always monotonicaly increasing.

   }
   catch (const char*& tString)
   {
      Prn::print(0, "MyCalTable EXCEPTION %s", tString);
      return;
   }
   catch (...)
   {
      Prn::print(0, "MyCalTable EXCEPTION");
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
// Get an interpolated y value from an input x value.

double MyCalTable::getYfromX(double aX)
{
   return mTable.getYfromX(aX);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void MyCalTable::show(int aPF)
{
   if (!Prn::getFilter(aPF)) return;
   Prn::print(aPF, "");
   Prn::print(aPF, "FilePath %s", mFilePath);
   mTable.show(aPF);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

