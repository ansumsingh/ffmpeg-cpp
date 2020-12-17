#include "common.hpp"
#include "ffmpeg.h"
#include <catch2/catch.hpp>

namespace{
    auto dummyAvFrame = []()->AVFrame* {
		auto frame = av_frame_alloc();
		frame->width = ffmpegcpp::unittests::commonWidth;
		frame->height = ffmpegcpp::unittests::commonHeight;
		frame->format = AVPixelFormat::AV_PIX_FMT_BGR4;
		REQUIRE(av_frame_get_buffer(frame, 0) == 0);

		return frame;
	};
}

namespace ffmpeg::unittests{

TEST_CASE("AVframe")
{
    auto frame = dummyAvFrame();
    auto frame2 = av_frame_alloc();
    av_frame_ref(frame2, frame);

	auto frame3 = av_frame_clone(frame);
	av_frame_unref(frame);
	av_frame_free(&frame);
	av_frame_free(&frame2);
	av_frame_free(&frame3);

	REQUIRE_FALSE(frame);
	REQUIRE_FALSE(frame2);
	REQUIRE_FALSE(frame3);
}
} // ffmpeg::unittests