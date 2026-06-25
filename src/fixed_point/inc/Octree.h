#pragma once

#include "FixedPointTypeDefs.h"
#include <array>

namespace Octree
{
	// Morton index
	uint32 Morton3D_32(uint32 x, uint32 y, uint32 z);
	uint64 Morton3D_64(uint32 x, uint32 y, uint32 z);
	void BitSpacing(uint32& value);
	void BitSpacing(uint64& value);

	// Octree
	class Octree_Class
	{
	// all coordinates are (z,y,x) pairs
	private:
		std::array<float, 3> min_coords;
		float ranges[3];

		void calculate_ratios(const float (&value)[3]);
		void calculate_ranges(const float (&lower_coordinates)[3], const float (&upper_coordinates)[3]);

	public:
		Octree_Class(const float (&lower_coordinates)[3], const float (&upper_coordinates)[3]);
	};
}