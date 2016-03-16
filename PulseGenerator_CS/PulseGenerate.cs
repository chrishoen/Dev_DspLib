using System;
using System.Collections.Generic;
using Ris;

namespace PulseDevelop
{
    // The class contains static methods that generate sound signals
    public class PulseGenerate
    {
        // Generate sin wave
        public static void Gen1(PulseSignal ss)
        {
            for (int k = 0; k < ss.Ns; k++)
            {
                double t = k * ss.Ts;
                ss.X[k] = Math.Sin(2.0 * Math.PI * ss.Fp * t);
            }
        }

        // Generate white noise
        public static void Gen2(PulseSignal ss)
        {
            Random r = new Random();
            for (int k = 0; k < ss.Ns; k++)
            {
                ss.X[k] = 2.0 * (r.NextDouble() - 0.5);
            }
        }

        // Generate square wave
        public static void Gen3(PulseSignal ss)
        {
            for (int k = 0; k < ss.Ns; k++)
            {
                ss.X[k] = (k % ss.Np <= ss.Np1) ? 1.0 : 0.0;
            }
        }

        // Generate pulse train
        public static void Gen41(PulseSignal ss)
        {
            for (int k = 0; k < ss.Ns; k++)
            {
                double t = k * ss.Ts;
                double x = Math.Sin(2.0 * Math.PI * ss.Fp * t);
                ss.X[k] = (k % ss.Nm <= ss.Nm1) ? x : 0.0;
            }
        }

        // Generate random pulse train
        public static void Gen42(PulseSignal ss)
        {
            Random r = new Random();
            double a = 1.0;

            for (int k = 0; k < ss.Ns; k++)
            {
                if (k % ss.Np == 0)
                {
                    a = (r.NextDouble() > 0.5) ? 1.0 : 0.0;
                }

                double t = k * ss.Ts;
                ss.X[k] = a * Math.Sin(2.0 * Math.PI * ss.Fp * t);
            }
        }

        // Generate sawtooth wave
        public static void Gen5(PulseSignal ss)
        {
            for (int k = 0; k < ss.Ns; k++)
            {
                ss.X[k] = (double)(k % ss.Np) / (double)ss.Np;
            }
        }

        // Generate triangle wave
        public static void Gen6(PulseSignal ss)
        {
            for (int k = 0; k < ss.Ns; k++)
            {
                int p = k % ss.Np;
                if (p <= ss.Np1)
                {
                    ss.X[k] = (double)(p) / (double)ss.Np1;
                }
                else
                {
                    ss.X[k] = 1.0 - ((double)(p - ss.Np1) / (double)ss.Np2);
                }
            }
        }

        // Generate am wave
        public static void Gen7(PulseSignal ss)
        {
            for (int k = 0; k < ss.Ns; k++)
            {
                double t = k * ss.Ts;
                ss.X[k] = Math.Sin(2.0 * Math.PI * ss.Fp * t) * Math.Sin(2.0 * Math.PI * ss.Fm * t);
            }
        }

        // Generate fm wave
        public static void Gen8(PulseSignal ss)
        {
            for (int k = 0; k < ss.Ns; k++)
            {
                double t = k * ss.Ts;
                ss.X[k] = Math.Cos(2.0 * Math.PI * ss.Fp * t + ss.M1 * Math.Cos(2.0 * Math.PI * ss.Fm * t));
            }
        }

        // Generate sin wave
        public static void Gen91(PulseSignal ss)
        {
            Random r = new Random();
            
            for (int k = 0; k < ss.Ns; k++)
            {
                double t = k * ss.Ts;
                ss.X[k] = Math.Sin(2.0 * Math.PI * ss.Fp * t) + Math.Sin(2.0 * Math.PI * 2.0 * ss.Fp * t) + Math.Sin(2.0 * Math.PI * 3.0 * ss.Fp * t) + 0.0 * 2.0 * (r.NextDouble() - 0.5);
            }
        }

        // Generate random BPSK wave
        public static void Gen92(PulseSignal ss)
        {
            Random r = new Random();
            double a = 1.0;

            for (int k = 0; k < ss.Ns; k++)
            {
                if (k % ss.Np == 0)
                {
                    a = (r.NextDouble() > 0.5) ? 1.0 : -1.0;
                }

                double t = k * ss.Ts;
                ss.X[k] = a * Math.Cos(2.0 * Math.PI * ss.Fp * t);
                ss.X[k] = 0.8*a;
            }
        }

    }
}
