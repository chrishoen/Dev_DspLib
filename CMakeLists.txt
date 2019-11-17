cmake_minimum_required (VERSION 3.8)

set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/MyOverrides.cmake")
include(MyPrecompiledHeader.cmake)
include(MyCodeMacros.cmake)
include(MyGlobalImports.cmake)
include(MyLocalImports.cmake)

project ("Dev_DspLib")
my_init_global_import_variables()

add_subdirectory ("DspLib")
return()

add_subdirectory ("DspLib")
add_subdirectory ("SlowTest")
add_subdirectory ("FuzzyBool")
return()

add_subdirectory ("DelayTest")
add_subdirectory ("DspLib")
add_subdirectory ("FileTest")
add_subdirectory ("FreqDetector")
add_subdirectory ("HistoryTest")
add_subdirectory ("LutTest")
add_subdirectory ("PulseAnalyzer")
add_subdirectory ("PulseGenerator")
add_subdirectory ("RootFinder")
add_subdirectory ("RVectorTest")
add_subdirectory ("Statistics")
add_subdirectory ("Test")
add_subdirectory ("ThreeVector")

return()

add_subdirectory ("DspLib")
add_subdirectory ("HistoryTest")
return()

