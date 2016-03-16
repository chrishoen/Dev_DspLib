using System;
using System.Collections.Generic;
using Ris;

namespace SoundDevelop
{
    public class AlphaFilter
    {
        public double _Alpha;
        public double _Xs;

        public AlphaFilter(double alpha)
        {
            _Alpha = alpha;
            _Xs = 0.0;
        }

        public AlphaFilter(double lambdaRatio, double deltaT)
        {
            double lambda = lambdaRatio * Math.Pow(deltaT, 2.0);

            _Alpha = (-Math.Pow(lambda, 2.0) + Math.Sqrt(Math.Pow(lambda, 4.0) + 16.0 * Math.Pow(lambda, 2.0))) / 8.0;

            _Xs = 0.0;
        }

        public double Calculate(double x)
        {
            _Xs = _Alpha * x + (1.0 - _Alpha) * _Xs;
            return _Xs;
        }

    }

    public class AlphaBetaFilter
    {
        /// <summary>
        /// Members
        /// </summary>
        double _Alpha;
        double _Beta;
        double _DT;
        double _Xs;
        double _Vs;

        public AlphaBetaFilter(double alpha, double dt)
        {
            _Alpha = alpha;
            _DT = dt;

            _Beta = Math.Pow(alpha, 2.0) / (2.0 - alpha);

            _Xs = 0.0;
            _Vs = 0.0;
        }

        public double Calculate(double x)
        {
            double xk, vk, rk;

            xk = _Xs + (_Vs * _DT);
            vk = _Vs;

            rk = x - xk;

            xk += _Alpha * rk;
            vk += (_Beta * rk) / _DT;

            _Xs = xk;
            _Vs = vk;

            return _Xs;
        }

    }

}
