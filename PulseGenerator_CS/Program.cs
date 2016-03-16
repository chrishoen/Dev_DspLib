using System;
using System.Collections.Generic;
using System.Text;

using Ris;

namespace PulseDevelop
{
    class Program
    {
        static void Main(string[] args)
        {
            Prn.initializeForConsole();
            MyCmdLineExec tCmdLineExec = new MyCmdLineExec();
            CmdLineConsole.execute(tCmdLineExec);
        }
    }
}
