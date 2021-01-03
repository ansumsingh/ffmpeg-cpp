#pragma once

#include "Rational.h"
#include "Types.h"

namespace ffmpegcpp
{
	struct StreamData
	{
		MediaType type;

		Rational timeBase;
		Rational frameRate;
	};
}