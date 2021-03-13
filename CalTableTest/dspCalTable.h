#pragma once

/*==============================================================================

lookup tables
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <vector>

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class  CalTable
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   std::vector<float> mXArray;
   std::vector<float> mYArray;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Consructor.
   CalTable();

   // Initialize from a json file.
   void initialize();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



