#pragma once

#include <cstdint>

namespace RMath {

	static float Lerp(uint32_t a, uint32_t b, float ratio) {
		return static_cast<float>((b - a) * ratio + a);
	}


	static unsigned int To1D(uint32_t x, uint32_t y, unsigned int raster_width) {
		return y * raster_width + x;
	}

	static float Normalize(uint32_t value, float base) {
		return static_cast<float>(value) / base;
	}


}