using System;
using System.Text;
using System.IO;

namespace Ris
{
    //******************************************************************************
    // This is an abstract base class for a message parser. It can be used
    // by code that receives messages into byte buffers such that the message
    // classes don't have to be visible to the receiving code. Inheriting classes
    // provide all of the details that are needed by receiving code to receive and
    // extract messages, as opposed to having the message classes being visible
    // to the receiving code.

    public abstract class BaseMessageParser
    {
        public BaseMessageParser()
        {
            mHeaderLength=0;
            mMessageLength=0;
            mMessageType=0;
            mPayloadLength=0;
            mHeaderValidFlag=false;
            mNetworkOrder=false;
        }

        // Return a constant header length
        public abstract int getHeaderLength();

        // Return a constant max buffer size
        public abstract int getMaxBufferSize();

        // Extract message header parameters from a buffer and validate them
        // Returns true if the header is valid
        public abstract bool extractMessageHeaderParms (ByteBuffer aBuffer);

        // Message header parameters, these are common to all message headers.
        // They are extracted from an actual received message header. In some
        // form, all message headers contain these parameters.

        public int  mHeaderLength;
        public int  mMessageLength;
        public int  mMessageType;
        public int  mPayloadLength;
        public bool mHeaderValidFlag;

        // Create a new message based on a message type. The created message
        // is initialized via its default constructor
        public abstract ByteContent createMessage(int aMessageType);

        // Extract a complete message from a byte buffer
        public ByteContent makeFromByteBuffer (ByteBuffer aBuffer)
        {
            // Guard
            if (mHeaderValidFlag == false)
            {
                return null;
            }

            ByteContent tMsg = null;

            // Set buffer direction for get
            aBuffer.setCopyFrom();

            // Call the inheritor's overload to create a new message
            // based on the message type
            tMsg = createMessage(mMessageType);

            // guard
            if (tMsg == null)
            {
                return null;
            }

            // Copy data from the buffer into the new message object
            aBuffer.getFromBuffer(tMsg);
            return tMsg;
        }

        // Preprocess a message before it is sent
        public abstract void processBeforeSend (ByteContent aMsg);

        // Endianess for buffers associated with the parser.
        // If true then the messages will be sent in network order,
        // big endian. If false, then little endian.
        void setNetworkOrder (bool aNetworkOrder)
        {
            mNetworkOrder = aNetworkOrder;
        }
        public bool mNetworkOrder;

        // Configures a byte buffer endianess
        public void configureByteBuffer (ByteBuffer aBuffer)
        {
        }
    };

    //******************************************************************************
    // This is an abstract base class for a message parser creator. It defines
    // a method that inheriting classes overload to create new message parsers.
    // It is used by transmitters and receivers to create new instances of message
    // parsers.

    public abstract class BaseMessageParserCreator
    {
       public abstract BaseMessageParser createNew();
    };

}
