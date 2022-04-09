# CMakeList.txt : CMake project for FinalProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("FinalProject")

add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
# Add source to this project's executable.
add_executable (FinalProject "FinalProject.cpp" "FinalProject.h")
target_include_directories(FinalProject PUBLIC "C:\\Users\\vyom3\\source\\repos\\C++\\FinalProject\\nana\\include")
target_link_directories(FinalProject PUBLIC "C:\\Users\\vyom3\\source\\repos\\C++\\FinalProject\\nana\\build\\bin")
target_link_libraries(FinalProject "nana_v142_Debug_x64")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} /NANA_ENABLE_AUDIO")
add_definitions(-DNANA_ENABLE_AUDIO)
# TODO: Add tests and install targets if needed.
