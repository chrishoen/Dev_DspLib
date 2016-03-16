using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using Ris;

namespace SoundDevelop
{
    // The class contains sound parameters 
    public class SoundSignal
    {
        // Constructor
        public SoundSignal()
        {
            m_Name = "Default";
            m_Fs = 8000.0;
            m_Ts = 1.0 / m_Fs;
            m_Fp = 1.0;
            m_Fm = 1.0;
            m_Tp = 1.0 / m_Fp;
            m_Tm = 1.0 / m_Fm;

            m_DCp = 1.0;
            m_DCm = 1.0;
            m_Alpha = 0.0;
            
            m_Duration = 10.0;
            m_NumSamples = (int)(m_Duration * m_Fs);
        }

        // MakeConsistent
        public void MakeConsistent()
        {
            m_Ts = 1.0 / m_Fs;

            m_Np = (int)Math.Round(m_Fs / m_Fp);
            m_Np1 = (int)Math.Round(m_DCp * m_Np);
            m_Np2 = (int)Math.Round((1.0 - m_DCp) * m_Np);
            m_Fp = m_Fs / (double)m_Np;
            m_Tp = 1.0 / m_Fp;

            m_Nm = (int)Math.Round(m_Fp / m_Fm)*m_Np;
            m_Nm1 = (int)Math.Round(m_DCm * m_Nm);
            m_Nm2 = (int)Math.Round((1.0 - m_DCm) * m_Nm);
            m_Fm = m_Fp * (double)m_Np/(double)m_Nm;
            m_Tm = 1.0 / m_Fm;

            double nsamples = (int)(Math.Round(m_Duration) * m_Fs);
            m_Ns = (int)Math.Round(nsamples / m_Np) * m_Np;
            m_Duration = m_Ns * m_Ts;
            m_NumSamples = m_Ns;
            m_X = new double[m_NumSamples];
        }

        // Normalize
        public void Normalize()
        {
            // Get min and max
            double xMin = 0.0;
            double xMax = 0.0;

            for (int k = 0; k < m_Ns; k++)
            {
                double x = m_X[k];
                if (x < xMin) xMin = x;
                if (x > xMax) xMax = x;
            }

            // Get scale and offset
            if (xMin != xMax)
            {
                double scale = 1.0 / ((xMax - xMin) / 2.0);
                double offset = (xMax + xMin) / 2.0;

                // Adjust signal to be -1 <= x[k] <= 1
                for (int k = 0; k < m_Ns; k++)
                {
                    double x = m_X[k];
                    double xa = scale * (x - offset);
                    m_X[k] = xa;
                }
            }

        }

        // Show
        public void Show()
        {
            Console.WriteLine("Fs           {0,10}     {1,10}", m_Fs.ToString("F2"), m_Ts.ToString("F8"));
            Console.WriteLine("Fp           {0,10}     {1,10}", m_Fp.ToString("F2"), m_Tp.ToString("F8"));
            Console.WriteLine("Fm           {0,10}     {1,10}", m_Fm.ToString("F2"), m_Tm.ToString("F8"));
            Console.WriteLine("Duration     {0,10}", m_Duration.ToString("F2"));
            Console.WriteLine("NumSamples   {0,10}", m_NumSamples);
            Console.WriteLine("Ns           {0,10}", m_Ns);
            Console.WriteLine("Np           {0,10}", m_Np);
            Console.WriteLine("Np1          {0,10}", m_Np1);
            Console.WriteLine("Np2          {0,10}", m_Np2);
            Console.WriteLine("Nm           {0,10}", m_Nm);
            Console.WriteLine("Nm1          {0,10}", m_Nm1);
            Console.WriteLine("Nm2          {0,10}", m_Nm2);
            Console.WriteLine("");
        }

        // Property
        public String Name
        {
            get { return m_Name; }
            set { m_Name = value; }
        }
        private String m_Name;

        // Property
        public double[] X
        {
            get { return m_X; }
            set { m_X = value; }
        }
        private double[] m_X;

        // Property
        public double Fs
        {
            get { return m_Fs; }
            set { m_Fs = value; m_Ts = 1.0 / m_Fs; }
        }
        private double m_Fs;

        // Property
        public double Ts
        {
            get { return m_Ts; }
            set { m_Ts = value; m_Fs = 1.0 / m_Ts; }
        }
        private double m_Ts;

        // Property
        public double Fp
        {
            get { return m_Fp; }
            set { m_Fp = value; m_Tp = 1.0 / m_Fp; }
        }
        private double m_Fp;

        // Property
        public double Tp
        {
            get { return m_Tp; }
            set { m_Tp = value; m_Fp = 1.0 / m_Tp; }
        }
        private double m_Tp;

        // Property
        public double Fm
        {
            get { return m_Fm; }
            set { m_Fm = value; m_Ts = 1.0 / m_Fm; }
        }
        private double m_Fm;

        // Property
        public double Tm
        {
            get { return m_Tm; }
            set { m_Tm = value; m_Fs = 1.0 / m_Tm; }
        }
        private double m_Tm;

        // Property
        public double Duration
        {
            get { return m_Duration; }
            set { m_Duration = value; }
        }
        private double m_Duration;

        // Property
        public int NumSamples
        {
            get { return m_NumSamples; }
            set { m_NumSamples = value; }
        }
        private int m_NumSamples;

        // Property
        public int Ns
        {
            get { return m_Ns; }
            set { m_Ns = value; }
        }
        private int m_Ns;

        // Property
        public int Np
        {
            get { return m_Np; }
            set { m_Np = value; }
        }
        private int m_Np;

        // Property
        public int Np1
        {
            get { return m_Np1; }
            set { m_Np1 = value; }
        }
        private int m_Np1;

        // Property
        public int Np2
        {
            get { return m_Np2; }
            set { m_Np2 = value; }
        }
        private int m_Np2;

        // Property
        public int Nm
        {
            get { return m_Nm; }
            set { m_Nm = value; }
        }
        private int m_Nm;

        // Property
        public int Nm1
        {
            get { return m_Nm1; }
            set { m_Nm1 = value; }
        }
        private int m_Nm1;

        // Property
        public int Nm2
        {
            get { return m_Nm2; }
            set { m_Nm2 = value; }
        }
        private int m_Nm2;

        // Property
        public double DCp
        {
            get { return m_DCp; }
            set { m_DCp = value; }
        }
        private double m_DCp;

        // Property
        public double DCm
        {
            get { return m_DCm; }
            set { m_DCm = value; }
        }
        private double m_DCm;

        // Property
        public double M1
        {
            get { return m_M1; }
            set { m_M1 = value; }
        }
        private double m_M1;

        // Property
        public double Alpha
        {
            get { return m_Alpha; }
            set { m_Alpha = value; }
        }
        private double m_Alpha;

    }

}
