#include "FrameContainer.h"
#include "FFmpegException.h"
#include <catch2/catch.hpp>

namespace {
	auto dummyAvFrame = []() {
		auto frame = av_frame_alloc();
		frame->width = 1092;
		frame->height = 1080;
		frame->format = AVPixelFormat::AV_PIX_FMT_BGR4;
		REQUIRE(av_frame_get_buffer(frame, 0) == 0);

		return frame;
	};
}

namespace ffmpegcpp::unittests {

TEST_CASE("FrameContainer()")
{
  REQUIRE_THROWS_AS(ffmpegcpp::FrameContainer(new AVFrame{}, new AVRational{}), ffmpegcpp::FFmpegException);

  SECTION("Construct without throw")
  {	  
	  auto frame = dummyAvFrame();
	  REQUIRE_NOTHROW(ffmpegcpp::FrameContainer(frame, new AVRational{}));
  }

  SECTION("~FrameContainer()")
  {	  
	  AVFrame* frame;
	  {
		  auto frameContainer = ffmpegcpp::FrameContainer{dummyAvFrame(), new AVRational{}};
		  frame = frameContainer.GetFrame();
		  REQUIRE(frame);
	  }
	  REQUIRE(frame->height == 1080);
  }
}

TEST_CASE("~FrameContainer()")
{
  REQUIRE_THROWS_AS(ffmpegcpp::FrameContainer(new AVFrame{}, new AVRational{}), ffmpegcpp::FFmpegException);

  SECTION("Construct without throw")
  {	  
	  auto frame = dummyAvFrame();
	  REQUIRE_NOTHROW(ffmpegcpp::FrameContainer(frame, new AVRational{}));
  }
}

TEST_CASE("FrameContainer::getFrame()")
{
	auto frame = dummyAvFrame();
	auto frameContainer = ffmpegcpp::FrameContainer{ frame, new AVRational{} };
	auto avFrame = frameContainer.GetFrame();
	
	REQUIRE(avFrame->width == 1092);
	REQUIRE(avFrame->height == 1080);
	REQUIRE(avFrame->format == AVPixelFormat::AV_PIX_FMT_BGR4);
}

}//ffmpegcpp::unittests