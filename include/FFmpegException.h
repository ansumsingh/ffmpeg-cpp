#pragma once

#include "ffmpeg.h"

#include "StandardLibraryIncludes.h"

namespace ffmpegcpp
{
	class FFmpegException : public std::exception
	{

	public:

		FFmpegException(const std::string& error);

		FFmpegException(const std::string& error, int returnValue);

		virtual char const* what()
		{
			return errorInfo.data();
		}


	private:

		std::string errorInfo;
	};
}