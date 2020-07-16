#pragma once


namespace util
{
	inline bool inRange (int index, size_t size)
	{
		return ((index >= 0) and (index < size));
	}
}