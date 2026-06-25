#pragma once

#include "FixedPointTypeDefs.h"

namespace Octree
{
	class FixedPoint32
	{
		// Stores a float as a fixed point 32 bits for the integer and 32 bits for the fraction
	public:
		FixedPoint32(float value);
		fixedInt32 getInteger() { return mInteger; }
		fixedFrac32 getFraction() { return mFraction; }

	private:
		fixedInt32 mInteger;
		fixedFrac32 mFraction;

		fixedInt32 float2fixedInt(float value);
		fixedFrac32 float2fixedFrac(float value);
	};
}