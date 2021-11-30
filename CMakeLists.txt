cmake_minimum_required (VERSION 3.8)

set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/MyOverrides.cmake")
include(MyPrecompiledHeader.cmake)
include(MyCodeMacros.cmake)
include(MyPostBuild.cmake)
include(MyGlobalImports.cmake)
include(MyLocalImports.cmake)

project ("Dev_DspLib")
my_init_global_import_variables()
my_init_post_build_variables()

add_subdirectory ("Butterworth")
add_subdirectory ("CalTableTest")
add_subdirectory ("DelayTest")
add_subdirectory ("DspLib")
add_subdirectory ("FileTest")
add_subdirectory ("FreqDetector")
add_subdirectory ("FuzzyBool")
add_subdirectory ("HistoryTest")
add_subdirectory ("RVectorTest")
add_subdirectory ("SlowTest")
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

