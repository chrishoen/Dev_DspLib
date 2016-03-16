using System;
using System.Collections.Generic;
using System.Text;
using System.Globalization;


namespace Ris
{

    //**************************************************************************
    //**************************************************************************
    //**************************************************************************
    // Cmd line command

    public class CmdLineCmd
    {
        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Members

        public string mCmdLineString;

        // The command, the first token in the command line string
        public string mCmd;

        // Argument values as primitive data types
        public const int cMaxNumOfArgs = 20;
        public List<string> mSList = new List<string>(cMaxNumOfArgs + 1);

        public int  mArgNum;
        public bool mDefaultFlag;

        public bool mGoodCmd;

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Constructor

        public CmdLineCmd()
        {
            mCmdLineString = null;
            mCmd = null;
            mSList = new List<string>(cMaxNumOfArgs + 1);
            mArgNum = 0;
            mDefaultFlag = false;
            mGoodCmd = false;
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Put a command line string to be parsed

        public void putCmdLineString(string aString)
        {
            //******************************************************************
            //******************************************************************
            //******************************************************************
            // Store command line

            mCmdLineString = string.Copy(aString);

            //******************************************************************
            // Guard

            if (mCmdLineString.Length == 0)
            {
                mCmd = "NULL";
                return;
            }

            //******************************************************************
            // Parse command line into string list

            char[] tSeparators = new char[] { ' ', ',' };

            // Loop variables
            int tBeginIndex = 0;
            int tEndIndex = 0;

            bool tIsText = false;
            bool tIsLastChar = false;
            bool tIsSeparator = false;
            bool tIsQuote = false;
            bool tKeepQuote = false;

            int tSeparatorCount = 1;
            int tTextCount = 0;
            int tQuoteCount = 0;

            // Loop for each character in string
            for (int index = 0; index < mCmdLineString.Length; index++)
            {
                //-------------------------------------------------------------
                // Get this char and characterize it

                char tChar = mCmdLineString[index];

                // Initialize for this char
                tIsText = false;
                tIsSeparator = false;
                tIsQuote = false;

                // Test if char is separator
                for (int j = 0; j < tSeparators.Length; j++)
                {
                    if (tChar == tSeparators[j])
                    {
                        tIsSeparator = true;
                    }
                }
            
                // Test if char is quote
                tIsQuote = tChar.Equals('"');

                // Test if char text
                tIsText = !tIsSeparator && !tIsQuote;

                // Test if last char
                tIsLastChar = index == mCmdLineString.Length - 1;

                //-------------------------------------------------------------
                // Parse string into string list

                if (tIsSeparator)
                {
                    if (tQuoteCount == 0)
                    {
                        tSeparatorCount++;
                        if (tTextCount > 0)
                        {
                            mSList.Add(mCmdLineString.Substring(tBeginIndex, tEndIndex - tBeginIndex + 1));
                        }
                        tTextCount = 0;
                    }
                    else
                    {
                        tTextCount++;
                        if (tTextCount == 1 && !tKeepQuote)
                        {
                            tBeginIndex = index;
                        }
                        tEndIndex = index;
                    }

                }
                else if (tIsQuote)
                {
                    tQuoteCount++;
                    if (tQuoteCount == 1)
                    {
                        tTextCount = 0;
                        if (tKeepQuote)
                        {
                            tBeginIndex = index;
                        }
                    }
                    else if (tQuoteCount == 2)
                    {
                        tQuoteCount = 0;
                        if (tKeepQuote)
                        {
                            tEndIndex = index;
                            mSList.Add(mCmdLineString.Substring(tBeginIndex, tEndIndex - tBeginIndex + 1));
                            tTextCount = 0;
                        }
                        else
                        {
                            if (tTextCount > 0)
                            {
                                mSList.Add(mCmdLineString.Substring(tBeginIndex, tEndIndex - tBeginIndex + 1));
                            }
                            else
                            {
                                mSList.Add(String.Empty);
                            }
                            tTextCount = 0;
                        }
                    }
                }
                else if (tIsText)
                {
                    tTextCount++;
                    if (tTextCount == 1)
                    {
                        if (tQuoteCount != 1 || !tKeepQuote)
                        {
                            tBeginIndex = index;
                        }
                    }
                    tEndIndex = index;
                }

                if (tIsLastChar)
                {
                    if (tTextCount > 0)
                    {
                        mSList.Add(mCmdLineString.Substring(tBeginIndex, tEndIndex - tBeginIndex + 1));
                    }
                }
            }

            //---------------------------------------------------------------------------
            // Set variables

            if (mSList.Count == 0)
            {
                mCmd = "NULL";
                return;
            }

            mArgNum = mSList.Count - 1;
            mCmd = mSList[0];

            mDefaultFlag = mArgNum == 0;
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Return arguments from the command line.
        // These are given the argument index, such that argInt(1) returns the
        // first argument as an integer and argInt(2) returns the second argument.

        public int argInt(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return 0;
            }

            NumberFormatInfo tFormat = new NumberFormatInfo();
            NumberStyles tStyle = NumberStyles.Integer;
            if (!mSList[aArgIndex].StartsWith("0X",StringComparison.OrdinalIgnoreCase))
            {
                tStyle = NumberStyles.Integer;
            }
            else
            {
                mSList[aArgIndex] = mSList[aArgIndex].Remove(0, 2);
                tStyle = NumberStyles.HexNumber;
            }

            int tValue = 0;
            if (!Int32.TryParse(
               mSList[aArgIndex],
               tStyle,
               tFormat,
               out tValue))
            {
                tValue = 0;
            }

            return tValue;
        }

        public Int32 argInt32(int aArgIndex) { return argInt(aArgIndex);}

        //**********************************************************************

        public UInt32 argUInt32(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return 0;
            }

            NumberFormatInfo tFormat = new NumberFormatInfo();
            NumberStyles tStyle = NumberStyles.Integer;
            if (!mSList[aArgIndex].StartsWith("0X",StringComparison.OrdinalIgnoreCase))
            {
                tStyle = NumberStyles.Integer;
            }
            else
            {
                mSList[aArgIndex] = mSList[aArgIndex].Remove(0, 2);
                tStyle = NumberStyles.HexNumber;
            }

            uint tValue = 0;
            if (!UInt32.TryParse(
               mSList[aArgIndex],
               tStyle,
               tFormat,
               out tValue))
            {
                tValue = 0;
            }

            return tValue;
        }

        //**********************************************************************

        public SByte argSByte(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return 0;
            }

            NumberFormatInfo tFormat = new NumberFormatInfo();
            NumberStyles tStyle = NumberStyles.Integer;
            if (!mSList[aArgIndex].StartsWith("0X",StringComparison.OrdinalIgnoreCase))
            {
                tStyle = NumberStyles.Integer;
            }
            else
            {
                mSList[aArgIndex] = mSList[aArgIndex].Remove(0, 2);
                tStyle = NumberStyles.HexNumber;
            }

            SByte tValue = 0;
            if (!SByte.TryParse(
               mSList[aArgIndex],
               tStyle,
               tFormat,
               out tValue))
            {
                tValue = 0;
            }

            return tValue;
        }

        //**********************************************************************

        public Byte argByte(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return 0;
            }

            NumberFormatInfo tFormat = new NumberFormatInfo();
            NumberStyles tStyle = NumberStyles.Integer;
            if (!mSList[aArgIndex].StartsWith("0X",StringComparison.OrdinalIgnoreCase))
            {
                tStyle = NumberStyles.Integer;
            }
            else
            {
                mSList[aArgIndex] = mSList[aArgIndex].Remove(0, 2);
                tStyle = NumberStyles.HexNumber;
            }

            Byte tValue = 0;
            if (!Byte.TryParse(
               mSList[aArgIndex],
               tStyle,
               tFormat,
               out tValue))
            {
                tValue = 0;
            }

            return tValue;
        }

        //**********************************************************************

        public Int16 argInt16(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return 0;
            }

            NumberFormatInfo tFormat = new NumberFormatInfo();
            NumberStyles tStyle = NumberStyles.Integer;
            if (!mSList[aArgIndex].StartsWith("0X",StringComparison.OrdinalIgnoreCase))
            {
                tStyle = NumberStyles.Integer;
            }
            else
            {
                mSList[aArgIndex] = mSList[aArgIndex].Remove(0, 2);
                tStyle = NumberStyles.HexNumber;
            }

            Int16 tValue = 0;
            if (!Int16.TryParse(
               mSList[aArgIndex],
               tStyle,
               tFormat,
               out tValue))
            {
                tValue = 0;
            }

            return tValue;
        }

        //**********************************************************************

        public UInt16 argUInt16(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return 0;
            }

            NumberFormatInfo tFormat = new NumberFormatInfo();
            NumberStyles tStyle = NumberStyles.Integer;
            if (!mSList[aArgIndex].StartsWith("0X",StringComparison.OrdinalIgnoreCase))
            {
                tStyle = NumberStyles.Integer;
            }
            else
            {
                mSList[aArgIndex] = mSList[aArgIndex].Remove(0, 2);
                tStyle = NumberStyles.HexNumber;
            }

            UInt16 tValue = 0;
            if (!UInt16.TryParse(
               mSList[aArgIndex],
               tStyle,
               tFormat,
               out tValue))
            {
                tValue = 0;
            }

            return tValue;
        }

        //**********************************************************************

        public Int64 argInt64(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return 0;
            }

            NumberFormatInfo tFormat = new NumberFormatInfo();
            NumberStyles tStyle = NumberStyles.Integer;
            if (!mSList[aArgIndex].StartsWith("0X",StringComparison.OrdinalIgnoreCase))
            {
                tStyle = NumberStyles.Integer;
            }
            else
            {
                mSList[aArgIndex] = mSList[aArgIndex].Remove(0, 2);
                tStyle = NumberStyles.HexNumber;
            }

            Int64 tValue = 0;
            if (!Int64.TryParse(
               mSList[aArgIndex],
               tStyle,
               tFormat,
               out tValue))
            {
                tValue = 0;
            }

            return tValue;
        }

        //**********************************************************************

        public UInt64 argUInt64(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return 0;
            }

            NumberFormatInfo tFormat = new NumberFormatInfo();
            NumberStyles tStyle = NumberStyles.Integer;
            if (!mSList[aArgIndex].StartsWith("0X",StringComparison.OrdinalIgnoreCase))
            {
                tStyle = NumberStyles.Integer;
            }
            else
            {
                mSList[aArgIndex] = mSList[aArgIndex].Remove(0, 2);
                tStyle = NumberStyles.HexNumber;
            }

            UInt64 tValue = 0;
            if (!UInt64.TryParse(
               mSList[aArgIndex],
               tStyle,
               tFormat,
               out tValue))
            {
                tValue = 0;
            }

            return tValue;
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        //**********************************************************************

        public bool argBool(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return false;
            }

            string tValue = mSList[aArgIndex].ToUpper();
            return tValue.Equals("TRUE",StringComparison.OrdinalIgnoreCase);
        }

        //**********************************************************************

        public double argDouble(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return 0;
            }

            double value = 0;
            if (!Double.TryParse(mSList[aArgIndex], out value))
            {
                value = 0.0;
            }

            return value;
        }

        //**********************************************************************

        public float argFloat(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return 0;
            }

            float tValue = 0;
            if (!Single.TryParse(mSList[aArgIndex], out tValue))
            {
                tValue = 0.0f;
            }

            return tValue;
        }

        //**********************************************************************

        public String argString(int aArgIndex)
        {
            if (aArgIndex > mArgNum)
            {
                return String.Empty;
            }

            return mSList[aArgIndex];
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Set defaults for arguments from the command line.
        // Used if no arguments are entered.

        public void setArgDefault(int aArgIndex, int value)
        {
            if (!mDefaultFlag) return;

            if (aArgIndex < mSList.Count)
            {
                mSList[aArgIndex] = value.ToString();
            }
            else
            {
                mSList.Add(value.ToString());
            }

            if (aArgIndex > mArgNum)
            {
                mArgNum = aArgIndex;
            }
        }

        //**********************************************************************

        public void setArgDefault(int aArgIndex, double value)
        {
            if (!mDefaultFlag) return;

            if (aArgIndex < mSList.Count)
            {
                mSList[aArgIndex] = value.ToString();
            }
            else
            {
                mSList.Add(value.ToString());
            }

            if (aArgIndex > mArgNum)
            {
                mArgNum = aArgIndex;
            }
        }

        //**********************************************************************

        public void setArgDefault(int aArgIndex, string value)
        {
            if (!mDefaultFlag) return;

            if (aArgIndex < mSList.Count)
            {
                mSList[aArgIndex] = value;
            }
            else
            {
                mSList.Add(value);
            }

            if (aArgIndex > mArgNum)
            {
                mArgNum = aArgIndex;
            }
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Cmd extraction

        public int NumArg
        {
            get { return mArgNum; }
        }

        // Returns true if aString is equal to the command
        public bool isCmd(string aCmd)
        {
            if (mCmd==null) return false;
            if (mCmd.Equals(aCmd,StringComparison.OrdinalIgnoreCase))
            {
                mGoodCmd = true;
                return true;
            }
            else
            {
                return false;
            }
        }

        //**********************************************************************
        //**********************************************************************
        //**********************************************************************
        // Returns true is no calls to isCmd returned true

        public bool isBadCmd()
        {
            // Return true if no call to isCmd returned true
            return (!mGoodCmd);
        }

        // Tests argument aArgIndex against a string
        public bool isArgString(int aArgIndex, string aValue)
        {
            if (aArgIndex >= mArgNum) return false;
            return mSList[aArgIndex].Equals(aValue,StringComparison.OrdinalIgnoreCase);
        }

        //***************************************************************************
        //***************************************************************************
        //***************************************************************************
        // Nested anchor, used for processing nested records. This is piggybacked 
        // onto a command by a command line processor so that it can be used by a 
        // command line executive.

        public CmdLineExecNestedAnchor mNestedAnchor;
    }

}//namespace
