#pragma once
#include "Types.h"
#include "ffmpeg.h"

namespace ffmpegcpp{
    // Convert to the MediaType from the internal AVMediaType
    MediaType toMediaType(AVMediaType type);
}// ffmpegcpp