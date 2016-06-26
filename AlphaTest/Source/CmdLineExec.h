#ifndef _CMDLINEEXEC_H_
#define _CMDLINEEXEC_H_

#include "risCmdLineExec.h"

//******************************************************************************
// specific command line executive
//******************************************************************************

class CmdLineExec : public Ris::BaseCmdLineExec
{
public:

   CmdLineExec();

   void reset();
   void execute(Ris::CmdLineCmd* aCmd);

   void executeGo1(Ris::CmdLineCmd* aCmd);
   void executeGo2(Ris::CmdLineCmd* aCmd);

   void executeTestAlphaOne        (Ris::CmdLineCmd* aCmd);
   void executeTestAlphaTwo        (Ris::CmdLineCmd* aCmd);
   void executeTestAlphaThree      (Ris::CmdLineCmd* aCmd);
   void executeTestAlphaStatistics (Ris::CmdLineCmd* aCmd);
   void executeTestMovingAverage   (Ris::CmdLineCmd* aCmd);
   void executeTrialStatistics     (Ris::CmdLineCmd* aCmd);


  void executeConstant (Ris::CmdLineCmd* aCmd);
  void executeImpulse  (Ris::CmdLineCmd* aCmd);
  void executeStep     (Ris::CmdLineCmd* aCmd);
  void executeRamp     (Ris::CmdLineCmd* aCmd);
  void executeSinusoid (Ris::CmdLineCmd* aCmd);

  double mAlphaOneAP1;
  double mAlphaTwoAP1;
  double mAlphaTwoAP2;
  double mAlphaThreeAP1;
  double mAlphaThreeAP2;
  double mAlphaThreeAP3;

};

//******************************************************************************
#endif

