#include "Frame.h"


ffmpegcpp::Frame::Frame(AVFrame* frame): data_{frame}
{

}

ffmpegcpp::Frame::Frame(const Frame& frame)
{
    data_ = av_frame_alloc();
    av_frame_ref(data_, frame.data_);
}

ffmpegcpp::Frame::Frame(Frame&& frame)
{
    data_ = av_frame_alloc();
    av_frame_move_ref(data_, frame.data_);
}

ffmpegcpp::Frame& ffmpegcpp::Frame::operator=(const Frame& frame)
{
    if (frame.data_ != data_)
    {
        av_frame_unref(data_);
        data_ = av_frame_clone(frame.data_);
        return *this;
    }
}

ffmpegcpp::Frame& ffmpegcpp::Frame::operator=(Frame&& frame)
{
    if (frame.data_ != data_)
    {
        av_frame_unref(data_);
        av_frame_move_ref(data_, frame.data_);
    }

    return *this;
}
