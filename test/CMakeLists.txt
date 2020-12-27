find_package(Catch2 REQUIRED)

add_executable(ffmpegcpp-tests main.cpp FrameContainer.test.cpp Frames.test.cpp Utilities.test.cpp Rational.test.cpp)
include_directories(${FFMPEG_CPP_INCLUDE_DIRS})

target_link_libraries(ffmpegcpp-tests  Catch2::Catch2 ffmpeg-cpp)

add_test(ffmpegcpp-unittests ffmpegcpp-tests -v normal)