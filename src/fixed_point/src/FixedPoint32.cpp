#include "FixedPoint32.h"

namespace Octree
{
	// Fixed Decimal 32
	FixedPoint32::FixedPoint32(float value)
	{
		mInteger = float2fixedInt(value);
		mFraction = float2fixedFrac(value);
	}

	fixedInt32 FixedPoint32::float2fixedInt(float value)
	{
		// Calculates the signed integer value of a signed float value.
		// Lowest value is 0
		// Largest value without error = 16777216
		// Largest value = 4294967295

		uint32 exponent = *(uint32*)&value;
		uint32 mantissa = *(uint32*)&value;

		fixedInt32 fixedInt;

		// Exponent bits
		exponent >>= 0x17; // 23 is for the number of mantissa bits.
		exponent &= 0xFF; // 255 is to get only the 8bits of the exponent and ignoring the sign bit.

		// Mantissa bits
		mantissa &= 0x7FFFFF; // Masks mantissa of float.
		mantissa |= 0x800000; // places the missing one from mantissa.

		if (exponent < 0x97) // Shift right when exponent is less than 150
			fixedInt = mantissa >> (0x96 - exponent); // >> shift by (150 - exponent)
		else if (exponent < 0x9F) // << shift when exponent is between 152 & 158
			fixedInt = mantissa << (exponent - 0x96); // << shift by (exponent - 150)
		else // Sets to largest value
			fixedInt = 0xFFFFFFFF;

		return fixedInt;
	}

	fixedFrac32 FixedPoint32::float2fixedFrac(float value)
	{
		// Calculates the decimal value in fixed point standard of a float.
		// Smallest value is 2^-32 = 2.3283064365386962890625E-10
		// Largest value is 0.99999994

		uint32 exponent = *(uint32*)&value;
		uint32 mantissa = *(uint32*)&value;

		fixedFrac32 fixedFrac;

		// Exponent bits
		exponent >>= 0x17; // 23 is for the number of mantissa bits.
		exponent &= 0xFF; // 255 is to get only the 8bits of the exponent and ignoring the sign bit.

		// Mantissa manipulation
		mantissa &= 0x7FFFFF; // Masks mantissa of float.
		mantissa |= 0x800000; // places the missing one from mantissa.

		if (exponent > 0x75) { fixedFrac = mantissa << (exponent - 0x76); } // << shift by (exponent - 118) when exp > 117
		else { fixedFrac = mantissa >> (0x76 - exponent); }

		return fixedFrac;
	}
}