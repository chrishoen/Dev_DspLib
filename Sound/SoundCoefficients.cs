using System;
using System.Collections.Generic;
using Ris;

namespace SoundDevelop
{
    public partial class SoundFilter
    {
        // Matlab fir1(100,0.10)
        public static double[] m_Coeff_LowPass1 = new double[100]{
            0.00000000000000000031,
            0.00016201819402187292,
            0.00032517175807679618,
            0.00048179157777351639,
            0.00062007768829641825,
            0.00072336634212022009,
            0.00077078262862471979,
            0.00073947880378070737,
            0.00060835497027562305,
            0.00036283698825646284,
            -0.00000000000000000065,
            -0.00046687314004737959,
            -0.00100527828658563770,
            -0.00156291410286396310,
            -0.00207018969610240580,
            -0.00244607473642213850,
            -0.00260706732349189450,
            -0.00247853616048936910,
            -0.00200721275417657450,
            -0.00117324086890998550,
            0.00000000000000000155,
            0.00144004582531247640,
            0.00302494278187036190,
            0.00458924057107598820,
            0.00593663545710492680,
            0.00685869312840307800,
            0.00715823824029578580,
            0.00667523780804289350,
            0.00531243343869921510,
            0.00305768132666186430,
            -0.00000000000000000265,
            -0.00366327209777640330,
            -0.00763006252278346580,
            -0.01150872186516993200,
            -0.01484437191581891600,
            -0.01715480270969193400,
            -0.01797310075658145900,
            -0.01689324178446703600,
            -0.01361427988779154500,
            -0.00797859857564667260,
            0.00000000000000000355,
            0.01012181336393847900,
            0.02200262809902207200,
            0.03509176806306681100,
            0.04870596733205653800,
            0.06207663420494879300,
            0.07440666649754793000,
            0.08493192028289429900,
            0.09298184457803325400,
            0.09803374528688940700,
            0.09975564789545325600,
            0.09803374528688940700,
            0.09298184457803325400,
            0.08493192028289429900,
            0.07440666649754793000,
            0.06207663420494879300,
            0.04870596733205653800,
            0.03509176806306681100,
            0.02200262809902207200,
            0.01012181336393847900,
            0.00000000000000000355,
            -0.00797859857564667260,
            -0.01361427988779154500,
            -0.01689324178446703600,
            -0.01797310075658145900,
            -0.01715480270969193400,
            -0.01484437191581891600,
            -0.01150872186516993200,
            -0.00763006252278346580,
            -0.00366327209777640330,
            -0.00000000000000000265,
            0.00305768132666186430,
            0.00531243343869921510,
            0.00667523780804289350,
            0.00715823824029578580,
            0.00685869312840307800,
            0.00593663545710492680,
            0.00458924057107598820,
            0.00302494278187036190,
            0.00144004582531247640,
            0.00000000000000000155,
            -0.00117324086890998550,
            -0.00200721275417657450,
            -0.00247853616048936910,
            -0.00260706732349189450,
            -0.00244607473642213850,
            -0.00207018969610240580,
            -0.00156291410286396310,
            -0.00100527828658563770,
            -0.00046687314004737959,
            -0.00000000000000000065,
            0.00036283698825646284,
            0.00060835497027562305,
            0.00073947880378070737,
            0.00077078262862471979,
            0.00072336634212022009,
            0.00062007768829641825,
            0.00048179157777351639,
            0.00032517175807679618,
            0.00016201819402187292};

    }

}
