using System;
using System.Collections.Generic;
using System.Text;

namespace Ris
{
    //**************************************************************************
    //**************************************************************************
    //**************************************************************************

    public class PrintSettings
    {
        // Members
        public const int cFilterTableSize = 200;
        public static bool[] mFilterTable = new bool[cFilterTableSize];

        // Initialize
        public static void initialize()
        {
            // All disabled, except zero
            for (int i = 0; i < cFilterTableSize; i++)
            {
                mFilterTable[i] = false;
            }
            mFilterTable[0] = true;
        }

        // setFilter
        public static void setFilter(int aFilter, bool aEnablePrint)
        {
            mFilterTable[aFilter] = aEnablePrint;
        }
    }

}

