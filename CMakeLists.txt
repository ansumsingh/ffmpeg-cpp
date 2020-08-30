cmake_minimum_required(VERSION 3.5)
project(ffmpeg-cpp)

find_package(FFMPEG REQUIRED)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE ffmpeg-cpp-sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(FFMPEG_CPP_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(ffmpeg-cpp ${ffmpeg-cpp-sources})
target_link_libraries(ffmpeg-cpp PUBLIC ${FFMPEG_LIBRARIES})
target_include_directories(ffmpeg-cpp PUBLIC ${FFMPEG_INCLUDE_DIRS} ${FFMPEG_CPP_INCLUDE})

option(BUILD_EXAMPLES "Build example projects." FALSE)

function(add_example)
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs)
    cmake_parse_arguments(AE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    add_executable(${AE_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/examples/${AE_NAME}.cpp)
    target_link_libraries(${AE_NAME} ffmpeg-cpp)
endfunction()

if(BUILD_EXAMPLES)
    add_example(NAME decode_audio)
    add_example(NAME decode_video)
    add_example(NAME difference)
    add_example(NAME encode_audio)
    add_example(NAME encode_video)
    add_example(NAME filtering_audio)
    add_example(NAME filtering_video)
    add_example(NAME print_info)
    add_example(NAME remuxing)
    file(GLOB_RECURSE demo-sources ${CMAKE_CURRENT_SOURCE_DIR}/examples/demo/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/examples/demo/*.h)
    add_executable(demo ${demo-sources})
    target_link_libraries(demo ffmpeg-cpp)
endif()
