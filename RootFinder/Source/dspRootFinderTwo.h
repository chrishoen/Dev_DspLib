#pragma once

/*==============================================================================
==============================================================================*/
#include <Eigen\Dense>
#include "dspFunctionObject.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Dsp
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is a base class for classes that encapsualte function objects. 

class BaseRootFinderFunctionObjectTwo
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // This evaluates the function at the input value array.
   virtual void evaluateFunction(
      Eigen::VectorXd& aX,                  // Input
      Eigen::VectorXd& aY)=0;               // Output

   // This evaluates the jacobian of the function at the input value array.
   virtual void evaluateJacobian(
      Eigen::VectorXd& aX,                  // Input
      Eigen::MatrixXd& aJacobian)=0;        // Output

   // This returns the dimension of the function input vector.
   virtual int dimension()=0;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides the functionality to find roots of equations using
// the Newton rapheson method.

class RootFinderTwo
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   int mNumSteps;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Infastrucure:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // This finds the roots of a given function, starting at an initial guess.
   bool findRoot(
      BaseRootFinderFunctionObjectTwo* aFunctionObject,  // Input
      Eigen::VectorXd&    aXInitial,            // Input
      Eigen::VectorXd&    aWeight,              // Input
      double              aAccuracy,            // input        
      int                 aMaxSteps,            // input        
      Eigen::VectorXd&    aX)                   // Output
   {
      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Initialize.

      // Initialize the output matrix.
      int tDim = aFunctionObject->dimension();
      aX = Eigen::VectorXd(tDim);

      // Temp independent variable matrix.
      Eigen::VectorXd tXs(tDim);

      // Temp dependent variable matrix.
      Eigen::VectorXd tY(tDim);

      // Temp jacobian matrix.
      Eigen::MatrixXd tJ(tDim, tDim);

	   // Temp jacobian inverse matrix.
	   Eigen::MatrixXd tJinv(tDim, tDim);

      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Loop.

      aX = aXInitial;

      bool tSuccess = false;
      mNumSteps = 0;

      while (true)
      {
         // Evaluate the function and its jacobian at the current
         // iteration value
         aFunctionObject->evaluateFunction(aX, tY);
         aFunctionObject->evaluateJacobian(aX, tJ);

         // Calculate the newton raphson algorithm.
         // change to psuedo inverse
         tJinv = tJ.completeOrthogonalDecomposition().pseudoInverse();
         tXs = aX - tJinv*tY;

         // Caclulate the difference between the current and previous
         // iterations.
         double tDiff = (tXs - aX).norm();

         // Store the current iteration value.
         aX = tXs;

         // Test the difference.
         if (tDiff < aAccuracy)
         {
            tSuccess = true;
            break;
         }

         // Test the number of iteration steps.
         if (++mNumSteps > aMaxSteps)
         {
            tSuccess = false;
            break;
         }
      } 

      // Done.
      return tSuccess;      
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
