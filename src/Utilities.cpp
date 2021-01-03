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

std::string ffmpegcpp::toString(MediaType type){
    switch(type){
        case MediaType::AUDIO:
            return "AUDIO";
        case MediaType::VIDEO:
            return "VIDEO";
        case MediaType::SUBTITLE:
            return "SUBTITLE";
        case MediaType::DATA:
            return "DATA";
        case MediaType::NB:
            return "NB";
        case MediaType::UNKNOWN:
        default:
            return "UNKNOWN";
    }
}

AVMediaType ffmpegcpp::toAVMediaType(MediaType type){
    switch(type){
        case MediaType::AUDIO:
            return AVMediaType::AVMEDIA_TYPE_AUDIO;
        case MediaType::VIDEO:
            return AVMediaType::AVMEDIA_TYPE_VIDEO;
        case MediaType::SUBTITLE:
            return AVMediaType::AVMEDIA_TYPE_SUBTITLE;
        case MediaType::DATA:
            return AVMediaType::AVMEDIA_TYPE_DATA;
        case MediaType::NB:
            return AVMediaType::AVMEDIA_TYPE_NB;
        case MediaType::UNKNOWN:
        default:
            return AVMediaType::AVMEDIA_TYPE_UNKNOWN;
    }
}