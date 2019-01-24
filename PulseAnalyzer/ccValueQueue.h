#pragma once

/*==============================================================================

Template for queue of values

==============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a class template for a queue of values, as opposed to blocks.

template <class Element>
class ValueQueue
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   int mAllocate;
   int mPutIndex;
   int mGetIndex;

   Element* mElement;
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor, initialize members for an empty queue of size zero 
   ValueQueue()
   {
      // All null
      mAllocate = 0;
      mPutIndex = 0;
      mGetIndex = 0;
      mElement  = 0;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Destructor, deallocate the queue array

  ~ValueQueue()
   {
     // Deallocate the array
     if (mElement) delete mElement;
   }

  //***************************************************************************
  //***************************************************************************
  //***************************************************************************
   // This initializes the queue to a fixed size. It initializes member
   // variables and allocates heap storage for the queue array. The queue has
   // a specified maximum number of elements and it allocates memory for the
   // maximum number of elements plus one, there is an extra element allocated.

   void initialize(int aMaxNumOfElements)
   {
      // Initialize variables
      mPutIndex = 0;
      mGetIndex = 0;
      // Allocate memory for the array to have an extra element
      mAllocate = aMaxNumOfElements + 1;

      // Allocate memory for the array
      mElement = new Element[mAllocate];
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns true if put operations are allowed. Puts are allowed if the 
   // current size is less than or equal to Allocate - 2. If the size is equal
   // to Allocate - 2 then the next put operation would put the size to
   // Allocate - 1, which is the max number of elements. This is the same as
   // "is not full".

   bool isPut ()
   {
      int tSize = mPutIndex - mGetIndex;
      if (tSize < 0) tSize = mAllocate + tSize;
      return tSize <= mAllocate - 2;
   }
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This is executed after a put operation to advance the queue put index to
   // point to the next element to put to. It uses a temp variable so that
   //  writing to the index is atomic.

   void nextPut ()
   {
      int tPutIndex = mPutIndex;
      if(++tPutIndex == mAllocate) tPutIndex = 0;
      mPutIndex = tPutIndex;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This puts an element to the queue and advances the put index. It does a 
   // copy from a source element into the queue array element at the put index.
   // It uses a temp index variable so that writing to the index is atomic.
   // Note that the source element must be of element size.

   void put (Element aElement)
   {
      // Local put index
      int tPutIndex = mPutIndex;
      // Copy the source element into the element at the queue put index
      mElement[tPutIndex] = aElement;
      // Advance the put index
      if(++tPutIndex == mAllocate) tPutIndex = 0;
      mPutIndex = tPutIndex;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns a pointer to the current queue element to put to. It is
   // provided to give direct access to the put element to minimize copies. If
   // an element is put directly to the queue array by using this pointer then 
   // nextPut should be called after the put operation.

   Element& elementToPut ()
   {
      return mElement[mPutIndex];
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns true if get operations are allowed. Gets are allowed if the 
   // current size is greater than zero. This is the same as "is not empty".

   bool isGet ()
   {
      int tSize = mPutIndex - mGetIndex;
      if (tSize < 0) tSize = mAllocate + tSize;
      return tSize > 0;
   }
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This is executed after a get operation to advance the queue get index to
   // point to the next element to get from. It uses a temp index variable so
   // that writing to the index is atomic.

   void nextGet()
   {
      int tGetIndex = mGetIndex;
      if(++tGetIndex == mAllocate) tGetIndex = 0;
      mGetIndex = tGetIndex;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This gets an element from the queue and advances the get index. It does a 
   // copy from the queue array element at the get index into a destination
   // element. It uses a temp index variable so that writing to the index is
   // atomic. Note that the destination element must be of element size.

   Element get()
   {
      // Local index
      int tGetIndex = mGetIndex;
      // Store the queue array element at the get index
      Element tElement = mElement[tGetIndex];
      // Advance the get index
      if(++tGetIndex == mAllocate) tGetIndex = 0;
      mGetIndex = tGetIndex;
      // Return the element
      return tElement;
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This returns a pointer to the current queue element to get from. It is
   // provided to give direct access to the get element to minimize copies. If
   // an element is gotten directly from the queue array by using this pointer
   // then nextGet should be called after the get operation.

   Element& elementToGet()
   {
      return mElement[mGetIndex];
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // This is the current size of the queue. It is the difference between the 
   // mPutIndex and the mGetIndex.

   int size()
   {
      int tSize = mPutIndex - mGetIndex;
      if (tSize < 0) tSize = mAllocate + tSize;
      return tSize;
   }

   bool isEmpty()
   {
      return size()==0;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace



#if 0
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// class template Queue <Element,NumOfElements>
//
// This structure implements a queue of type Element and of size NumOfElements.
// It provides queue creation and destruction and queue put and get operations.
// It is thread safe such that it can be used between two threads or isrs where 
// one does queue puts and the other one does queue gets and that one thread
// can preempt the other one. It does this without using any os synchronization
// objects such as mutexes. It implements the thread safety by using separate
// put and get indices and by being careful on having the put operation read
// the get index and write to the put index. Likewise for get operations.
// Because of the thread safety, it allocates memory for one more than the 
// NumOfElements so that there is an extra element between put and get
// operations.
//
// The structure has the following members:
//******************************************************************************
// This is the number of elements allocated for the queue. Allocate is one 
// greater than the max number of elements so that there is one extra element 
// so that get operations will not interfere with interrupting put operations. 
// It is the number of elements to which memory is allocated
// 
//    Allocate = NumOfElements + 1
//    allocated storage = Allocate*ElementSize
//
//******************************************************************************
// This is the array index of the back of the queue, where put operations take
// place.
// 
//    0 =< PutIndex =< Allocate - 1
//
//******************************************************************************
// This is the array index of the front of the queue, where get operations take 
// place.
// 
//    0 =< GetIndex =< Allocate - 1
//
//******************************************************************************
// This is a pointer to allocated storage
// 
//    ElementStore = malloc (Allocate*ElementSize)

//******************************************************************************
// This is the queue class template
/*==============================================================================

Queue<Element,Allocate>
This structure implements a queue of type Element and of size NumOfElements.
It provides queue creation and destruction and queue put and get operations.
It is thread safe such that it can be used between two threads or isrs where 
one does queue puts and the other one does queue gets and that one thread
can preempt the other one. It does this without using any os synchronization
objects such as mutexes. It implements the thread safety by using separate
put and get indices and by being careful on having the put operation read
the get index and write to the put index. Likewise for get operations.
Because of the thread safety, it allocates memory for one more than the 
NumOfElements so that there is an extra element between put and get
operations.

P  PutIndex
G  GetIndex
S  Size
PF PutFlag
GF GetFlag
M  MaxNumOfElements
A  Allocate

In the followinng example M=3,A=4

            PG               PF = 1
           +---+             GF = 0
       +---|   |---+         S  = 0
       |   +---+   |
       |           | 
     +---+       +---+
     |   |       |   |
     +---+       +---+
       |           |  
       |   +---+   |
       +---|   |---+
           +---+

             G               PF = 1
           +---+             GF = 1
       +---| X |---+         S  = 1
       |   +---+   |
       |           | 
     +---+       +---+
     |   |       |   |P
     +---+       +---+
       |           |  
       |   +---+   |
       +---|   |---+
           +---+

             G               PF = 1
           +---+             GF = 1
       +---| X |---+         S  = 2
       |   +---+   |
       |           | 
     +---+       +---+
     |   |       | X |
     +---+       +---+
       |           |  
       |   +---+   |
       +---|   |---+
           +---+
             P  

             G               PF = 0
           +---+             GF = 1 
       +---| X |---+         S  = 3
       |   +---+   |
       |           | 
     +---+       +---+
    P|   |       | X |
     +---+       +---+
       |           |  
       |   +---+   |
       +---| X |---+
           +---+
               
             PG 
           +---+
       +---| X |---+
       |   +---+   |
       |           | 
     +---+       +---+
     | X |       | X |    Not Allowed
     +---+       +---+
       |           |  
       |   +---+   |
       +---| X |---+
           +---+
               


A=M+1;

S=P-G;
if(S<0) S=A+S;

PF = S=<A-2;
GF = S>0;

tP = P;
if (++tP==A) tP=0;
P = tP;

likewise G;



******************************************************************************
******************************************************************************
******************************************************************************
 Overview

This file is the the header and template definition file for a set of
class templates that define array container classes. The array
container classes are based on statically allocated arrays of
elements.  The elements are either scalars or other
containers. Containers that are currently defined are lists, queues,
stacks, and other containers that are based on them.

Lists are arrays of elements that provide Put and Get operations to
sequentially move elements into the array and then sequentially move
elements out of the array. Lists are used to transfer data between a
producer and a consumer. The producer resets the list, performs a
sequence of Put operations on the list, and passes access to the
consumer. The consumer then performs a sequence of Get operations on
the list. Producers and consumers do not perform concurrent Puts and
Gets on a list.

Lists provide state variables that indicate whether or not Put
operations are enabled (the list is not full) and state variables that
indicate whether or not Get operations are enabled (the list is not
empty). Lists also provide state variables that are used as Put and
Get array indices. Lists contain a dual finite state machine that
implements Put and Get logic on the state variables.

Queues are arrays of elements that implement FIFOs. They provide Put
and Get operations to concurrently move elements into and out of the
array. Puts are done at the back of the queue and gets are done from
the front of the queue.

Queues provide state variables that indicate whether or not Put
operations are enabled (the queue is not full) and state variables
that indicate whether or not Get operations are enabled (the queue is
not empty). Queues also provide state variables that are used as front
and back array indices.

Queues are implemented in such a way that a queue can be used
concurrently between two threads, one of which only does queue Puts
and one of which only does queue Gets. The implementation is such that
mutual exclusion semaphores are not needed. If there are more than two
threads then semaphores are needed.

Stacks are arrays of elements that implement LIFOs. They provide Put
and Get operations to concurrently move elements into and out of the
array.

// Class Summary

BaseContainer
This is a base class for all container classes. It provides a
set of attribute member variables that are common to all containers.
The attributes maintain container status.

Array<Element,Allocate>
This class template implements an array of type Element and of size
Allocate. Container classes use the array as storage.  The array is
allocated statically at object instantiation and does not use the new
operator or any type of dynamic memory allocation.

List<Element,Allocate>
This class template implements a list of type Element and of size
Allocate. It provides members that support list Put and Get
operations, which are common to all list classes.


Trace <Element,Allocate>
This class template implements a shift register of type Element and
of size Allocate. It is used to store the last Allocate values of an
object. It traces the history of an object with a sliding window of
it's last Allocate values. It is implemented as a queue that, if it is
full after a put opertion then a Get operation on the front value is
performed automatically.


Stack<Element,Allocate>
This class template implements a stack of type Element and of size
Allocate. It provides members that support list Put and Get
operations, which are common to all stack classes.

Update<Element>
This class template implements a double buffer of type Element that
provides the most recent update of an object. The double buffer is
implemented in such a way that it can be used to transfer data from
one thread to another, in only one direction, such that it provides
the most recent update of a status object from a producer to a
consumer.  The producer puts it's most recent status to the object and
the consumer asynchronously gets the status. The producer can put it's
status at the same time that the consumer gets it, with a lock
mechanism providing mutual exclusion protection. It can be used to
transfer data from one thread to another without using mutual
exclusion semaphores. Mutual exclusion is implemented by disabling
interrupts for short periods of time. It provides members that
implement double buffer Put and Get operations.

Double<Element>
This class template implements a double buffer of type Element that
provides the an element to put to and an element to get, which is the
last element that was put to.

Allocator<Allocate> 
This class template implements a resource allocator and it it used to
allocate and deallocate the members of a finite resource set with size
Allocate.  It is implemented as a stack of resource tokens (ints) that
is reset to full (Put 0,1,2,3..Allocate-1), there being one element
for each available resource. To allocate a resource Get a token from
the stack and to deallocate a resource Put the token back on the
stack.

MemHeap<Element,Allocate>
This class template implements a heap of type Element and of size
Allocate. It is used for dynamic memory allocation of objects of type
Element that is fast and does not fragment. It allocates a static
array of type Element and of size Allocate and provides a resource
allocator to allocate and deallocate array elements. Type Element is a
class that inherits from BaseContainer and it overloads the new and
delete operators.

// Examples

// data to   a list from stdin

This example shows data input to a list from stdin.
Bytes come in from stdin until the list is full.

The loop continues to put bytes to the list until it
is no longer put enabled.

ByteList<256> ByteListRx;

void GetByteListInput(ByteListRx& BytesRx)
{
 BytesRx.reset();
 while(BytesRx.isPut()) BytesRx.Put(getch());
}

// data to   a list from stdin

This example shows data input to a list from stdin.
Bytes come in from stdin until the list is full or
escape is entered.

The loop continues to put bytes to the list until it
is no longer put enabled.

ByteList<256> ByteListRx;

void GetByteListInput(ByteListRx& BytesRx)
{
 unsigned char Byte;
 BytesRx.reset();
 while(BytesRx.isPut()){
    Byte = getch();
    if(Byte!=27) BytesRx.Put(Byte);
    else         BytesRx.stopPut();}
}

// data from a list to   stdout

This example shows data output from a list to stdout.
Bytes are extracted from the list and output to 
stdout until the list is empty.

The loop continues to get bytes from the list until it
is no longer get enabled. The loop gets a byte from the 
list and sends it to stdout.

ByteList<256> ByteListRx;

void GetByteListOutput(ByteListRx& BytesRx)
{
 BytesRx.StartGet();
 while(BytesRx.isGetAvailable()) putch(BytesRx.Get());
}

// data from a list to a list

This example shows data transferred from one list
to another. Data is transferred until either the
source is empty or the destination is full.

ByteList<256> ByteListTx;
ByteList<256> ByteListRx;

void Transfer(ByteListRx& Source,ByteListRx& Destin)
{
 Source.StartGet();
 Destin.reset(); 
 while(Source.isGetAvailable() && Destin.isPut())
    Destin.Put(Source.Get());
}

// data from a file to a list

This example shows data transferred from a file
input directly into a byte list.

typedef ByteList<1024> SFileList;
SFileList FileList;

void TransferFileToList(SFileList& List)
{
 List.reset();
 List.mPutIndex = getfile(List.Array);
}

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
// class template Array <Element,Allocate>

// This class template implements an array of type Element and of size
// Allocate. Container classes use the array as storage.  The array is
// allocated statically at object instantiation and does not use the new
// operator or any type of dynamic memory allocation.
// 
// Array classes have member variables mBeginIndex and mEndIndex that are
// lower and upper bounds on array elements that can contain valid
// data. Data indices can access array data in the closed interval
// [mBeginIndex,mEndIndex] where
// 
//   0 =< mBeginIndex =< DataIndex =< mEndIndex =< Allocate-1
// 
// This feature is provided to implement objects that have header storage
// allocated at the beginning of the array and have variable length
// maximum transmission unit size which can be less than Allocate.

#endif

