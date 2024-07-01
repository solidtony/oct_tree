#pragma once

#include "FixedPointTypeDefs.h"

namespace Octree
{
	class FixedPoint64
	{
		// Stores a double as a fixed point 64 bits for the integer and 64 bits for the fraction
	public:
		FixedPoint64(double value);
		fixedInt64 getInteger() { return mInteger; }
		fixedFrac64 getFraction() { return mFraction; }

	private:
		fixedInt64 mInteger;
		fixedFrac64 mFraction;

		// 64 bits
		fixedInt64 double2fixedInt(double value);
		fixedFrac64 double2fixedFrac(double value);
	};
}