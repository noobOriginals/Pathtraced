cmake_minimum_required(VERSION 3.20)
project(Pathtraced VERSION 0.1.0 LANGUAGES C CXX)

set(FullOutputDir "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/Static Lbraries")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

set(SrcPath "${CMAKE_SOURCE_DIR}")
set(HeaderPath "${CMAKE_SOURCE_DIR}")
file(GLOB Sources CONFIGURE_DEPENDS "${SrcPath}/*.cpp" "${SrcPath}/*.c" "${HeaderPath}/*.hpp" "${HeaderPath}/*.h")

add_executable("${PROJECT_NAME}" ${Sources})
target_compile_features("${PROJECT_NAME}" PUBLIC cxx_std_17)
