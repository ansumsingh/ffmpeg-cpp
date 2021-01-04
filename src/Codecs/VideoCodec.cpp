#include <limits>
#include "VideoCodec.h"
#include "../FFmpegException.h"

using namespace std;

namespace ffmpegcpp
{
	VideoCodec::VideoCodec(const char* codecName)
		: Codec(codecName)
	{
	}

	VideoCodec::VideoCodec(AVCodecID codecId)
		: Codec(codecId)
	{
	}

	VideoCodec::~VideoCodec()
	{
	}

	void VideoCodec::SetQualityScale(int qscale)
	{

		codecContext->flags |= AV_CODEC_FLAG_QSCALE;
		codecContext->global_quality = FF_QP2LAMBDA * 0;
	}

	bool VideoCodec::IsPixelFormatSupported(AVPixelFormat format)
	{
		if (format == AV_PIX_FMT_NONE) return true; // let the codec deal with this
		const enum AVPixelFormat *p = codecContext->codec->pix_fmts;
		while (*p != AV_PIX_FMT_NONE)
		{
			if (*p == format) return true;
			p++;
		}
		return false;
	}

	bool VideoCodec::IsFrameRateSupported(const Rational& frameRate)
	{
		if (!codecContext->codec->supported_framerates) return true; // all frame rates are fair game
		const AVRational *p = codecContext->codec->supported_framerates;
		while (p->num)
		{
			if (Rational{*p} == frameRate) return true;
			p++;
		}
		return false;
	}

	OpenCodec* VideoCodec::Open(int width, int height, const Rational& frameRate, AVPixelFormat format)
	{

		// sanity checks
		if (!IsPixelFormatSupported(format)) throw FFmpegException("Pixel format " + string(av_get_pix_fmt_name(format)) + " is not supported by codec " + codecContext->codec->name);
		if (!IsFrameRateSupported(frameRate)) throw FFmpegException("Frame rate " + to_string(frameRate.numerator()) + "/" + to_string(frameRate.denominator()) + " is not supported by codec " + codecContext->codec->name);

		// if the codec is not an audio codec, we are doing it wrong!
		if (codecContext->codec->type != AVMEDIA_TYPE_VIDEO) throw FFmpegException("A video output stream must be initialized with a video codec");

		// set everything & open
		codecContext->width = width;
		codecContext->height = height;
		codecContext->pix_fmt = format;

		// FPS
		AVRational time_base;
		time_base.num = frameRate.denominator();
		time_base.den = frameRate.numerator();
		codecContext->time_base = time_base;
		AVRational framerate;
		framerate.num = frameRate.numerator();
		framerate.den = frameRate.denominator();
		codecContext->framerate = framerate;

		return Codec::Open();
	}

	AVPixelFormat VideoCodec::GetDefaultPixelFormat()
	{
		const enum AVPixelFormat *p = codecContext->codec->pix_fmts;
		if (*p == AV_PIX_FMT_NONE) throw FFmpegException("Codec " + string(codecContext->codec->name) + " does not have a default pixel format, you have to specify one");
		return *p;
	}

	Rational VideoCodec::GetClosestSupportedFrameRate(const Rational& originalFrameRate)
	{
		if (!codecContext->codec->supported_framerates)
		{
			// make up a frame rate - there is no supported frame rate
			return originalFrameRate;
		};

		const AVRational *p = codecContext->codec->supported_framerates;
		AVRational bestFrameRate;
		bestFrameRate.num = 0;
		bestFrameRate.den = 1;
		double bestDiff = std::numeric_limits<double>::max();
		double fVal = originalFrameRate.toDouble();
		while (p->num)
		{
			double pVal = av_q2d(*p);
			double diff = fabs(pVal - fVal);
			if (diff < bestDiff)
			{
				bestDiff = diff;
				bestFrameRate.num = p->num;
				bestFrameRate.den = p->den;
			}
			p++;
		}

		// There were no valid frame rates in the list... this should never happen unless ffmpeg screws up.
		if (bestFrameRate.num == 0) return originalFrameRate;

		return bestFrameRate;
	}
}
