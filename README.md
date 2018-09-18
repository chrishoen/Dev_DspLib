# Dev_DspLib
### digital signal processng library, C++, vstudio, windows

This is a library of C++ classes that provides some realtime functionality. Features include:
   1. Thread base classes.
   8. Miscellaneous utility functions.

This library is written for Windows in Visual Studio. The classes are based on Win32 realtime functions for threads and sockets and such. The library is portable. The details of the provided functionality that are specific to Win32 are contained in a small set of `*_win.cpp` files. There is a corresponding library for Linux, RisLibLx, with a corresponding small set of `*_linux.cpp` files that are specific to Linux. It is the intention of the library that programs built under Windows can be rebuilt seamlessly under Linux.

## Classes
``` markdown
dspButterworthCo.h                 -- butterworth lowpass filter coefficients
dspFilterAlpha.h
dspFilterButterworth.h
dspFilterFilters.h
dspFilterStatistics.h
dspFunctionObject.h
dspHistory.h
dspHistoryAlphaFilter.h
dspHistoryConverters.h
dspHistoryFilterCausal.h
dspHistoryFilterCDiffBase.h
dspHistoryFilterCDiffHolob.h
dspHistoryFilterCDiffIdentity.h
dspHistoryFilterCDiffSavGol.h
dspHistoryFilterNoncausal.h
dspHistoryFilterOperator.h
dspHistoryFilterParms.h
dspHistoryGaussNoise.h
dspHistoryGenBase.h
dspHistoryGenerator.h
dspHistoryGenParms.h
dspHistoryGenRandWave.h
dspHistoryGenSinWave.h
dspHistoryGenStep.h
dspHistoryGenZero.h
dspHistoryLoopClock.h
dspHistoryStatistics.h
dspHistoryTextFile.h
dspLut.h
dspPdw.h
dspPdwFreeList.h
dspPdwSequence.h
dspPdwTextFile.h
dspRootFinder.h
dspRootFinderTwo.h
dspRVector.h
dspSample.h
dspSignal.h
dspStatistics.h
dspStatistics2.h
dspTextFile.h
dspThreeAxisAngle.h
dspThreeMath.h
dspThreeMatrix.h
dspThreeVector.h
dsp_functions.h
dsp_math.h
stdafx.h                      -- used for precompiled header files
```

## Solution Projects
``` markdown
Butterworth     -- unit test for butterworth lowass filter coefficients
DelayTest
DspLib
Files
FileTest
FreqDetector
HistoryTest
LutTest
PulseAnalyzer
PulseGenerator
RootFinder
RVectorTest
Statistics
Test
ThreeVector
```
 
