#pragma once
#include "Types.h"
#include "ffmpeg.h"
#include <string>
namespace ffmpegcpp{
    // Convert to the MediaType from the internal AVMediaType
    MediaType toMediaType(AVMediaType type);
    AVMediaType toAVMediaType(MediaType type);
    std::string toString(MediaType type);
}// ffmpegcpp