#include "Utilities.h"

#include <catch2/catch.hpp>

namespace ffmpegcpp::unittests{
    TEST_CASE("toMediaType()"){
        auto [input, expected] = GENERATE(
            std::pair{AVMediaType::AVMEDIA_TYPE_UNKNOWN, MediaType::UNKNOWN},
            std::pair{AVMediaType::AVMEDIA_TYPE_DATA, MediaType::DATA},
            std::pair{AVMediaType::AVMEDIA_TYPE_AUDIO, MediaType::AUDIO},
            std::pair{AVMediaType::AVMEDIA_TYPE_VIDEO, MediaType::VIDEO},
            std::pair{AVMediaType::AVMEDIA_TYPE_SUBTITLE, MediaType::SUBTITLE},
            std::pair{AVMediaType::AVMEDIA_TYPE_NB, MediaType::NB}
            );
        
        REQUIRE(ffmpegcpp::toMediaType(input) == expected);
        REQUIRE(ffmpegcpp::toMediaType(static_cast<AVMediaType>(100)) == MediaType::UNKNOWN);
    }

    TEST_CASE("toAVMediaType()"){
        auto [expected, input] = GENERATE(
            std::pair{AVMediaType::AVMEDIA_TYPE_UNKNOWN, MediaType::UNKNOWN},
            std::pair{AVMediaType::AVMEDIA_TYPE_DATA, MediaType::DATA},
            std::pair{AVMediaType::AVMEDIA_TYPE_AUDIO, MediaType::AUDIO},
            std::pair{AVMediaType::AVMEDIA_TYPE_VIDEO, MediaType::VIDEO},
            std::pair{AVMediaType::AVMEDIA_TYPE_SUBTITLE, MediaType::SUBTITLE},
            std::pair{AVMediaType::AVMEDIA_TYPE_NB, MediaType::NB}
            );
        
        REQUIRE(ffmpegcpp::toAVMediaType(input) == expected);
        REQUIRE(ffmpegcpp::toAVMediaType(static_cast<MediaType>(100)) == AVMediaType::AVMEDIA_TYPE_UNKNOWN);
    }
}