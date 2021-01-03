#pragma once

#include "Rational.h"
#include "ffmpeg.h"

namespace ffmpegcpp
{
	class FrameContainer
	{
	public:

		FrameContainer(AVFrame* frame, const Rational& timeBase);
		~FrameContainer();

		AVFrame* GetFrame();
		Rational GetTimeBase();

	private:

		AVFrame* frame;
		Rational timeBase_;
	};

}

