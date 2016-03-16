using System;
using System.Text;
using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace Ris
{
    //**************************************************************************
    //**************************************************************************
    //**************************************************************************

    public class UdpRxMsgSocket
    {
        //**********************************************************************
        // Members

        public UdpClient         mUdpClient;
        public IPEndPoint        mIPEndPoint;
        public BaseMessageParser mMessageParser;
        public int               mRxCount;
        public bool              mValidFlag;

        //**********************************************************************
        // Constructor

        public UdpRxMsgSocket()
        {
        }

        public void configure(int aPort,BaseMessageParser aMessageParser)
        {
            mUdpClient  = new UdpClient(aPort);
            mIPEndPoint = new IPEndPoint(IPAddress.Any, aPort);
            mMessageParser = aMessageParser;
            
            Prn.print(Prn.SocketInit2,"UdpRxMsgSocket     $ {0,16} : {1}",mIPEndPoint.Address.ToString(),mIPEndPoint.Port);
        }

        public void close()
        {
            if (mUdpClient != null)
            {
                mUdpClient.Close();
                mUdpClient = null;
            }
        }

        //**********************************************************************
        // Rceive record message via socket

        public ByteContent receiveMsg()
        {
            //--------------------------------------------------------------
            // Guard

            if (mUdpClient == null) return null;

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
            // Create byte buffer

            ByteBuffer tBuffer = new ByteBuffer(tRxBytes);
            tBuffer.setCopyFrom();
            tBuffer.setLength(tRxBytes.Length);

            //--------------------------------------------------------------
            // Copy from the receive buffer into the message parser object
            // and validate the header


            mMessageParser.extractMessageHeaderParms(tBuffer);

            // If the header is not valid then error
            if (!mMessageParser.mHeaderValidFlag)
            {
                Prn.print(Prn.SocketRun1, "UdpRxSocket Receive FAIL INVALID HEADER");
                return null;
            }

            Prn.print(Prn.SocketRun2, "UdpRxSocket Receive Header {0} {1}",
                mMessageParser.mMessageLength,
                mMessageParser.
                mMessageType);

            //--------------------------------------------------------------
            // At this point the buffer contains the complete message.
            // Extract the message from the byte buffer into a new message
            // object and return it.

            tBuffer.rewind();
            ByteContent tRxMsg = mMessageParser.makeFromByteBuffer(tBuffer);

            if (tRxMsg == null)
            {
                Prn.print(Prn.SocketRun1, "UdpRxSocket Receive FAIL ZERO2");
                return null;
            }

            // Returning true  means socket was not closed
            // Returning false means socket was closed
            mRxCount++;
            return tRxMsg;
        }
    }
    //**************************************************************************
    //**************************************************************************
    //**************************************************************************

    public class UdpTxMsgSocket
    {
        //**********************************************************************
        // Members

        public Socket            mSocket;
        public IPEndPoint        mIPEndPoint;
        public BaseMessageParser mMessageParser;
        public int               mTxMsgCount;
        public bool              mValidFlag;

        //**********************************************************************
        // Constructor

        public UdpTxMsgSocket()
        {
        }

        public void configure(String aAddress,int aPort,BaseMessageParser aMessageParser)
        {
            // Socket 
            mSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram,ProtocolType.Udp);
            mIPEndPoint = new IPEndPoint(IPAddress.Parse(aAddress), aPort);

            Prn.print(Prn.SocketInit2,"UdpTxMsgSocket     $ {0,16} : {1}",mIPEndPoint.Address.ToString(),mIPEndPoint.Port);

            // Message parser
            mMessageParser = aMessageParser;
        }

        //**********************************************************************
        // Send message via socket

        public void sendMsg (ByteContent aTxMsg)
        {
            // Process message before send
            mMessageParser.processBeforeSend(aTxMsg);

            // Create byte buffer
            ByteBuffer tBuffer = new ByteBuffer(mMessageParser.getMaxBufferSize());

            // Copy message to buffer
            tBuffer.putToBuffer(aTxMsg);
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
        }
    }
}
