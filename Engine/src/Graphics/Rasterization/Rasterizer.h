#pragma once
#include "pch.h"

#include "Surface.h"
#include "RMath.h"

namespace Graphics {

	struct Vector2 { uint32_t X; uint32_t Y; };

	/*Vector2 Vector2Lerp(Vector2 a, Vector2 b, float ratio) {

		Vector2 c{ 0 };

		c.X = RMath::Lerp(a.X, b.X, ratio);
		c.Y = RMath::Lerp(a.X, b.X, ratio);

		return c;
	}*/

#define COLOR_BUFFER_BIT 0xFF


	class Rasterizer
	{
	public:
		Rasterizer() : _frames{ nullptr }, _frame_ptr{ nullptr }, _frame_index{ 0 }, _frame_width{ 0 }, _frame_height{ 0 }, _frame_size{ 0 }, _frame_count{0} {}
		~Rasterizer() {}

		bool Init(uint32_t _width, uint32_t _height, uint32_t _buffer_count = 2);
		bool Shutdown();
		
		bool CreateSurface(uint32_t _screenWidth, uint32_t _screenHeight);
		bool SwapBuffers();
		
		void Clear(uint32_t _bits);

		void ClearColor(uint32_t clearColor);

		void DrawLine(Vector2 pointA, Vector2 pointB, uint32_t color);
		void DrawPoint(Vector2 point, uint32_t color);



	private:
		uint32_t _bufferBits;
		uint32_t _clearColor;

		uint32_t** _frames;		// all buffers
		uint32_t* _frame_ptr;
		uint32_t _frame_index;
		uint32_t _frame_count;		

		uint32_t _frame_height;
		uint32_t _frame_width;
		uint32_t _frame_size;



	};

}

