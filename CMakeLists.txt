cmake_minimum_required (VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(MY_MACRO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zzzMacros")
set(CMAKE_USER_MAKE_RULES_OVERRIDE "${MY_MACRO_DIR}/MyOverrides.cmake")
include("${MY_MACRO_DIR}/MyCodeMacros.cmake")
include("${MY_MACRO_DIR}/MyGlobalImports.cmake")
include("${MY_MACRO_DIR}/MyLocalImports.cmake")
include("${MY_MACRO_DIR}/MyPrecompiledHeader.cmake")
include("${MY_MACRO_DIR}/MySpecial.cmake")


project ("Dev_DspLib")
my_append_compile_flags()
my_show_cmake_vars()


add_subdirectory ("DspLib")
add_subdirectory ("HistoryTest")
return()

add_subdirectory ("DspLib")
add_subdirectory ("SampleTest")
return()

add_subdirectory ("DspLib")
return()

add_subdirectory ("Butterworth")
add_subdirectory ("CalTableTest")
add_subdirectory ("DelayTest")
add_subdirectory ("DspLib")
add_subdirectory ("FileTest")
add_subdirectory ("FreqDetector")
add_subdirectory ("FuzzyBool")
add_subdirectory ("HistoryTest")
add_subdirectory ("RootFinder")
add_subdirectory ("RVectorTest")
#add_subdirectory ("SlowTest")
add_subdirectory ("Statistics")
add_subdirectory ("Test")
add_subdirectory ("ThreeVector")
return()

add_subdirectory ("DspLib")
add_subdirectory ("RootFinder")
return()

add_subdirectory ("DspLib")
return()

add_subdirectory ("DspLib")
add_subdirectory ("HistoryTest")
return()

add_subdirectory ("DspLib")
add_subdirectory ("SlowTest")
return()

