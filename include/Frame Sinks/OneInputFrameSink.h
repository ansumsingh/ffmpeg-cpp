#pragma once

#include "../ffmpeg.h"

#include "FrameWriter.h"
#include "FrameSink.h"


namespace ffmpegcpp
{
	class OneInputFrameSink : public FrameSink
	{
	public:

		OneInputFrameSink(FrameWriter* writer, MediaType mediaType);
		~OneInputFrameSink();

		virtual MediaType GetMediaType();

		FrameSinkStream* CreateStream();


	private:

		int nStreamsGenerated = 0;

		FrameWriter* writer;

		FrameSinkStream* stream = nullptr;

		MediaType mediaType;
	};
}

