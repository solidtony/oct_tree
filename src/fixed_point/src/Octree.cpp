#include "Octree.h" 

////////////////////////////////////////////////////////////////////////
// start: Morton Indexing

// AG
// Morton Indexing
//uint32 Octree::Morton3D(uint32 x, uint32 y, uint32 z)
//{
//	uint32 morton_index = 0x0;
//	uint32 mask = 0x80000000;
//
//	x >>= 0x2;
//	y >>= 0x1;
//
//	while (mask > 0) // z is initially un-shifted.
//	{
//		morton_index |= mask & z;
//		mask >>= 0x1;
//		morton_index |= mask & y;
//		mask >>= 0x1;
//		morton_index |= mask & x;
//		mask >>= 0x1;
//
//		z >>= 0x2;
//		y >>= 0x2;
//		x >>= 0x2;
//	}
//
//	return morton_index;
//}

// Morton indexing
uint32 Octree::Morton3D_32(uint32 x, uint32 y, uint32 z)
{
	// 32 bit
	Octree::BitSpacing(z);
	Octree::BitSpacing(y);
	Octree::BitSpacing(x);
	z |= (y >> 0x1) | (x >> 0x2);

	return z;
}

uint64 Octree::Morton3D_64(uint32 x, uint32 y, uint32 z)
{
	uint64 z64 = *(uint64*)&z << 0x20;
	uint64 y64 = *(uint64*)&y << 0x20;
	uint64 x64 = *(uint64*)&x << 0x20;

	// 64 bit
	Octree::BitSpacing(z64);
	Octree::BitSpacing(y64);
	Octree::BitSpacing(x64);
	z64 |=  (y64 >> 0x1) | (x64 >> 0x2);

	return z64;
}

// Bit spacing for morton indexing interleaving
void Octree::BitSpacing(uint32& value)
{
	value &= 0xFFC00000;
	// initial: c123 4567 8900 0000 0000 0000 0000 0000
    // after 1: c123 4500 0000 0067 8900 0000 0000 0000
	// after 2: c100 0023 4500 0000 0067 8900 0000 0000
	// after 3: c100 0023 0000 4500 0067 0000 8900 0000
	// after 4: c001 0020 0300 4005 0060 0700 8009 0000

	value = (value | (value >> 0x8)) & 0xFC03C000;
	value = (value | (value >> 0x4)) & 0xC3C03C00;
	value = (value | (value >> 0x4)) & 0xC30C30C0;
	value = (value | (value >> 0x2)) & 0x92492490;
}

void Octree::BitSpacing(uint64& value)
{
	value &= 0xFFFFF80000000000;
	// initial: abcd efgh ijkl mnop qrst u000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
	// after 1: abcd efgh ij00 0000 0000 0000 0000 00kl mnop qrst u000 0000 0000 0000 0000 0000
	// after 2: abcd ef00 0000 00gh ij00 0000 0000 00kl mnop 0000 0000 qrst u000 0000 0000 0000
	// after 3: ab00 00cd ef00 0000 00gh ij00 0000 00kl 0000 mnop 0000 0000 qrst u000 0000 0000
	// after 4: ab00 00cd 0000 ef00 00gh 0000 ij00 00kl 0000 mn00 00op 0000 qr00 00st u000 0000
	// after 5: a00b 00c0 0d00 e00f 00g0 0h00 i00j 00k0 0l00 m00n 00o0 0p00 q00r 00s0 0tu0 0000
	// after 6: a00b 00c0 0d00 e00f 00g0 0h00 i00j 00k0 0l00 m00n 00o0 0p00 q00r 00s0 0t00 u000

	value = (value | (value >> 0x14)) & 0xFFC00003FF800000;
	value = (value | (value >> 0x08)) & 0xFC03C003F00F8000;
	value = (value | (value >> 0x04)) & 0xC3C03C030F00F800;
	value = (value | (value >> 0x04)) & 0xC30C30C30C30C380;
	value = (value | (value >> 0x02)) & 0x9249249249249260;
	value = (value | (value >> 0x02)) & 0x9249249249249248;
}
// end: Morton Indexing
////////////////////////////////////////////////////////////////////////

// Unused functions, but may come in handy.

uint32 ReverseBits(uint32 input)
{
	uint32 output = input;
	for (int i = sizeof(input) * 8 - 1; i; --i)
	{
		output <<= 1;
		input >>= 1;
		output |= input & 1;
	}
	return output;
}

// Most significant bit.
int uint32_MSBindex(int input)
{
	int msbIndex = 0;

	while (input)
	{
		input >>= 1;
		++msbIndex;
	}
	return msbIndex;
}

Octree::Octree_Class::Octree_Class(const float (&lower_coordinates)[3], const float (&upper_coordinates)[3])
{
	min_coords[0] = lower_coordinates[0];
}

