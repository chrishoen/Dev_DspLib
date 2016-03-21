
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prnPrint.h"
#include "my_functions.h"
#include "dspFilterFilters.h"
#include "dspFilterAlpha.h"
#include "dspFilterStatistics.h"

#include "CmdLineExec.h"

//******************************************************************************
CmdLineExec::CmdLineExec()
{
   mStepFlag=true;
}
//******************************************************************************
void CmdLineExec::reset()
{
}
//******************************************************************************
void CmdLineExec::execute(Ris::CmdLineCmd* aCmd)
{
   if(aCmd->isCmd("RESET"  ))  reset();
   if(aCmd->isCmd("GO1"    ))  executeGo1  (aCmd);
   if(aCmd->isCmd("GO2"    ))  executeGo2  (aCmd);
   if(aCmd->isCmd("GO3"    ))  executeGo3  (aCmd);
   if(aCmd->isCmd("GO4"    ))  executeGo4  (aCmd);
   if(aCmd->isCmd("GO5"    ))  executeGo5  (aCmd);
   if(aCmd->isCmd("GO6"    ))  executeGo6  (aCmd);
   if(aCmd->isCmd("GO7"    ))  executeGo7  (aCmd);
   if(aCmd->isCmd("GO8"    ))  executeGo8  (aCmd);
   if(aCmd->isCmd("GO9"    ))  executeGo9  (aCmd);
   if(aCmd->isCmd("GO10"   ))  executeGo10 (aCmd);
   if(aCmd->isCmd("GO11"   ))  executeGo11 (aCmd);
   if(aCmd->isCmd("GO12"   ))  executeGo12 (aCmd);
   if(aCmd->isCmd("GO13"   ))  executeGo13 (aCmd);
   if(aCmd->isCmd("GO14"   ))  executeGo14 (aCmd);
   if(aCmd->isCmd("GO15"   ))  executeGo15 (aCmd);
   if(aCmd->isCmd("GO16"   ))  executeGo16 (aCmd);
   if(aCmd->isCmd("GO21"   ))  executeGo21 (aCmd);
   if(aCmd->isCmd("GO22"   ))  executeGo22 (aCmd);

   if(aCmd->isCmd("STEP"   ))  mStepFlag=true;
   if(aCmd->isCmd("RAMP"   ))  mStepFlag=false;
}

//******************************************************************************

void CmdLineExec::executeGo1(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::AlphaOne tF;
   tF.initialize(0.201107);

   for (int i=0;i<10;i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i=0;i<70;i++)
   {
      if (mStepFlag) tF.put(1.0);
      else           tF.put(i*1.0);
      tF.show();
   }
   Prn::print(0,"");
}

//******************************************************************************

void CmdLineExec::executeGo2(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::AlphaTwo tF;
   tF.initialize(0.201107,0.0225534,1.0);

   for (int i=0;i<10;i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i=0;i<70;i++)
   {
      if (mStepFlag) tF.put(1.0);
      else           tF.put(i*1.0);
      tF.show();
   }
   Prn::print(0,"");
}

//******************************************************************************

void CmdLineExec::executeGo3(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::AlphaThree tF;
   tF.initialize(0.201107,0.0225534,0.00126464,1.0);

   for (int i=0;i<10;i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i=0;i<70;i++)
   {
      if (mStepFlag) tF.put(1.0);
      else           tF.put(i*1.0);
      tF.show();
   }
   Prn::print(0,"");
}

//******************************************************************************

void CmdLineExec::executeGo4(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::MovingAverage tF;
   tF.initialize(10);

   for (int i=0;i<20;i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i=0;i<20;i++)
   {
      tF.put(1.0);
      tF.show();
   }
   Prn::print(0,"");

}

//******************************************************************************

void CmdLineExec::executeGo5(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::ShiftRegister tF;
   tF.initialize(4);

   for (int i=0;i<16;i++)
   {
      tF.shiftRight(i*1.0);
   }

   for (int i=0;i<4;i++)
   {
      Prn::print(0,"%3d %8.3f",i,tF.get(i));
   }
}

//******************************************************************************

void CmdLineExec::executeGo6(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo7(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::FIRTestFilter tF;
   tF.initialize();

   for (int i=0;i<8;i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i=0;i<8;i++)
   {
      tF.put(1.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i=0;i<8;i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

}

//******************************************************************************

void CmdLineExec::executeGo8(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::IIRTestFilter tF;
   tF.initialize();

   for (int i=0;i<8;i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i=0;i<8;i++)
   {
      tF.put(1.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i=0;i<8;i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

}

//******************************************************************************

void CmdLineExec::executeGo9(Ris::CmdLineCmd* aCmd)
{
   aCmd->setArgDefault(1,3);

   Dsp::Filter::MovingDerivative tF;
   tF.initialize(aCmd->argInt(1),1.0);

   for (int i=0;i<20;i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i=0;i<20;i++)
   {
      tF.put(i*1.0);
      tF.show();
   }
   Prn::print(0,"");

}

//******************************************************************************

void CmdLineExec::executeGo10(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::CharacterFilter1 tF;
   tF.initialize(1.0);

   for (int i = 0; i<20; i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(i*1.0);
      tF.show();
   }
}

//******************************************************************************

void CmdLineExec::executeGo11(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::CharacterFilter1 tF;
   tF.initialize(1.0);

   for (int i=0;i<20;i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i=0;i<20;i++)
   {
      tF.put(1.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i=0;i<20;i++)
   {
      tF.put(0.0);
      tF.show();
   }
}

//******************************************************************************

void CmdLineExec::executeGo12(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::AlphaStatistics tF;
   tF.initialize(1.0);

   for (int i = 0; i<20; i++)
   {
      tF.put(0.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(i*1.0);
      tF.show();
   }
}

//******************************************************************************

void CmdLineExec::executeGo13(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::PeriodicStatistics tF;
   tF.initialize(40);

   for (int i = 0; i<20; i++)
   {
      tF.put(1.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(2.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(1.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(2.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(1.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(2.0);
      tF.show();
   }
   Prn::print(0,"");
}


//******************************************************************************

void CmdLineExec::executeGo14(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::ShiftRegister tF;
   tF.initialize(4);

   for (int i = 0; i<16; i++)
   {
      tF.shiftRight(11.0 + i*1.0);
      Prn::print(0,"%3d %8.3f %8.3f", i, tF.getLeft(), tF.getRight());
   }

}

//******************************************************************************

void CmdLineExec::executeGo15(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::ShiftRegister tF;
   tF.initialize(256);

   for (int i = 0; i<1000; i++)
   {
      tF.shiftRight(11.0 + i*1.0);
   }

   for (int i = 0; i<16; i++)
   {
      tF.shiftRight(11.0 + i*1.0);
      Prn::print(0,"%3d %8.3f %8.3f", i, tF.getLeft(), tF.getRight());
   }

}

//******************************************************************************

void CmdLineExec::executeGo16(Ris::CmdLineCmd* aCmd)
{
}

//******************************************************************************

void CmdLineExec::executeGo21(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::PeriodicStatistics tF;
   tF.initialize(40);

   for (int i = 0; i<20; i++)
   {
      tF.put(1.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(2.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(1.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(2.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(1.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(2.0);
      tF.show();
   }
   Prn::print(0,"");
}

//******************************************************************************

void CmdLineExec::executeGo22(Ris::CmdLineCmd* aCmd)
{
   Dsp::Filter::PeriodicStatistics tF;
   tF.initialize(40);

   for (int i = 0; i<20; i++)
   {
      tF.put(2.0 + 10.0);
      tF.show();
   }
   Prn::print(0,"");

   for (int i = 0; i<20; i++)
   {
      tF.put(-2.0 + 10.0);
      tF.show();
   }
   Prn::print(0,"");


}

