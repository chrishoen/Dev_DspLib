# Dev_DspLib
### digital signal processng library, C++, vstudio, cmake windows and linux

This is a library of C++ classes that provides some realtime functionality. Features include:
   1. butterworth and alpha beta gamma causal recursive filters.
   2. signal history buffers with noncausal filtering for smoothing and differentiating
   3. signal generators for history buffers
   4. signal statistics
   5. legacy R3 vectors and matrices
   6. fuzzy boolean and slow threaholders
   6. miscellaneous utility functions.

This library is written for Windows and Linux in Visual Studio, using the cmake paradigm. The classes are based on Win32 or pthread realtime functions for threads and sockets and such. The library is portable. The details of the provided functionality that are specific to Win32 are contained in a small set of `*_win.cpp` or `*_linux.cpp`files. It is the intention of the library that programs built under Windows can be rebuilt seamlessly under Linux. CMake is used to implement the cross platform functionality.

The solution contains the library project and a set of associated unit test projects.

## Classes
``` markdown
dspBiasEstimator.h                -- bias estimator
dspButterworthCo.h                -- butterworth lowpass filter coefficients
dspCalTable.h                     -- calbration tables
dspFilterAlphaAbsDev.h            -- short term local absolute deviation alpha filter
dspFilterAlphaOne.h               -- alpha filter 
dspFilterAlphaStdDev.h            -- short term local standard deviation alpha filter
dspFilterAlphaThree.h             -- alpha beta gamma filter
dspFilterAlphaTwo.h               -- alpha beta filter
dspFilterButterworth.h            -- butterworth lowpass filter
dspFilterFilters.h                -- some more filters 
dspFuzzyBool.h                    -- fuzzy logic boolean  
dspHistory.h                      -- signal history buffer, contains time and value pairs  
dspHistoryAlphaFilter.h           -- signal history noncausal alpha beta gamma filter for smoothing/derivatives
dspHistoryConverters.h            -- signal history buffer converters
dspHistoryCsvFileReader.h         -- signal history csv file reader
dspHistoryCsvFileWriter.h         -- signal history csv file writer
dspHistoryFilterCausal.h          -- signal history causal filter operator  
dspHistoryFilterCDiffBase.h       -- signal history noncausal filter central difference method base class  
dspHistoryFilterCDiffHolob.h      -- signal history noncausal filter central difference Holobordko method
dspHistoryFilterCDiffIdentity.h   -- signal history noncausal filter central difference identity method
dspHistoryFilterCDiffSavGol.h     -- signal history noncausal filter central difference Savitzky-Golay method  
dspHistoryFilterNoncausal.h       -- signal history noncausal filter operator
dspHistoryFilterOperator.h        -- signal history filter operator, applies specific filter implementation
dspHistoryFilterParms.h           -- signal history filter parameters
dspHistoryGaussNoise.h            -- signal history gaussian noise generator 
dspHistoryGenBase.h               -- signal history generator base class  
dspHistoryGenerator.h             -- signal history generator, applies specific implementation
dspHistoryGenParms.h              -- signal history generator parameters  
dspHistoryGenRandWave.h           -- signal history generator for a randow wave, lowpass filters gaussian noise   
dspHistoryGenSinWave.h            -- signal history generator for a sin wave
dspHistoryGenStep.h               -- signal history generator for a step function
dspHistoryGenZero.h               -- signal history generator for a sin wave 
dspHistoryLoopClock.h             -- signal history generator loop clock
dspHistoryStatistics.h            -- signal history buffer statistics 
dspPaths.h                        -- file and directory paths  
dspPeriodicStatistics.h           -- periodic statistics
dspRVector.h                      -- vector on R3   
dspSample.h                       -- sample value and time of arrival class
dspSignal.h                       -- legacy signal class
dspSlidingMinMaxMean.h            -- sliding window for min,max,mean
dspSlidingWindow.h                -- sliding window base class
dspSlowThresholder.h              -- slow thresholder 
dspSlowThresholderParms.h         -- slow thresholder parameters
dspSlowThresholderParmsWrapper.h  -- slow thresholder parameters
dspTextFile.h                     -- text file io
dspThreeAxisAngle.h               -- R3 axis angle representation of a rotation  
dspThreeMath.h                    -- R3 include file
dspThreeMatrix.h                  -- R3 matrices, euler angles  
dspThreeVector.h                  -- R3 vectors
dspTrialStatistics.h              -- trial statistics 
dsp_functions.h                   -- utility functions 
dsp_math.h                        -- constants
```

## Solution Projects
``` markdown
AlphaTest       -- unit test for alpha 123 filters using signal generators
Butterworth     -- unit test for butterworth lowass filter coefficients
CalTableTest    -- unit test for calibration tables
DspLib          -- digital signal processing library -- this is the library
FuzzyBool       -- unit test for fuzzy bools
HistoryTest     -- unit test and example code for history buffers, filters, and generators
RootFinder      -- unit test for the root finders
RVectorTest     -- unit test for the R3 vectors and matrices
SampleTest      -- unit test for alpha 123 filters using recorded samples
SlowTest        -- unit test for slow thresholders
Statistics      -- unit test for the statistics
Test            -- scratch test program
ThreeVector     -- unit test for the R3 vectors and matrices
```
 
