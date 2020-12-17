#pragma once

#include "../ffmpeg.h"
#include "VideoStreamInfo.h"
#include "../StandardLibraryIncludes.h"

namespace ffmpegcpp
{
	struct ContainerInfo
	{
		long durationInMicroSeconds;
		float durationInSeconds;
		float start;
		float bitRate;
		const AVInputFormat* format;

		std::vector<VideoStreamInfo> videoStreams;
		// TODO: audio streams!
	};


}