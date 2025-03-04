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
   // This writes an element to the head of the queue.

   bool doPut (T& aValue)
   {
      // Copy the value into the element at the queue put index.
      mElement[mPutIndex % WinSize] = aValue;

      // Advance the put index.
      ++mPutIndex;

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
   // to the first gettable element.

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
0
1
2   put 101  
3   put 102
4   put 103
5   put 104     
6   put 105   get = 102
7             get = 103
8             get = 104
9             get = 105
7
8



#endif