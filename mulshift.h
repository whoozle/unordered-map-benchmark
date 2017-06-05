#pragma once

#include <stdint.h>

//The state of the art for hashing integers is the multiply-shift scheme described by Dietzfelbinger et al. in 1997.
//https://en.wikipedia.org/wiki/Universal_hashing#Avoiding_modular_arithmetic

template<typename T>
struct mul_shift_hash
{
	static constexpr size_t Bits = 8 * sizeof(size_t) / 2;
	static constexpr size_t Mask = (size_t(1) << Bits) - 1;
	static constexpr size_t A0	= 1818545041;	//some random value (rolled myself)
	static constexpr size_t A	= 1103515245;	//random value from GCC random
	static constexpr size_t B	= 12343;		//random value from GCC random, rounded to nearest prime

	size_t operator() (const T &value) const
	{
		size_t r = A0;
		size_t n = value.size();
		auto data = value.data();
		for(size_t a = A; n--; ++a) {
			auto ch = *data++;
			r += a * ch + B;
		}
		return r & Mask;
	}
};
