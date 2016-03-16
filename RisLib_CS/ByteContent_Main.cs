using System;
using System.Text;
using System.IO;

namespace Ris
{
    //******************************************************************************
    //******************************************************************************
    //******************************************************************************
    // This is a base class for classes that can be copied to/from ByteBuffers.
    // Each inheriting class supplies a copyToFrom member function that can be
    // called by ByteBuffer put and get functions to copy it.

    public class ByteContent
    {
        // This is supplied by each particular inheriting class to copy itself
        // to/from a byte buffer.

        public virtual void copyToFrom(ByteBuffer aBuffer) { }

        // General purpose identifier
        public int mMessageType;

        // Constructor
        public ByteContent()
        {
            mMessageType = 0;
        }
    };

    //******************************************************************************
    //******************************************************************************
    //******************************************************************************
    // This class encapsualtes byte buffers. It represents memory sections. It
    // provides member functions to do some simple memory management for a buffer.
    // It provides primitive data type put and get operations that allow primitives
    // to be copied to/from a byte buffer in network order. It also provides "copy"
    // member functions that either put to a buffer or get from a buffer, based on
    // a copy direction flag.
    //
    // This class maintains a buffer base pointer, which contains the base address
    // of the buffer, a buffer working pointer, which contains an addresss within
    // the buffer where the next put or get operation will be performed. It also
    // maintains a buffer length, which contains the number of bytes that have
    // been put into the buffer.

    public partial class ByteBuffer
    {
        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        // Members

        //---------------------------------------------------------------------------
        // Pointer members.
        // The base pointer contains the address of the beginning of the
        // buffer. The working pointer contains the address in the buffer
        // to which the next put or get operation will operate. The
        // working length contains the number of bytes that have been put
        // into the buffer. The max length is maxlength of the buffer,
        // it is the size allocated for the buffer

        public byte[] mBaseBytes;
        public int    mWorkingIndex;
        public int    mWorkingLength;
        public int    mMaxLength;

        //---------------------------------------------------------------------------
        // Copy direction. This specifies the direction of copy operations.
        // Copy to does a put, copy from does a get.

        public const int cCopyTo   = 0;
        public const int cCopyFrom = 1;
        public int mCopyDirection;

        //---------------------------------------------------------------------------
        // Copy direction. This specifies the direction of copy operations.
        // Copy to does a put, copy from does a get.

        public const int cNoError          = 0;
        public const int cBufferOverflow   = 1;
        public int mError;

        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        // Constructors.

        // Default constructor
        public ByteBuffer()
        {
            mBaseBytes     = null;
            mWorkingIndex  = 0;
            mWorkingLength = 0;
            mMaxLength     = 0;
            mCopyDirection = cCopyTo;
            mError         = cNoError;
        }

        // Constructor
        public ByteBuffer(int aSize)
        {
            mBaseBytes     = new byte[aSize];
            mWorkingIndex  = 0;
            mWorkingLength = 0;
            mMaxLength     = aSize;
            mCopyDirection = cCopyTo;
            mError         = cNoError;
        }

        // Constructor
        public ByteBuffer(byte[] aBytes)
        {
            mBaseBytes     = aBytes;
            mWorkingIndex  = 0;
            mWorkingLength = 0;
            mMaxLength     = aBytes.Length;
            mCopyDirection = cCopyTo;
            mError         = cNoError;
        }

        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        // Pointer operations.
        // reset sets the working pointer to the base address and
        // sets the length to zero.
        // rewind sets the working pointer to the base address
        // forward advances the working pointer and the length, if the
        // copy direction is for a put operation.
        // advance advances the working pointer and the length

        public void reset()
        {
            mWorkingIndex  = 0;
            mWorkingLength = 0;
        }

        public void rewind()
        {
            mWorkingIndex = 0;
        }

        public void forward (int aSize=1)
        {
            if (aSize + mWorkingIndex > mMaxLength) return;

            if (mCopyDirection == cCopyTo)
            {
                mWorkingIndex  += aSize;
                mWorkingLength += aSize;
            }
            else
            {
                mWorkingIndex  += aSize;
            }
        }

        public void advance (int aSize=1)
        {
            if (aSize + mWorkingIndex > mMaxLength) return;

            mWorkingIndex  += aSize;
            mWorkingLength += aSize;
        }

        public void fillZero (int aSize=1)
        {
            if (aSize + mWorkingIndex > mMaxLength) return;

            if (mCopyDirection == cCopyTo)
            {
                for (int i=0; i<aSize; i++)
                {
                    mBaseBytes[mWorkingIndex + i] = 0;
                }
                mWorkingIndex  += aSize;
                mWorkingLength += aSize;
            }
        }

        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        // Buffer position

        // Get the address of the start of the buffer
        public byte[] getBaseAddress()
        {
            return mBaseBytes;
        }

        public void setPosition (int aIndex)
        {
            // Set index
            mWorkingIndex = aIndex;

            // Guard
            if (mWorkingIndex > mMaxLength - 1)
            {
                mWorkingIndex = mMaxLength - 1;
            }
        }

        public int getPosition ()
        {
           return mWorkingIndex;
        }

        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        // Length and Copy direction

        public int getMaxLength()
        {
           return mMaxLength;
        }

        public void setLength(int aValue)
        {
           mWorkingLength=aValue;
        }

        public int getLength()
        {
           return mWorkingLength;
        }

        public int getError()
        {
           return mError;
        }

        public void setError(int aValue)
        {
           mError = aValue;
        }

        public void setCopyTo()
        {
           mCopyDirection = cCopyTo;
        }

        public void setCopyFrom ()
        {
           mCopyDirection = cCopyFrom;
        }

        public bool isCopyTo()
        {
           return mCopyDirection == cCopyTo;
        }

        public bool isCopyFrom ()
        {
           return mCopyDirection == cCopyFrom;
        }


    }
}
