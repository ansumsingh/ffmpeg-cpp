#pragma once
#include "ffmpeg.h"
#include <memory>

namespace ffmpegcpp
{
    class Frame
    {
    public:
        Frame(AVFrame *);
        // use av_frame_alloc and av_frame_ref
        Frame(const Frame& other);
        // use av_frame_alloc and av_frame_move
        Frame(Frame&& other);
        // use av_frame_unref and av_frame_clone
        Frame& operator=(const Frame& other);
        // use av_frame_unref and av_frame_move
        Frame& operator=(Frame&& other);
        // av_frame_unref
        ~Frame();
    private:
        AVFrame* data_;
    };

}; // namespace ffmpegcpp