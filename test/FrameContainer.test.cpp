#include "common.hpp"
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

TEST_CASE("FrameContainer()", "[!mayfail]")
{
  REQUIRE_THROWS_AS(ffmpegcpp::FrameContainer(new AVFrame{}, Rational{}), ffmpegcpp::FFmpegException);

  SECTION("Construct without throw")
  {	  
	  auto frame = dummyAvFrame();
	  REQUIRE_NOTHROW(ffmpegcpp::FrameContainer(frame, Rational{}));
  }

  SECTION("~FrameContainer()")
  {	  
	  AVFrame* frame;
	  {
		  auto frameContainer = ffmpegcpp::FrameContainer{dummyAvFrame(), Rational{}};
		  frame = frameContainer.GetFrame();

		  REQUIRE(frame);
	  	  REQUIRE(frame->height == ffmpegcpp::unittests::commonHeight);
	  	  REQUIRE(frame->width == ffmpegcpp::unittests::commonWidth);
	  }
  }
}

TEST_CASE("~FrameContainer()")
{
  REQUIRE_THROWS_AS(ffmpegcpp::FrameContainer(new AVFrame{}, Rational{}), ffmpegcpp::FFmpegException);

  SECTION("Construct without throw")
  {	  
	  auto frame = dummyAvFrame();
	  REQUIRE_NOTHROW(ffmpegcpp::FrameContainer(frame, Rational{}));
  }
}

TEST_CASE("FrameContainer::getFrame()")
{
	auto frame = dummyAvFrame();
	auto frameContainer = ffmpegcpp::FrameContainer{ frame, Rational{} };
	auto avFrame = frameContainer.GetFrame();
	
	REQUIRE(avFrame->width == ffmpegcpp::unittests::commonWidth);
	REQUIRE(avFrame->height == ffmpegcpp::unittests::commonHeight);
	REQUIRE(avFrame->format == AVPixelFormat::AV_PIX_FMT_BGR4);
}

TEST_CASE("FrameContainer::getTimeBase()")
{
	using namespace ffmpegcpp::unittests;

	auto frame = dummyAvFrame();
	auto timeBase = Rational{commonNumerator, commonDenominator};
	auto frameContainer = ffmpegcpp::FrameContainer{frame, timeBase};
	
	REQUIRE(frameContainer.GetTimeBase().numerator() == commonNumerator);
	REQUIRE(frameContainer.GetTimeBase().denominator() == commonDenominator);
}

}//ffmpegcpp::unittests