using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using Ris;

namespace Ris
{

    public class CmdLineConsole
    {
        public static void execute(BaseCmdLineExec aExec)
        {
            aExec.reset();

            bool tGoing = true;

            while (tGoing)
            {
                // Read command line
                CmdLineCmd tCmd = new CmdLineCmd();
                String tCParBuff = Console.ReadLine();
                tCmd.putCmdLineString(tCParBuff);

                // Toggle print
                if (tCmd.isCmd("P"))
                {
                    Prn.ToggleSuppress();
                }
                // Exit
                else if (tCmd.isCmd("EXIT") || tCmd.isCmd("E"))
                {
                    aExec.executeExit();
                    tGoing = false;
                }
                // Execute command
                else
                {
                    aExec.execute(tCmd);

                    if (tCmd.isBadCmd())
                    {
                        Console.WriteLine("INVALID COMMAND");
                        Console.WriteLine("-----------------------------------------");
                    }
                }
            }
        }
    }

}//namespace
