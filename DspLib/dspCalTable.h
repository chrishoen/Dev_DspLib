#pragma once

/*==============================================================================
calibration table
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <utility>
#include <vector>

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides a one dimensional calibration table. It contains a
// list of x,y pairs and provides a function that uses it to interpolate
// from x to y.

class  CalTable
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // True if the calibration table is valid.
   bool mValidFlag;

   // Table of calibration x,y pairs.
   std::vector<std::pair<double,double>> mTable;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Consructor.
   CalTable();

   // Initialize from vector of pairs.
   void initialize(const std::vector<std::pair<double, double>>& aTableData);

   // Get an interpolated y value from an input x value.
   double getYfromX(double aX);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Show.
   void show(int aPrintFilter);
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace


