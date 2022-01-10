#pragma once

#include <cstdint>

namespace RMath {

	static float Lerp(int a, int b, float ratio) {
		return static_cast<float>((b - a) * ratio + a);
	}

	static void GetPixelSpace(float x, float y, uint32_t width, uint32_t height, int*& fill) {
		int pos_x = (x + 1.0f) * (width * 0.5f);
		int pos_y = (1.0f - y) * (height * 0.5f);

		delete fill;

		fill = new int[2]{
			pos_x,
			pos_y
		};

	}


	static unsigned int To1D(uint32_t x, uint32_t y, unsigned int raster_width) {
		return y * raster_width + x;
	}

	static float Normalize(uint32_t value, float base) {
		return static_cast<float>(value) / base;
	}


	/*Vector2 Vector2Lerp(Vector2 a, Vector2 b, float ratio) {

		Vector2 c{ 0 };

		c.X = RMath::Lerp(a.X, b.X, ratio);
		c.Y = RMath::Lerp(a.X, b.X, ratio);

		return c;
	}*/


}