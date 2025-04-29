#pragma once

#include "dspSlidingWindow.h"
#include "dspSlidingMean.h"
#include "risCmdLineExec.h"

//******************************************************************************
// specific command line executive
//******************************************************************************

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

  Dsp::SlidingWindow<int, 4> mWindow;
  Dsp::SlidingMean<float, 4> mMinMaxMean;

  CmdLineExec();

  void reset();
  void execute(Ris::CmdLineCmd* aCmd);

  void executePut(Ris::CmdLineCmd* aCmd);
  void executeGet(Ris::CmdLineCmd* aCmd);
  void executeTail(Ris::CmdLineCmd* aCmd);
  void executePutMMM(Ris::CmdLineCmd* aCmd);
  void executeShow(Ris::CmdLineCmd* aCmd);
  
  void executeGo1(Ris::CmdLineCmd* aCmd);
  void executeGo2(Ris::CmdLineCmd* aCmd);
  void executeGo3(Ris::CmdLineCmd* aCmd);
  void executeGo4(Ris::CmdLineCmd* aCmd);
  void executeGo5(Ris::CmdLineCmd* aCmd);
};

//******************************************************************************

