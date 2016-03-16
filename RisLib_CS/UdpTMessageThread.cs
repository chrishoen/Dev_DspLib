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

    public abstract class UdpTMessageThread
    {
        //**********************************************************************
        // Inheriting classes override this method to process received messages

        public abstract void processRxMessage (ByteTMessage aMsg);

        //**********************************************************************
        // Members

        public Thread               mThread;
        public UdpRxTMessageSocket  mRxSocket;
        public UdpTxTMessageSocket  mTxSocket;
        public int                  mRxCount;

        //**********************************************************************
        // Constructor

        public UdpTMessageThread()
        {
        }

        public void configure(int aRxPort,int aTxPort,BaseTMessageCopier aMsgCopier)
        {
            // Rx socket
            mRxSocket = new UdpRxTMessageSocket();
            mRxSocket.configure(aRxPort,aMsgCopier);

            // Tx socket
            mTxSocket = new UdpTxTMessageSocket();
            mTxSocket.configure("127.0.0.1",aTxPort,aMsgCopier);
        }

        //**********************************************************************
        // Launch thread

        public void start()
        {
            // Create new thread object using thread run function
            mThread = new Thread(new ThreadStart(threadRun));
            // Start the thread
            mThread.Start();
        }

        //**********************************************************************
        // Shutdown thread

        public void stop()
        {
            if (mRxSocket != null)
            {
                mRxSocket.close();
            }
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Thread run function, receives messages

        public void threadRun()
        {
            while (true)
            {
                //--------------------------------------------------------------
                // Receive from the message socket

                ByteTMessage tMsg = mRxSocket.receiveMessage();

                //--------------------------------------------------------------
                // Call inheritor's override to process the message

                if (tMsg != null)
                {
                    processRxMessage(tMsg);
                }
                else
                {
                    return;
                }
            }
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Transmit message

        public void sendMessage(ByteTMessage aMsg)
        {
            mTxSocket.sendMessage(aMsg);
        }
    }
}
