using System;
using System.Collections.Generic;
using System.Text;
using System.Messaging;
using System.Diagnostics;
using System.Threading;
using Ris;

namespace Ris
{
    //**************************************************************************
    //**************************************************************************
    //**************************************************************************

    public class Prn
    {
        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Members

        public static bool mSuppressFlag = true;

        public enum PrnMode { Console, WinForm }
        public static PrnMode mPrnMode = PrnMode.Console;

        public static UdpTxStringSocket mTxSocket;

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Initialize

        public static void initializeForConsole()
        {
            mPrnMode = PrnMode.Console;
            PrintSettings.initialize();
            mSuppressFlag = false;
        }

        public static void initializeForWinForm()
        {
            mPrnMode = PrnMode.WinForm;
            PrintSettings.initialize();
            mTxSocket = new UdpTxStringSocket();
            mTxSocket.configure(PortDef.cPrintView);
            mSuppressFlag = false;
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Access

        public static void setFilter(int aFilter, bool aEnablePrint)
        {
            PrintSettings.setFilter(aFilter, aEnablePrint);
        }

        public static void Suppress()
        {
            mSuppressFlag = true;
        }

        public static void UnSuppress()
        {
            mSuppressFlag = false;
        }

        public static void ToggleSuppress()
        {
            mSuppressFlag = !mSuppressFlag;
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Print

        public static void print(int aFilter, string aFormat, params object[] aObjects)
        {
            // Test for print enabled
            if (mSuppressFlag == true && aFilter != 0) return;
            if (PrintSettings.mFilterTable[aFilter] == false) return;

            if (mPrnMode == PrnMode.Console)
            {
                // Print to console
                Console.WriteLine(aFormat, aObjects);
            }
            else
            {
                // Print to PrintView
                String tString = string.Format(aFormat, aObjects);
                mTxSocket.sendString(tString);
            }
        }

        ~Prn()
        {
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Filter constants

        public const int  FilterZero = 0;
        public const int  PrintInit1 = 1;
        public const int  PrintInit2 = 2;
        public const int  PrintInit3 = 3;
        public const int  PrintInit4 = 4;
        public const int  PrintRun1 = 5;
        public const int  PrintRun2 = 6;
        public const int  PrintRun3 = 7;
        public const int  PrintRun4 = 8;
        public const int  SocketInit1 = 9;
        public const int  SocketInit2 = 10;
        public const int  SocketInit3 = 11;
        public const int  SocketInit4 = 12;
        public const int  SocketRun1 = 13;
        public const int  SocketRun2 = 14;
        public const int  SocketRun3 = 15;
        public const int  SocketRun4 = 16;
        public const int  SerialInit1 = 17;
        public const int  SerialInit2 = 18;
        public const int  SerialInit3 = 19;
        public const int  SerialInit4 = 20;
        public const int  SerialRun1 = 21;
        public const int  SerialRun2 = 22;
        public const int  SerialRun3 = 23;
        public const int  SerialRun4 = 24;
        public const int  FileInit1 = 25;
        public const int  FileInit2 = 26;
        public const int  FileInit3 = 27;
        public const int  FileInit4 = 28;
        public const int  FileRun1 = 29;
        public const int  FileRun2 = 30;
        public const int  FileRun3 = 31;
        public const int  FileRun4 = 32;
        public const int  ThreadInit1 = 33;
        public const int  ThreadInit2 = 34;
        public const int  ThreadInit3 = 35;
        public const int  ThreadInit4 = 36;
        public const int  ThreadRun1 = 37;
        public const int  ThreadRun2 = 38;
        public const int  ThreadRun3 = 39;
        public const int  ThreadRun4 = 40;
        public const int  ProcInit1 = 41;
        public const int  ProcInit2 = 42;
        public const int  ProcInit3 = 43;
        public const int  ProcInit4 = 44;
        public const int  ProcRun1 = 45;
        public const int  ProcRun2 = 46;
        public const int  ProcRun3 = 47;
        public const int  ProcRun4 = 48;
        public const int  ExampleInit1 = 49;
        public const int  ExampleInit2 = 50;
        public const int  ExampleInit3 = 51;
        public const int  ExampleInit4 = 52;
        public const int  ExampleRun1 = 53;
        public const int  ExampleRun2 = 54;
        public const int  ExampleRun3 = 55;
        public const int  ExampleRun4 = 56;
        public const int  QCallInit1 = 57;
        public const int  QCallInit2 = 58;
        public const int  QCallInit3 = 59;
        public const int  QCallInit4 = 60;
        public const int  QCallRun1 = 61;
        public const int  QCallRun2 = 62;  
        public const int  QCallRun3 = 63;
        public const int  QCallRun4 = 64;
        public const int  CommInit1 = 65;
        public const int  CommInit2 = 66;
        public const int  CommInit3 = 67;
        public const int  CommInit4 = 68;
        public const int  CommRun1 = 69;
        public const int  CommRun2 = 70;
        public const int  CommRun3 = 71;
        public const int  CommRun4 = 72;
        public const int  ViewInit1 = 73;
        public const int  ViewInit2 = 74;
        public const int  ViewInit3 = 75;
        public const int  ViewInit4 = 76;
        public const int  ViewRun1 = 77;
        public const int  ViewRun2 = 78;
        public const int  ViewRun3 = 79;
        public const int  ViewRun4 = 80;
    };
}

