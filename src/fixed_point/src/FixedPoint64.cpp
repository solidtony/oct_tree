#include "FixedPoint64.h"

namespace Octree
{
	// Fixed Decimal 64
	FixedPoint64::FixedPoint64(double value)
	{
		mInteger = double2fixedInt(value);
		mFraction = double2fixedFrac(value);
	}

	fixedInt64 FixedPoint64::double2fixedInt(double value)
	{
		// Calculates the signed integer value of a double value.
		// Largest value 9223372036854774784
		// Largest value without error 2^53 = 9007199254740992
		// (2^53 instead of 2^52 => 52bit mantissa + 1bit assumed leading 1)

		uint64 exponent = *(uint64*)&value;
		uint64 mantissa = *(uint64*)&value;
		uint64 sign = *(uint64*)&value;

		fixedInt64 fixedInt;

		// Sign bit
		sign &= 0x8000000000000000;

		// Exponent bits
		exponent >>= 0x34; // 52 is for the number of mantissa bits.
		exponent &= 0x7FF; // 2047 is to get only the 11 bits of the exponent and ignore the sign bit.

		// Mantissa bits
		mantissa &= 0x000FFFFFFFFFFFFF; // Masks double for the mantissa only.
		mantissa |= 0x0010000000000000; // Sets mantissa leading digit to one.

		if (exponent < 0x434) // Shift right when exponent is less than 1076
		{
			fixedInt = mantissa >> (0x433 - exponent); // >> shift by (1075 - exponent)
		}
		else if (exponent < 0x43E) // Shift left when exponent is between 1076 & 1085
		{
			fixedInt = mantissa << (exponent - 0x433); // << shift by (exponent - 1075)
		}
		else // Sets to largest value
		{
			fixedInt = 0x7FFFFFFFFFFFFFFF;
		}

		// Set sign value
		fixedInt |= sign; // AG need to fix negative values

		return fixedInt;
	}

	fixedFrac64 FixedPoint64::double2fixedFrac(double value)
	{
		// Calculates the signed integer value of a signed double value.

		// Smallest decimal place is 2^-64 ~= 5.42101E-20
		uint64 exponent = *(uint64*)&value;
		uint64 mantissa = *(uint64*)&value;

		fixedFrac64 fixedFrac;

		// Exponnent bits
		exponent >>= 0x34; // 52 is for the number of mantissa bits.
		exponent &= 0x7FF; // 2047 is to get only the 11 bits of the exponent and ignore the sign bit.

		// Mantissa bits
		mantissa &= 0x000FFFFFFFFFFFFF; // Masks double for the mantissa only.
		mantissa |= 0x0010000000000000; // Sets mantissa leading digit to one.

		if (exponent > 0x3F2) // shift left when exponent is greater than 1010
		{
			fixedFrac = mantissa << (exponent - 0x3F3); // << shift by (exponent - 1011)
		}
		else
		{
			fixedFrac = mantissa >> (0x3F3 - exponent); // >> shift by (1011 - exponent) wth exp <= 1010
		}

		return fixedFrac;
	}
}