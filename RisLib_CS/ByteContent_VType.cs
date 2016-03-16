using System;
using System.Text;
using System.IO;

namespace Ris
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

    public partial class ByteBuffer
    {
        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        // Copy value types

        //---------------------------------------------------------------------------
        // copy does either a copy to the buffer or a copy from the buffer
        //
        // These either put an item to the byte buffer or get an
        // item from the byte buffer, based on the value of the
        // buffer copy direction flag.

        //******************************************************************************
        //******************************************************************************
        //******************************************************************************

        // Copy unsigned byte
        public void copy (ref byte aValue)
        {
            // Number of bytes to copy
            int tSize = 1;

            // Copy to the buffer
            if (isCopyTo())
            {
                // Guard
                if (tSize + mWorkingIndex > mMaxLength)
                {
                    setError(cBufferOverflow);
                    return;
                }

                // Copy value to the buffer
                mBaseBytes[mWorkingIndex] = aValue;
 
                // Adjust buffer members
                mWorkingIndex  += tSize;
                mWorkingLength += tSize;
            }
            // Copy from the buffer
            else
            {
                // Guard
                if (tSize + mWorkingIndex > mWorkingLength)
                {
                    setError(cBufferOverflow);
                    return;
                }

                // Copy value from the buffer
                aValue = mBaseBytes[mWorkingIndex];

                // Adjust buffer members
                mWorkingIndex  += tSize;
            }
        }

        // Copy signed byte
        public void copy (ref sbyte aValue)
        {
            // Copy to the buffer
            if (isCopyTo())
            {
                // Convert signed to unsigned
                byte tByte = unchecked((byte)aValue);
                // Copy unsigned to the buffer
                copy( ref tByte);
            }
            // Copy from the buffer
            else
            {
                // Unsigned temp
                byte tByte = 0;
                // Copy unsigned from the buffer
                copy( ref tByte);
                // Convert unsigned to signed
                aValue = unchecked((sbyte)tByte);
            }
        }

        // Copy bool
        public void copy (ref bool aValue)
        {
            // Copy to the buffer
            if (isCopyTo())
            {
                // Convert bool to byte
                byte tByte = aValue ? (byte)1 : (byte)0;
                // Copy byte to the buffer
                copy( ref tByte);
            }
            // Copy from the buffer
            else
            {
                // Unsigned temp
                byte tByte = 0;
                // Copy byte from the buffer
                copy( ref tByte);
                // Convert byte to bool
                aValue = tByte != 0;
            }
        }

        //******************************************************************************
        //******************************************************************************
        //******************************************************************************

        public void copy<MyType> (int aSize,ref MyType aValue,Func<MyType, byte[]> aToBytes,Func<byte[],int,MyType> aFromBytes)
        {
            // Copy to the buffer
            if (isCopyTo())
            {
                // Guard
                if (aSize + mWorkingIndex > mMaxLength)
                {
                    setError(cBufferOverflow);
                    return;
                }

                // Copy value to the buffer
                byte[] tValueBytes = aToBytes(aValue);
                for (int i = 0; i < aSize; i++)
                {
                    mBaseBytes[mWorkingIndex + i] = tValueBytes[i];
                }
                 
                // Adjust buffer members
                mWorkingIndex  += aSize;
                mWorkingLength += aSize;
            }
            // Copy from the buffer
            else
            {
                // Guard
                if (aSize + mWorkingIndex > mWorkingLength)
                {
                    setError(cBufferOverflow);
                    return;
                }

                // Copy value from the buffer
                aValue = aFromBytes( mBaseBytes, mWorkingIndex );

                // Adjust buffer members
                mWorkingIndex  += aSize;
            }
        }

        //******************************************************************************
        //******************************************************************************
        //******************************************************************************

        public void copy (ref short aValue)
        {
            copy<short>  (2,ref aValue,BitConverter.GetBytes,BitConverter.ToInt16);
        }

        public void copy (ref int   aValue)
        {
            copy<int>    (4,ref aValue,BitConverter.GetBytes,BitConverter.ToInt32);
        }

        public void copy (ref long  aValue)
        {
            copy<long>   (8,ref aValue,BitConverter.GetBytes,BitConverter.ToInt64);
        }

        public void copy (ref ushort aValue)
        {
            copy<ushort> (2,ref aValue,BitConverter.GetBytes,BitConverter.ToUInt16);
        }

        public void copy (ref uint   aValue)
        {
            copy<uint>   (4,ref aValue,BitConverter.GetBytes,BitConverter.ToUInt32);
        }

        public void copy (ref ulong  aValue)
        {
            copy<ulong>  (8,ref aValue,BitConverter.GetBytes,BitConverter.ToUInt64);
        }

        public void copy (ref float  aValue)
        {
            copy<float>  (4,ref aValue,BitConverter.GetBytes,BitConverter.ToSingle);
        }

        public void copy (ref double  aValue)
        {
            copy<double> (8,ref aValue,BitConverter.GetBytes,BitConverter.ToDouble);
        }
    }
}
