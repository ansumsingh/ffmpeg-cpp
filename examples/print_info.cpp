
#include <iostream>

#include <ffmpegcpp.h>

using namespace ffmpegcpp;

int main()
{
	// This example will print info about a video.
	try
	{

		// Load a video from a container and read its info.
		const char* fileName = "samples/big_buck_bunny.mp4";
		Demuxer* demuxer = new Demuxer(fileName);
		ContainerInfo info = demuxer->GetInfo();

		// Print the data similar to ffmpeg.exe.
		std::cout << "Input " << info.format->name << " from '" << fileName << "'" << std::endl;
		std::cout << "Video streams:" << std::endl;
		for (int i = 0; i < info.videoStreams.size(); ++i)
		{
			VideoStreamInfo stream = info.videoStreams[i];
			std::cout << "Stream #" << (i + 1)
				<< ": codec " << stream.codec->name
				<< ", pixel format " << stream.formatName
				<< ", resolution " << stream.width << "x" << stream.height
				<< ", bit rate " << stream.bitRate << "kb/s"
				<< ", fps " << stream.frameRate.toDouble()
				<< ", time base " << stream.timeBase.numerator()  << "/" << stream.timeBase.denominator()
				<< ", " << demuxer->GetFrameCount(stream.id) << " frames"
				<< std::endl;
		}

	std::cout << "Encoding complete!" << std::endl;
	std::cout << "Press any key to continue..." << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception caught!" << std::endl;
		std::cout << e.what() << std::endl;
	}


	return 0;
}
