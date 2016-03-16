using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using Ris;

namespace SoundDevelop
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
            if (command.isCmd("T22")) OnTest22(command);
            if (command.isCmd("T23")) OnTest23(command);
            if (command.isCmd("T24")) OnTest24(command);
            if (command.isCmd("T31")) OnTest31(command);
            if (command.isCmd("T32")) OnTest32(command);
            if (command.isCmd("T41")) OnTest41(command);
            if (command.isCmd("T42")) OnTest42(command);
            if (command.isCmd("T51")) OnTest51(command);
            if (command.isCmd("T61")) OnTest61(command);
            if (command.isCmd("T71")) OnTest71(command);
            if (command.isCmd("T81")) OnTest81(command);
            if (command.isCmd("T91")) OnTest91(command);
            if (command.isCmd("T92")) OnTest92(command);
            if (command.isCmd("T93")) OnTest93(command);
        }

        public void OnTest11 (CmdLineCmd command)
        {
            SoundSignal ss = new SoundSignal();
            ss.Name = "Test11";
            ss.Fs = 44100.0;
            ss.Fp = 400.0;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen1(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            SoundFile.WriteToTextFile(ss, ss.Np * 2);
            Console.WriteLine("Done");
        }

        public void OnTest21 (CmdLineCmd command)
        {
            SoundSignal ss = new SoundSignal();
            ss.Name = "Test21";
            ss.Fs = 44100.0;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen2(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            Console.WriteLine("Done");
        }

        public void OnTest22(CmdLineCmd command)
        {
            SoundSignal ss = new SoundSignal();
            ss.Name = "Test22";
            ss.Fs = 44100.0/2.0;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen2(ss);
            SoundFilter.Filter1(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            Console.WriteLine("Done");
        }

        public void OnTest23(CmdLineCmd command)
        {
            command.setArgDefault(1, 0.02);

            SoundSignal ss = new SoundSignal();
            ss.Name = "Test23";
            ss.Fs = 44100.0;
            ss.Alpha = command.argDouble(1);
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen2(ss);
            SoundFilter.AlphaFilter(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            Console.WriteLine("Done");
        }

        public void OnTest24(CmdLineCmd command)
        {
            command.setArgDefault(1, 0.02);

            SoundSignal ss = new SoundSignal();
            ss.Name = "Test24";
            ss.Fs = 44100.0;
            ss.Alpha = command.argDouble(1);
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen2(ss);
            SoundFilter.AlphaBetaFilter(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            Console.WriteLine("Done");
        }

        public void OnTest31(CmdLineCmd command)
        {
            SoundSignal ss = new SoundSignal();
            ss.Name = "Test31";
            ss.Fs = 44100.0;
            ss.Fp = 400.0;
            ss.DCp = 0.1;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen3(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            SoundFile.WriteToTextFile(ss, ss.Np * 2);
            Console.WriteLine("Done");
        }

        public void OnTest32(CmdLineCmd command)
        {
            command.setArgDefault(1, 0.02);

            SoundSignal ss = new SoundSignal();
            ss.Name = "Test32";
            ss.Fs = 44100.0;
            ss.Fp = 100.0;
            ss.Alpha = command.argDouble(1);
            ss.DCp = 0.5;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen3(ss);
            ss.Normalize();
            SoundFilter.AlphaBetaFilter(ss);
            SoundFile.WriteToWaveFile(ss);
            SoundFile.WriteToTextFile(ss, ss.Np * 2);
            Console.WriteLine("Done");
        }

        public void OnTest41(CmdLineCmd command)
        {
            SoundSignal ss = new SoundSignal();
            ss.Name = "Test41";
            ss.Fs = 44100.0;
            ss.Fp = 400.0;
            ss.Fm = 40.0;
            ss.DCm = 0.2;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen41(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            SoundFile.WriteToTextFile(ss, ss.Nm * 2);
            Console.WriteLine("Done");
        }

        public void OnTest42(CmdLineCmd command)
        {
            SoundSignal ss = new SoundSignal();
            ss.Name = "Test42";
            ss.Fs = 44100.0;
            ss.Fp = 800.0;
            ss.Duration = 20.0*60;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen42(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            SoundFile.WriteToTextFile(ss, ss.Nm * 2);
            Console.WriteLine("Done");
        }

        public void OnTest51(CmdLineCmd command)
        {
            SoundSignal ss = new SoundSignal();
            ss.Name = "Test51";
            ss.Fs = 44100.0;
            ss.Fp = 400.0;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen5(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            SoundFile.WriteToTextFile(ss, ss.Np * 2);
            Console.WriteLine("Done");
        }

        public void OnTest61(CmdLineCmd command)
        {
            SoundSignal ss = new SoundSignal();
            ss.Name = "Test61";
            ss.Fs = 44100.0;
            ss.Fp = 400.0;
            ss.DCp = 0.5;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen6(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            SoundFile.WriteToTextFile(ss, ss.Np * 2);
            Console.WriteLine("Done");
        }

        public void OnTest71(CmdLineCmd command)
        {
            SoundSignal ss = new SoundSignal();
            ss.Name = "Test71";
            ss.Fs = 44100.0;
            ss.Fp = 400.0;
            ss.Fm = 4.0;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen7(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            SoundFile.WriteToTextFile(ss, ss.Np * 2);
            Console.WriteLine("Done");
        }

        public void OnTest81(CmdLineCmd command)
        {
            SoundSignal ss = new SoundSignal();
            ss.Name = "Test81";
            ss.Fs = 44100.0;
            ss.Fp = 200.0;
            ss.Fm = 8.0;
            ss.M1 = 5.0;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen8(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            SoundFile.WriteToTextFile(ss, ss.Np * 2);
            Console.WriteLine("Done");
        }

        public void OnTest91(CmdLineCmd command)
        {
            command.setArgDefault(1, 50.0);

            SoundSignal ss = new SoundSignal();
            ss.Name = "Test91";
            ss.Fs = 44100.0;
            ss.Fp = command.argDouble(1);
            ss.M1 = 2.0;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen91(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            SoundFile.WriteToTextFile(ss, ss.Np * 2);
            Console.WriteLine("Done");
        }

        public void OnTest92(CmdLineCmd command)
        {
            SoundSignal ss = new SoundSignal();
            ss.Name = "Test92";
            ss.Fs = 44100.0;
            ss.Fp = 1200.0;
            ss.Duration = 10.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen92(ss);
            ss.Normalize();
            SoundFile.WriteToWaveFile(ss);
            SoundFile.WriteToTextFile(ss, ss.Np * 2);
            Console.WriteLine("Done");
        }

        public void OnTest93(CmdLineCmd command)
        {
            command.setArgDefault(1, 0.05);

            SoundSignal ss = new SoundSignal();
            ss.Name = "Test93";
            ss.Fs = 44100.0;
            ss.Fp = 1200.0;
            ss.Alpha = command.argDouble(1);
            ss.Duration = 20.0*60.0;
            ss.MakeConsistent();
            ss.Show();
            SoundGenerate.Gen92(ss);
            ss.Normalize();
            SoundFilter.AlphaBetaFilter(ss);
            SoundFile.WriteToWaveFile(ss);
            Console.WriteLine("Done");
        }
    }
}


