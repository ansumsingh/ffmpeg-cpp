#include "FrameContainer.h"
#include "ffmpeg.h"
#include <catch2/catch.hpp>

TEST_CASE("FrameContainer()")
{
//   REQUIRE_NOTHROW([](){
//   auto container = ffmpegcpp::FrameContainer{new AVFrame, new AVRational};
//   });
  auto container = ffmpegcpp::FrameContainer{new AVFrame, new AVRational};
}