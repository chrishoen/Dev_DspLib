using System;
using System.Text;
using System.IO;

namespace Ris
{

    public partial class ByteBuffer
    {
        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        // Copy reference types

        //---------------------------------------------------------------------------
        // copy does either a copy to the buffer or a copy from the buffer
        //
        // These either put an item to the byte buffer or get an
        // item from the byte buffer, based on the value of the
        // buffer copy direction flag.

        //******************************************************************************
        //******************************************************************************
        //******************************************************************************

        public void copy (ByteContent aContent)
        {
            aContent.copyToFrom(this);
        }

        public void putToBuffer (ByteContent aContent)
        {
            // Set copy direction
            setCopyTo();

            // Call ByteContent supplied member function to do the put
            aContent.copyToFrom(this);
        }

        public void getFromBuffer (ByteContent aContent)
        {
            // Set copy direction
            setCopyFrom();

            // Call ByteContent supplied member function to do the get
            aContent.copyToFrom(this);
        }

        //******************************************************************************
        //******************************************************************************
        //******************************************************************************
        // This copy strings to/from a buffer. For a copy to, it copies the length of
        // the string into a two byte ushort and then it copies the string bytes to the
        // buffer. For a copy from, it copies the length of the string from the buffer
        // into a ushort and then it copies the buffer bytes into the string.

        public void copyS (ref String aString)
        {
            // Copy to the buffer
            if (isCopyTo())
            {
                // Number of bytes to copy
                int tSize  = aString.Length;

                // Guard
                if (2 + tSize + mWorkingIndex > mMaxLength)
                {
                    setError(cBufferOverflow);
                    return;
                }

                // Copy string length to the buffer
                // This advances the buffer by two bytes
                ushort tUSize = (ushort)tSize;
                copy (ref tUSize);

                // Copy string to the buffer
                byte[] tBytes = Encoding.ASCII.GetBytes(aString);

                for (int i = 0; i < tSize; i++)
                {
                    mBaseBytes[mWorkingIndex + i] = tBytes[i];
                }

                // Adjust buffer members
                mWorkingIndex  += tSize;
                mWorkingLength += tSize;
            }
            // Copy from the buffer
            else
            {
                // Guard
                if (2 + mWorkingIndex > mMaxLength)
                {
                    aString = String.Empty;
                    setError(cBufferOverflow);
                    return;
                }

                // Copy string length from the buffer
                // This advances the buffer by two bytes
                ushort tUSize = 0;
                copy (ref tUSize);
                int tSize = (int)tUSize;

                // Guard
                if (tSize + mWorkingIndex > mMaxLength || tSize==0)
                {
                    aString = String.Empty;
                    setError(cBufferOverflow);
                    return;
                }

                // Get string from buffer
                aString = ASCIIEncoding.ASCII.GetString(mBaseBytes,mWorkingIndex,tSize); 

                // Adjust buffer members
                mWorkingIndex  += tSize;
            }
        }

    }
}
