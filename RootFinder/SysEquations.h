#pragma once

/*==============================================================================
==============================================================================*/
#include "Special_Parms.h"
#include "dspFunctionObject.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************




//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a base class for classes that encapsualte function objects. 

class SysEquations : public Dsp::BaseFunctionObject
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   Special_Parms mP;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   //Coefficient Params
   double mX0;
   double mY0;


   double mA120;
   double mA121;
   double mA122;
   double mA340;
   double mA341;
   double mA342;

   double mB120;
   double mB121;
   double mB122;
   double mB340;
   double mB341;
   double mB342;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infastrucure:

   // Constructor.
   SysEquations(Special_Parms& aP);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // This evaluates the function at the input value array.
   void evaluateFunction(
      Eigen::VectorXd& aX,                    // Input
      Eigen::VectorXd& aY) override;          // Output

   // This evaluates the jacobian of the function at the input value array.
   void evaluateJacobian(
      Eigen::VectorXd& aX,                    // Input
      Eigen::MatrixXd& aJacobian) override;   // Output

   // This returns the dimension of the function input vector.
   int dimension() override { return 2; }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
