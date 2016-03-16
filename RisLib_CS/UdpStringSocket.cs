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

    public class UdpRxStringSocket
    {
        //**********************************************************************
        // Members

        public UdpClient         mUdpClient;
        public IPEndPoint        mIPEndPoint;
        public BaseMessageParser mMessageParser;
        public int               mRxMsgCount;

        //**********************************************************************
        // Constructor

        public UdpRxStringSocket()
        {
        }

        public void configure(int aPort)
        {
            mUdpClient  = new UdpClient(aPort);
            mIPEndPoint = new IPEndPoint(IPAddress.Any, aPort);
        }

        //**********************************************************************
        // Receive string via socket

        public String receiveString()
        {
            byte[] tRxBytes = null;

            try
            {
                tRxBytes = mUdpClient.Receive(ref mIPEndPoint);
            }
            catch
            {
                Console.WriteLine("mUdpClient.Receive EXCEPTION1");
                return null;
            }

            //--------------------------------------------------------------
            // Guard

            if (tRxBytes == null)
            {
                Console.WriteLine("mUdpClient.Receive EXCEPTION2");
                return null;
            }

            //--------------------------------------------------------------
            // Get string from bytes

            String tString = Encoding.ASCII.GetString(tRxBytes, 0, tRxBytes.Length);

            return tString;
        }
    }

    //**************************************************************************
    //**************************************************************************
    //**************************************************************************

    public class UdpTxStringSocket
    {
        //**********************************************************************
        // Members

        public Socket            mSocket;
        public IPEndPoint        mIPEndPoint;
        public int               mTxMsgCount;
        public bool              mValidFlag;

        //**********************************************************************
        // Constructor

        public UdpTxStringSocket()
        {
        }

        public void configure(String aAddress,int aPort)
        {
            // Socket 
            mSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram,ProtocolType.Udp);
            mIPEndPoint = new IPEndPoint(IPAddress.Parse(aAddress), aPort);
        }

        public void configure(int aPort)
        {
            // Socket 
            mSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram,ProtocolType.Udp);
            mIPEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), aPort);
        }

        //**********************************************************************
        // Send string via socket

        public void sendString (String aString)
        {
            // Get bytes from string
            byte[] tTxBytes  = Encoding.ASCII.GetBytes(aString);
            int    tTxLength = tTxBytes.Length;

            try
            {
                int tSent = mSocket.SendTo(tTxBytes, tTxLength, SocketFlags.None, mIPEndPoint);
            }
            catch (Exception send_exception )
            {
                Console.WriteLine("Socket Tx Exception {0}", send_exception.Message);
            }
        }
    }
}
