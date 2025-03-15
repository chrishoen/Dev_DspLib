#pragma once

/*==============================================================================
==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This template implements a sliding window that maintains a history
// of input values.

template <class T,int WinSize>
class SlidingWindow 
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Index of the next element to put to. [0..WinSize-1]
   int mPutIndex;

   // If true then the array is full.
   bool mFullFlag;

   // Number of array occupied elements.
   int mSize;

   // Array of elements.
   T mElement[WinSize];

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   SlidingWindow()
   {
      reset();
   }

   void reset()
   {
      mPutIndex = 0;
      mFullFlag = false;
      mSize = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Put.

   // Write an element to the array at the put index and advance
   // the put index. Return true if full.
   bool doPut (T& aValue)
   {
      // Copy the value into the element at the put index.
      mElement[mPutIndex] = aValue;

      // Advance the put index.
      if (++mPutIndex == WinSize) mPutIndex = 0;

      // Advance the size.
      if (++mSize > WinSize) mSize = WinSize;

      // Set the flags.
      mFullFlag = mSize == WinSize;
      return mFullFlag;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Get.

   // Return a reference to an element that is relative to the first
   // gettable element. The first gettable element is the last element
   // that was put. Index 0 is the most recent. Index WinSize-1 is the
   // least recent.
   T& elementAt(int aIndex)
   {
      // If try to access past the last element then return the last element.
      if (aIndex > mSize - 1) aIndex = mSize - 1;
      
      // Calculate the get index.
      int tGetIndex = (WinSize + mPutIndex - 1 - aIndex) % WinSize;

      // Return the element at the get index.
      return mElement[tGetIndex];
   }

   // Return a reference to the head element.
   T& elementAtHead()
   {
      return elementAt(0);
   }

   // Return a reference to the tail element.
   T& elementAtTail()
   {
      int tTailIndex = mSize > 0 ? mSize - 1 : 0; 
      return elementAt(tTailIndex);
   } 
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

#if 0

SlidingWindow<int, 4>

PutIndex
0  0  put 101
1  1  put 102
2  2  put 103  
3  3  put 104
4  0  put 105
6  2  put 106    get 0 = 106   most recent, youngest
7  3             get 1 = 105
8  0             get 2 = 104
9  1             get 3 = 103   least recent, oldest
7  2
8  3



#endif

