#ifndef _PDWFREELIST_H_
#define _PDWFREELIST_H_
/*==============================================================================

This defines a global free list of pdws. It is used as a pdw memory pool.
It contains a statically allocated array of pdws and a statically allocated
stack of pointers into the pdw array. It is not thread safe. It is the
simplest possible memory pool.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "dspPdw.h"

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************

   // Initialize the free list.
   void initializePdwFreeList();

   // Pop a pdw from the free list. Return null if the list is empty.
   Pdw* allocatePdw();

   // Push a pdw to the free list.
   void freePdw(Pdw* aPdw);

}//namespace
#endif

