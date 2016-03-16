using System;
using System.Collections.Generic;
using Ris;

namespace SoundDevelop
{
    public partial class SoundFilter
    {
        public static void Filter1(SoundSignal ss)
        {
            // Local
            double[] b = m_Coeff_LowPass1;
            double[] y = new double[ss.Ns];

            // FIR convolution
            for (int k = 0; k < ss.Ns; k++)
            {
                double sum = 0.0;
                for (int m = 0; m < b.Length; m++)
                {
                    int n = (k - m >= 0) ? k - m : ss.Ns - m;
                    sum += b[m] * ss.X[n];
                }
                y[k] = sum;
            }

            // Transfer to signal
            ss.X = y;
        }

        public static void AlphaFilter(SoundSignal ss)
        {
            // Local
            AlphaFilter filter = new AlphaFilter(ss.Alpha);
            double[] y = new double[ss.Ns];

            // Apply filter to samples
            for (int k = 0; k < ss.Ns; k++)
            {
                y[k] = filter.Calculate(ss.X[k]);
            }

            // Transfer to signal
            ss.X = y;
        }

        public static void AlphaBetaFilter(SoundSignal ss)
        {
            // Local
            AlphaBetaFilter filter = new AlphaBetaFilter(ss.Alpha, ss.Ts);
            double[] y = new double[ss.Ns];

            // Apply filter to samples
            for (int k = 0; k < ss.Ns; k++)
            {
                y[k] = filter.Calculate(ss.X[k]);
            }

            // Transfer to signal
            ss.X = y;
        }

    }

}
