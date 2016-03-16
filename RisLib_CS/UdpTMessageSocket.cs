using System;
using System.Text;
using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace Ris
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Definitions

   class TMessageSocketDefT
   {
      //************************************************************************
      // Use this for a buffer size for these sockets

      public const int cBufferSize = 20000;

   };

    //**************************************************************************
    //**************************************************************************
    //**************************************************************************
    // This encapsualtes the message header.

    public class TMessageMsgHeader : ByteContent
    {
        public TMessageMsgHeader()
        {
            mSyncWord1         = 0x11111111;
            mSyncWord2         = 0x22222222;
            mMessageIdentifier = 0;
            mMessageLength     = 0;
            mSourceId          = 0;
            mDestinationId     = 0;

            mInitialPosition   = 0;
            mInitialLength     = 0;
        }

        //------------------------------------------------
        // Header Content

        public int   mSyncWord1;
        public int   mSyncWord2;
        public int   mMessageIdentifier;
        public int   mMessageLength;
        public int   mSourceId;
        public int   mDestinationId;

        // Header Content
        //------------------------------------------------

        // Header length
        public const int cLength = 24;

        // Valid
        public bool mHeaderValidFlag;

        //----------------------------------------------------------------------
        // Validate a received header

        public bool validate()
        {
            // Test for error
            bool tError =
                mSyncWord1 != 0x11111111 ||
                mSyncWord2 != 0x22222222 ||
                mMessageLength < cLength  ||
                mMessageLength > TMessageSocketDefT.cBufferSize;

            // If no error then valid
            mHeaderValidFlag = !tError;

            // Return valid flag
            return mHeaderValidFlag;
        }

        //----------------------------------------------------------------------
        // If the byte buffer is configured for put operations then this puts
        // the contents of the object into the byte buffer (it does a copy to,
        // it copies the object to the byte buffer).
        // If the byte buffer is configured for get operations then this gets
        // the contents of the object from the byte buffer (it does a copy
        // from, it copies the object from the byte buffer).
        // Copy To and Copy From are symmetrical.
        //----------------------------------------------------------------------

        public override void copyToFrom (ByteBuffer aBuffer)
        {
            aBuffer.copy( ref mSyncWord1         );
            aBuffer.copy( ref mSyncWord2         );
            aBuffer.copy( ref mMessageIdentifier );
            aBuffer.copy( ref mMessageLength     );
            aBuffer.copy( ref mSourceId          );
            aBuffer.copy( ref mDestinationId     );
        }

        //----------------------------------------------------------------------
        // For variable content messages, the message length cannot be known
        // until the entire message has been written to a byte buffer.
        // Therefore, the message header cannot be written to a byte buffer
        // until the entire message has been written and the length is known.
        // The procedure to write a message to a byte buffer is to skip over the 
        // buffer segment where the header is located, write the message payload
        // to the buffer, set the header message length based on the now known
        // payload length, and write the header to the buffer.
        //
        // These are called explicitly by inheriting messages at the
        // beginning and end of their copyToFrom's to manage the headers.
        // For "get" operations, headerCopyToFrom "gets" the header and
        // headerReCopyToFrom does nothing. For "put" operations,
        // headerCopyToFrom stores the buffer pointer and advances past where
        // the header will be written and headerReCopyToFrom "puts" the header
        // at the stored position. Both functions are passed a byte buffer
        // pointer to where the copy is to take place. Both are also passed a 
        // MessageContent pointer to where they can get and mMessageType
        // which they transfer into and out of the headers.
        //----------------------------------------------------------------------

        public void headerCopyToFrom (ByteBuffer aBuffer,ByteTMessage aParent)
        {
            //------------------------------------------------------------------
            // Instances of this class are members of parent message classes.
            // A call to this function should be the first line of code in a
            // containing parent message class's copyToFrom. It performs 
            // pre -copyToFrom operations. It's purpose is to copy headers 
            // to /from byte buffers. The corresponding function
            // headerReCopyToFrom should be called as the last line of code in 
            // the containing message class' copyToFrom. Lines of code in 
            // between should copy individual data elements into/out of the
            // buffer.
            //------------------------------------------------------------------
            // for a "copy to" put
            //
            // If this is a "copy to" put operation then the header copy will
            // actually be done by the headerReCopyToFrom, after the rest of the
            // message has been copied into the buffer. This is because some of 
            // the fields in the header cannot be set until after the rest of
            // the message has been put into the buffer. (You don't know the 
            // length of the message until you put all of the data into it, you 
            // also can't compute a checksum). This call stores the original
            // buffer position that is passed to it when it is called for later 
            // use by the headerReCopyToFrom. The original buffer position
            // points to where the header should be copied. This call then 
            // forward advances the buffer to point past the header. Forward 
            // advancing the buffer position to point just after where the
            // header should be is the same as doing a pretend copy of the 
            // header. After this pretend copy of the header, the buffer 
            // position points to where the data should be put into the buffer.
            // Store the original buffer position for later use by the
            // headerReCopyToFrom and advance the buffer position forward
            // to point past the header.

            if (aBuffer.isCopyTo())
            {
                // Store the buffer parameters for later use by the
                // headerReCopyToFrom
                mInitialPosition = aBuffer.getPosition();
                mInitialLength   = aBuffer.getLength();

                // Advance the buffer position to point past the header.
                aBuffer.forward(cLength);
            }

            //------------------------------------------------------------------
            // for a "copy from" get
            //
            // If this is a "copy from" get operation then copy the header from
            // the buffer into the header member. Also set the message content
            // type from the variable datum id

            else
            {
                // Copy the buffer content into the header object.
                copyToFrom(aBuffer);
                // Set the message content type.
                aParent.mType = mMessageIdentifier;
            }
        }

        public void headerReCopyToFrom  (ByteBuffer aBuffer,ByteTMessage aParent)
        {
            // If this is a put operation then this actually copies the header
            // into the buffer. This sets some header length parameters and 
            // copies the header into the buffer position that was stored when
            // headerCopyToFrom was called.

            if (aBuffer.isCopyTo())
            {
                // Store the buffer parameters for later use by the
                // headerReCopyToFrom
                int tFinalPosition = aBuffer.getPosition();
                int tFinalLength   = aBuffer.getLength();

                // Get message parameters from parent
                mMessageIdentifier = aParent.mType;
                mMessageLength     = aBuffer.getLength();

                // Restore buffer parameters
                // to the initial position
                aBuffer.setPosition (mInitialPosition);
                aBuffer.setLength   (mInitialPosition);

                // Copy the adjusted header into the buffer'
                // at the original position
                copyToFrom( aBuffer );

                // Restore buffer parameters
                // to the final position
                aBuffer.setPosition (tFinalPosition);
                aBuffer.setLength   (tFinalPosition);
            }
            else
            {
            }
        }

        //----------------------------------------------------------------------
        // These are set by headerCopyToFrom and used by headerReCopyToFrom,
        // for "put" operations.Theyt contain the buffer position and length of
        // where the headerReCopyToFrom will take place, which should be
        // where headerCopyToFrom was told to do the copy.

        public int mInitialPosition;
        public int mInitialLength;

        public void reset()
        {
            mSyncWord1         = 0;
            mSyncWord2         = 0;
            mMessageIdentifier = 0;
            mMessageLength     = 0;
            mSourceId          = 0;
            mDestinationId     = 0;

            mInitialPosition   = 0;
            mInitialLength     = 0;
        }

    };

    //**************************************************************************
    //**************************************************************************
    //**************************************************************************

    public class UdpRxTMessageSocket
    {
        //**********************************************************************
        // Members

        public UdpClient           mUdpClient;
        public IPEndPoint          mIPEndPoint;
        public BaseTMessageCopier  mMsgCopier;
        public int                 mRxCount;
        public bool                mValidFlag;

        //**********************************************************************
        // Constructor

        public UdpRxTMessageSocket()
        {
        }

        public void configure(int aPort,BaseTMessageCopier aMsgCopier)
        {
            mUdpClient  = new UdpClient(aPort);
            mIPEndPoint = new IPEndPoint(IPAddress.Any, aPort);
            mMsgCopier  = aMsgCopier;

            Prn.print(Prn.SocketInit2,"UdpRxMsgSocket     $ {0,16} : {1}",mIPEndPoint.Address.ToString(),mIPEndPoint.Port);
        }

        public void close()
        {
            if (mUdpClient != null)
            {
                mUdpClient.Close();
            }
        }

        //**********************************************************************
        // Rceive record message via socket

        public ByteTMessage receiveMessage ()
        {
            //--------------------------------------------------------------
            // Receive bytes from socket

            byte[] tRxBytes = null;

            try
            {
                tRxBytes = mUdpClient.Receive(ref mIPEndPoint);
            }
            catch
            {
                Prn.print(Prn.SocketRun1, "UdpRxSocket Receive EXCEPTION");
                return null;
            }
            //--------------------------------------------------------------
            // Guard

            if (tRxBytes != null)
            {
                Prn.print(Prn.SocketRun2, "UdpRxSocket Receive {0}",tRxBytes.Length);
            }
            else
            {
                Prn.print(Prn.SocketRun1, "UdpRxSocket Receive FAIL ZERO1");
                return null;
            }

            //--------------------------------------------------------------
            // Copy from the receive buffer into an instance of the header
            // and validate the header

            // Create byte buffer
            ByteBuffer tBuffer = new ByteBuffer(tRxBytes);
            tBuffer.setCopyFrom();
            tBuffer.setLength(tRxBytes.Length);

            TMessageMsgHeader tHeader = new TMessageMsgHeader();

            tBuffer.setCopyFrom();
            tBuffer.getFromBuffer(tHeader);

            // If the header is not valid then error
      
            if (!tHeader.validate())
            {
                Prn.print(Prn.SocketRun1, "UdpRxSocket Receive FAIL INVALID HEADER");
                return null;
            }

            Prn.print(Prn.SocketRun2, "UdpRxSocket Receive Header {0} {1}",
                tHeader.mMessageLength,
                tHeader.mMessageIdentifier);

            //--------------------------------------------------------------
            // At this point the buffer contains the complete message.
            // Extract the message from the byte buffer into a new message
            // object and return it.

            // Create a record based on the record type
            ByteTMessage tMsg = mMsgCopier.createMessage(tHeader.mMessageIdentifier);

            // Copy from the buffer into the record
            mMsgCopier.copyToFrom(tBuffer, tMsg);

            // Returning true  means socket was not closed
            // Returning false means socket was closed
            mRxCount++;
            return tMsg;
        }
    }
    //**************************************************************************
    //**************************************************************************
    //**************************************************************************

    public class UdpTxTMessageSocket
    {
        //**********************************************************************
        // Members

        public Socket              mSocket;
        public IPEndPoint          mIPEndPoint;
        public BaseTMessageCopier  mMsgCopier;
        public int                 mTxCount;
        public bool                mValidFlag;

        //**********************************************************************
        // Constructor

        public UdpTxTMessageSocket()
        {
        }

        public void configure(String aAddress,int aPort,BaseTMessageCopier aMsgCopier)
        {
            // Socket 
            mSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram,ProtocolType.Udp);
            mIPEndPoint = new IPEndPoint(IPAddress.Parse(aAddress), aPort);
            // Copier
            mMsgCopier = aMsgCopier;
        }

        //**********************************************************************
        // Send message via socket

        public void sendMessage (ByteTMessage aMsg)
        {
            // Create byte buffer
            ByteBuffer tBuffer = new ByteBuffer(TMessageSocketDefT.cBufferSize);

            //------------------------------------------------------------------
            // Instance of a header,set members

            TMessageMsgHeader tHeader = new TMessageMsgHeader();
            tHeader.mMessageIdentifier = aMsg.mType;

            //------------------------------------------------------------------
            // Copy

            // Copy header to buffer
            tBuffer.setCopyTo();
            tHeader.headerCopyToFrom(tBuffer,aMsg);

            // Copy record to buffer
            mMsgCopier.copyToFrom(tBuffer,aMsg);
      
            // ReCopy header to buffer
            tHeader.headerReCopyToFrom(tBuffer,aMsg);

            //------------------------------------------------------------------------
            // Send buffer to socket

            byte[] tTxBytes = tBuffer.getBaseAddress();
            int    tTxLength = tBuffer.getPosition();

            try
            {
                int tSent = mSocket.SendTo(tTxBytes, tTxLength, SocketFlags.None, mIPEndPoint);
                Prn.print(Prn.SocketRun2, "UdpTxSocket Send {0}",tSent);
            }
            catch
            {
                Prn.print(Prn.SocketRun2, "UdpTxSocket Send EXCEPTION");
            }
            mTxCount++;
        }
    }
}
