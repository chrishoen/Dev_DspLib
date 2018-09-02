/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

#include "dspPdwFreeList.h"

namespace Dsp
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Regionals

static const int cAllocate = 10000;
static Pdw  mPdwArray[cAllocate];
static Pdw* mPointerStack[cAllocate];
static int  mStackIndex = 0;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Fill the pointer array with addresses of pdws in the pdw array.
// Set the index to the top of the stack, the stack is initially full.

void initializePdwFreeList()
{
   for (int i = 0; i < cAllocate; i++)
   {
      mPointerStack[i] = &mPdwArray[i];
   }
   mStackIndex = cAllocate-1;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Pop a pdw from the free list. Return null if the list is empty.

Pdw* allocatePdw()
{
   // If the free list is empty then return null.
   if (mStackIndex == 0)
   {
      printf("PDW FREE LIST EMPTY\n");
      return 0;
   }

   // Pop a pointer from the stack
   Pdw* tPdw = mPointerStack[mStackIndex--];

   return tPdw;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Push a pdw to the free list.

void freePdw(Pdw* aPdw)
{
   // Guard against no initialization.
   if (mStackIndex==0)
   {
      printf("PDW FREE LIST NOT INITIALIZED\n");
      return;
   }

   // If the free list is full then return.
   if (mStackIndex==cAllocate-1) return;

   // Push the pointer to the stack
   mPointerStack[++mStackIndex] = aPdw;
}

}//namespace

//******************************************************************************
/*
Stack <Element,Allocate>

This structure implements a stack of type Element and of size Allocate. It 
provides members that implement stack push and pop operations, which use 
element Tokens. It provides members that give direct access to the stack
push and pop elements so that pushes and pops can be performed with minimum
copying.

I  Index
PF PushFlag, if true then a push is allowed
GF PopFlag,  if true then a pop  is allowed
M  MaxNumOfElements

In the following example M=4

           +---+             GF = 0 
         3 |   |             PF = 1
           +---+              I = 0
         2 |   | 
           +---+   
         1 |   | 
           +---+   
         0 | I | P
           +---+   

           +---+             GF = 1 
         3 |   |             PF = 1
           +---+              I = 1
         2 |   |  
           +---+   
         1 | I | P
           +---+   
         0 | X | G
           +---+   

           +---+             GF = 1 
         3 |   |             PF = 1
           +---+              I = 2
         2 | I | P
           +---+   
         1 | X | G
           +---+   
         0 | X | 
           +---+   

           +---+             GF = 1 
         3 | I | P           PF = 1
           +---+              I = 3
         2 | X | G
           +---+   
         1 | X |  
           +---+   
         0 | X |  
           +---+   

             I
           +---+             GF = 1 
         3 | X | G           PF = 0
           +---+              I = 4
         2 | X | 
           +---+   
         1 | X | 
           +---+   
         0 | X |  
           +---+   
*/

 