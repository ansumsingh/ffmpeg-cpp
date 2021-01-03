#pragma once

#include "FrameSink.h"

namespace ffmpegcpp
{
	class AudioFrameSink : public FrameSink
	{
	public:

		virtual MediaType GetMediaType()
		{
			return MediaType::AUDIO;
		}

		virtual ~AudioFrameSink() {}
	};
}
