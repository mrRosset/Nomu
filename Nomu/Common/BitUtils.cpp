#include "BitUtils.h"

u16 crc16_ccitt(u8(&values)[6])
{
	u32 result = 0;

	for (u8 b : values)
	{
		result ^= (b << 8);

		for (u8 d = 0; d < 8; d++)
		{
			result = result << 1;

			if (result & 0x10000)
			{
				result ^= 0x1021;
			}

			result &= 0xffff;
		}
	}

	return result;
}