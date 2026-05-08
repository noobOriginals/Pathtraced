cmake_minimum_required(VERSION 3.26.0)
project(Pathtraced VERSION 0.1.0 LANGUAGES C CXX)

set(FullOutputDir "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static-libs")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

set(SrcPath "${CMAKE_SOURCE_DIR}/src/sources")
set(HeaderPath "${CMAKE_SOURCE_DIR}/src/include")
file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "${SrcPath}/*.cpp" "${SrcPath}/*.c")

include_directories(${HeaderPath})

add_executable(${PROJECT_NAME} ${Sources})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(ScenePath "${CMAKE_SOURCE_DIR}/scenes")
set(SceneOutDir "${FullOutputDir}")
if(WIN32)
    set(SceneOutDir "${FullOutputDir}/${CMAKE_BUILD_TYPE}")
endif()

add_custom_target(
    CopyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ScenePath}
    ${SceneOutDir}
    COMMENT "Copying resources to binary output folder"
)
add_dependencies("${PROJECT_NAME}" CopyResources)
