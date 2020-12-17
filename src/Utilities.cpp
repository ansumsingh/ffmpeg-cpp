#include "Utilities.h"

ffmpegcpp::MediaType ffmpegcpp::toMediaType(AVMediaType type){
    switch(type){
        case AVMediaType::AVMEDIA_TYPE_AUDIO:
            return MediaType::AUDIO;
        case AVMediaType::AVMEDIA_TYPE_VIDEO:
            return MediaType::VIDEO;
        case AVMediaType::AVMEDIA_TYPE_SUBTITLE:
            return MediaType::SUBTITLE;
        case AVMediaType::AVMEDIA_TYPE_DATA:
            return MediaType::DATA;
        case AVMediaType::AVMEDIA_TYPE_NB:
            return MediaType::NB;
        case AVMediaType::AVMEDIA_TYPE_UNKNOWN:
        default:
            return MediaType::UNKNOWN;
    }
}