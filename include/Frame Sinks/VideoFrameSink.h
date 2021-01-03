#pragma once

#include "FrameSink.h"

namespace ffmpegcpp
{
	class VideoFrameSink : public FrameSink
	{
	public:

		virtual MediaType GetMediaType()
		{
			return MediaType::VIDEO;
		}

		virtual ~VideoFrameSink() {}
	};
}
