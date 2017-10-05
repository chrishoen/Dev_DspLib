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

template<int Dim>
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
      Eigen::Matrix<double,Dim,1>&   aX,                // Input
      Eigen::Matrix<double,Dim,1>&   aY)=0;             // Output

   // This evaluates the jacobian of the function at the input value array.
   virtual void evaluateJacobian(
      Eigen::Matrix<double,Dim,1>&   aX,                // Input
      Eigen::Matrix<double,Dim,Dim>& aJacobian)=0;      // Output
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class provides the functionality to find roots of equations using
// the Newton rapheson method.

template<int Dim>
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
   // Infrastrucure:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // This finds the roots of a given function, starting at an initial guess.
   bool findRoot(
      BaseRootFinderFunctionObjectTwo<Dim>* aFunctionObject,  // Input
      Eigen::Matrix<double,Dim,1>&    aXInitial,              // Input
      Eigen::Matrix<double,Dim,1>&    aWeight,                // Input
      double                          aAccuracy,              // Input        
      int                             aMaxSteps,              // Input        
      Eigen::Matrix<double,Dim,1>&    aX)                     // Output
   {
      //***************************************************************************
      //***************************************************************************
      //***************************************************************************
      // Initialize.

      // Temp independent variable matrix.
      Eigen::Matrix<double,Dim,1> tXs;

      // Temp dependent variable matrix.
      Eigen::Matrix<double,Dim,1> tY;

      // Temp jacobian matrix.
      Eigen::Matrix<double,Dim,Dim> tJ;

	   // Temp jacobian inverse matrix.
      Eigen::Matrix<double,Dim,Dim> tJinv;

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
//       tJinv = tJ.completeOrthogonalDecomposition().pseudoInverse();
         tJinv = tJ.inverse();
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
