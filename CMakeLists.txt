cmake_minimum_required (VERSION 3.8)

include(MyCMake.cmake)

project ("Dev_DspLib")
my_init_variables()

add_subdirectory ("DspLib")
return()

#add_subdirectory ("Butterworth")
#add_subdirectory ("DelayTest")
#add_subdirectory ("DspLib")
#add_subdirectory ("FileTest")
#add_subdirectory ("FreqDetector")
#add_subdirectory ("HistoryTest")
#add_subdirectory ("LutTest")
#add_subdirectory ("PulseAnalyzer")
#add_subdirectory ("PulseGenerator")
#add_subdirectory ("RootFinder")
#add_subdirectory ("RVectorTest")
#add_subdirectory ("Statistics")
#add_subdirectory ("Test")
#add_subdirectory ("ThreeVector")

