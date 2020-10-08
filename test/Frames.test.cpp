#include <catch2/catch.hpp>
#include "ffmpeg.h"

TEST_CASE("AVframe")
{
    auto dummyAvFrame = []()->AVFrame* {
		auto frame = av_frame_alloc();
		frame->width = 1092;
		frame->height = 1080;
		frame->format = AVPixelFormat::AV_PIX_FMT_BGR4;
		REQUIRE(av_frame_get_buffer(frame, 0) == 0);

		return frame;
	};
    auto frame = dummyAvFrame();
    auto frame2 = av_frame_alloc();
    av_frame_ref(frame2, frame);

	auto frame3 = av_frame_clone(frame);
	av_frame_unref(frame);
	av_frame_free(&frame2);
	av_frame_free(&frame3);
}