#include "FFmpegException.h"

using namespace std;

namespace ffmpegcpp
{
	FFmpegException::FFmpegException(const string& error) : errorInfo{error}
	{
	}

	FFmpegException::FFmpegException(const string& error, int returnValue): errorInfo{error}
	{
	}
}