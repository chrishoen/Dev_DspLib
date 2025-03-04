#pragma once

/*==============================================================================

Sliding window memory structure class template. 

It is not thread safe.
It is not shared memory safe.

==============================================================================*/
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This template implements an N element memory structure of type T that
// provides a fixed delay. It can be used for digital filters.

template <class T,int WinSize>
class SlidingWindow 
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Index of the next element to put to. This increments indefinitely 
   // with every put operation. 
   int mPutIndex;

   // If true then the array is full.
   bool mFullFlag;

   // If true then the array is empty.
   bool mEmptyFlag;

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
      mEmptyFlag = true;
      mSize = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This writes an element to the head of the array.

   bool doPut (T& aValue)
   {
      // Copy the value into the element at the queue put index.
      mElement[mPutIndex] = aValue;

      // Advance the put index.
      if (++mPutIndex == WinSize) mPutIndex = 0;

      // Advance the size.
      if (++mSize > WinSize) mSize = WinSize;

      // Set the flags.
      mEmptyFlag = false;
      mFullFlag = mPutIndex >= WinSize;
      return mFullFlag;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns a pointer to an element that is relative
   // to the first gettable element. Index 0 is the most recent.
   // Index WinSize-1 is the least recent.

   T& elementAt(int aIndex)
   {
      // If try to access past the last element then return the last element.
      if (aIndex > mSize - 1) aIndex = mSize - 1;
      
      // Calculate the get index.
      int tGetIndex = (WinSize + mPutIndex - 1 - aIndex) % WinSize;

      // Return the element at the get index.
      return mElement[tGetIndex];
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
6  2  put 106    get 0 = 106
7  3             get 1 = 105
8  0             get 2 = 104
9  1             get 3 = 103
7  2
8  3



#endif

#if 0
void show()
{
   printf("PutIndex %d %d\n", mPutIndex, mSize);
   for (int i=0;i<WinSize;i++)
   {
      printf("element %d $ %d\n", i, mElement[i]);
   }
}
#endif
