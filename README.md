# Dev_DspLib
### digital signal processng library, C++, vstudio, cmake windows and linux

This is a library of C++ classes that provides some realtime functionality. Features include:
   1. butterworth and alpha beta gamma causal recursive filters.
   2. signal history buffers with noncausal filtering for smoothing and differentiating
   3. signal generators for history buffers
   4. pulse analysis and generation
   5. signal statistics
   6. legacy R3 vectors and matrices
   7. Miscellaneous utility functions.

This library is written for Windows and Linux in Visual Studio, using the cmake paradigm. The classes are based on Win32 or pthread realtime functions for threads and sockets and such. The library is portable. The details of the provided functionality that are specific to Win32 are contained in a small set of `*_win.cpp` or `*_linux.cpp`files. It is the intention of the library that programs built under Windows can be rebuilt seamlessly under Linux. CMake is used to implement the cross platform functionality.

The solution contains the library project and a set of associated unit test projects.

The current linux version builds on an ASUS TinkerBoard running debian stretch. The only build prerequisite is the gcc build-essentials.
This library depends on RisLib.

## Classes
``` markdown
dspButterworthCo.h                -- butterworth lowpass filter coefficients
dspFilterAlpha.h                  -- alpha, alpha beta, alpha beta gamma tracking causal filters
dspFilterButterworth.h            -- butterworth lowpass causal filter
dspFilterFilters.h                -- some more filters
dspFilterStatistics.h             -- filtered statistics
dspFunctionObject.h               -- function object base class used by root finder
dspHistory.h                      -- signal history buffer, contains time and value pairs
dspHistoryAlphaFilter.h           -- signal history noncausal alpha beta gamma filter for smoothing/derivatives
dspHistoryConverters.h            -- signal history buffer converters
dspHistoryFilterCausal.h          -- signal history causal filter operator
dspHistoryFilterCDiffBase.h       -- signal history noncausal filter central difference method base class
dspHistoryFilterCDiffHolob.h      -- signal history noncausal filter central difference Holobordko method
dspHistoryFilterCDiffIdentity.h   -- signal history noncausal filter central difference Holobordko method
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
dspHistoryGenZero.h               -- signal history generator for a constant zero 
dspHistoryLoopClock.h             -- signal history generator loop clock 
dspHistoryStatistics.h            -- signal history buffer statistics 
dspHistoryTextFile.h              -- signal history buffer text .csv file writer
dspLut.h                          -- look up table classes
dspPdw.h                          -- pulse descriptor word class
dspPdwFreeList.h                  -- free list of pulse descriptor words class
dspPdwSequence.h                  -- sequence of pulse descriptor words class
dspPdwTextFile.h                  -- pulse descriptor word text file writer
dspRootFinder.h                   -- newtwon raphson root finder
dspRootFinderTwo.h                -- newtwon raphson root finder
dspRVector.h                      -- vector on R3
dspSample.h                       -- sample value and time of arrival class
dspSignal.h                       -- legacy signal class
dspStatistics.h                   -- statistics: mean,stddev,min,max
dspStatistics2.h                  -- more statistics
dspTextFile.h                     -- text file writer
dspThreeAxisAngle.h               -- R3 axis angle representation of a rotation
dspThreeMath.h                    -- R3 include file
dspThreeMatrix.h                  -- R3 matrices, euler angles
dspThreeVector.h                  -- R3 vectors
dsp_functions.h                   -- support functions
dsp_math.h                        -- support functions
stdafx.h                          -- used for precompiled header files
```

## Solution Projects
``` markdown
Butterworth     -- unit test for butterworth lowass filter coefficients
DelayTest       -- experiment for loop delay measurements
DspLib          -- digital signal processing library -- this is the library
Files           -- parameters files
FileTest        -- unit test for text file writers
FreqDetector    -- a frequency detector that uses a bandpass filter
HistoryTest     -- unit test and example code for history buffers, filters, and generators
LutTest         -- unit test for look up tables
PulseAnalyzer   -- a pulse analyzer program based on the pdws
PulseGenerator  -- a pulse generator program based on the pdws 
RootFinder      -- unit test for the root finders
RVectorTest     -- unit test for the R3 vectors and matrices
Statistics      -- unit test for the statistics
Test            -- scratch test program
ThreeVector     -- unit test for the R3 vectors and matrices
```
 
