#pragma once

#include <emmintrin.h>
#include <immintrin.h>

namespace scb
{
	union OutputStream
	{
		unsigned long mask[8];
		__m128i sseMask[2];
		__m256i avxMask;
	};
}
