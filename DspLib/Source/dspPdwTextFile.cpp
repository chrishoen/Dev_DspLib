/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <stdio.h>

#include "dspPdwFreeList.h"
#include "dspPdwTextFile.h"

namespace Dsp
{


//******************************************************************************
//******************************************************************************
//******************************************************************************
// Read a row from a pdw csv file, allocate a new pdw from the
// pdw free list, populate it, and return it.

Pdw* PdwCsvFileReader::readPdw()
{
   // Read a row from the file
   if(!readRow()) return 0;

   // Allocate a pdw from the free list.
   Pdw* tPdw = allocatePdw();

   // Guard
   if (tPdw == 0) return 0;

   // Populate pdw values.
   tPdw->mIndex  = mRowIndex;
   tPdw->mSeqNum = 0;
   tPdw->mToa        = mValues[0];
   tPdw->mAmplitude  = mValues[1];
   tPdw->mPulseWidth = 0.0;

   // Done
   return tPdw;
}

}//namespace