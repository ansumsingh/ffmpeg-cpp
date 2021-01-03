#pragma once

#include "../ffmpeg.h"
#include "../StandardLibraryIncludes.h"

#include "VideoFrameSink.h"
#include "VideoFilterInput.h"

namespace ffmpegcpp
{
	class Filter : public FrameSink, public FrameWriter
	{

	public:

		Filter(const char* filterString, FrameSink* target);
		virtual ~Filter();

		FrameSinkStream* CreateStream();

		void WriteFrame(int streamIndex, AVFrame* frame, StreamData* metaData);
		void Close(int streamIndex);

		bool IsPrimed();

		virtual MediaType GetMediaType();

	private:

		void CleanUp();

		void ConfigureFilterGraph();
		void DrainInputQueues();
		void PollFilterGraphForFrames();
		void FillArguments(char* args, int argsLength, AVFrame* frame, StreamData* metaData);

		const char* GetBufferName(AVMediaType mediaType);
		const char* GetBufferSinkName(MediaType mediaType);

		std::vector<VideoFilterInput*> inputs;
		std::vector<AVFilterContext*> bufferSources;

		MediaType targetMediaType;
		FrameSinkStream* target;

		const char* filterString;

		AVFilterGraph *filter_graph = nullptr;
		AVFilterContext *buffersink_ctx = nullptr;
		AVFrame* filt_frame = nullptr;

		bool initialized = false;

		StreamData outputMetaData;
	};


}
