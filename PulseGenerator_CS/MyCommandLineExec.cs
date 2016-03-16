using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using Ris;

namespace PulseDevelop
{

    class MyCmdLineExec : BaseCmdLineExec
    {
        public MyCmdLineExec()
        {
        }


        public override void execute(CmdLineCmd command)
        {
            if (command.isCmd("T11")) OnTest11(command);
            if (command.isCmd("T21")) OnTest21(command);
            if (command.isCmd("T31")) OnTest31(command);
            if (command.isCmd("T41")) OnTest41(command);
            if (command.isCmd("T42")) OnTest42(command);
        }

        public void OnTest11 (CmdLineCmd command)
        {
            PulseSignal ss = new PulseSignal();
            ss.Name = "Test11";
            ss.Fs = 10000.0;
            ss.Fp = 1000.0;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            PulseGenerate.Gen1(ss);
            ss.Normalize();
            PulseFile.WriteToTextFile(ss, ss.Ns);
            Console.WriteLine("Done");
        }

        public void OnTest21 (CmdLineCmd command)
        {
            PulseSignal ss = new PulseSignal();
            ss.Name = "Test21";
            ss.Fs = 44100.0;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            PulseGenerate.Gen2(ss);
            ss.Normalize();
            Console.WriteLine("Done");
        }

        public void OnTest31(CmdLineCmd command)
        {
            PulseSignal ss = new PulseSignal();
            ss.Name = "Test31";
            ss.Fs = 44100.0;
            ss.Fp = 400.0;
            ss.DCp = 0.1;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            PulseGenerate.Gen3(ss);
            ss.Normalize();
            PulseFile.WriteToTextFile(ss, ss.Ns);
            Console.WriteLine("Done");
        }

        public void OnTest41(CmdLineCmd command)
        {
            PulseSignal ss = new PulseSignal();
            ss.Name = "Test41";
            ss.Fs = 10000.0;
            ss.Fp = 1000.0;
            ss.Fm = 10.0;
            ss.DCm = 0.2;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            PulseGenerate.Gen41(ss);
            ss.Normalize();
            PulseFile.WriteToTextFile(ss, ss.Ns);
            Console.WriteLine("Done");
        }

        public void OnTest42(CmdLineCmd command)
        {
            PulseSignal ss = new PulseSignal();
            ss.Name = "Test42";
            ss.Fs = 44100.0;
            ss.Fp = 800.0;
            ss.Duration = 20.0 * 60;
            ss.MakeConsistent();
            ss.Show();
            PulseGenerate.Gen42(ss);
            ss.Normalize();
            PulseFile.WriteToTextFile(ss, ss.Nm * 2);
            Console.WriteLine("Done");
        }
    }
}


