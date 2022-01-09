#include "Rasterizer.h"

namespace Graphics {


	bool Rasterizer::Init(uint32_t _width, uint32_t _height, uint32_t _buffer_count)
	{
		_frame_size = _width * _height;
		_frame_count = _buffer_count;
		
		_frames = new uint32_t*[_buffer_count];

		for (size_t i = 0; i < _buffer_count; i++)
		{
			_frames[i] = new uint32_t[_width * _height];
		}


		CreateSurface(_width, _height);

		return false;
	}
	bool Rasterizer::Shutdown()
	{
		if (!ShutdownSurface()) {
			return false;
		}

		return true;

	}

	bool Rasterizer::SwapBuffers()
	{

		Clear(COLOR_BUFFER_BIT);
		ClearColor(0xFF161616);

		DrawPoint({ 10, 10 }, 0xFFFFFFFF);
	
		// need to find a way to move this exit condition out of here...

		bool res = UpdateSurface(_frames[_frame_index], _frame_size);

		_frame_index++;
		_frame_index %= _frame_count;

		return res;
	}

	void  Rasterizer::DrawPoint(Vector2 point, uint32_t color) {
		_frames[_frame_index][RMath::To1D(point.X, point.Y, _frame_width)] = color;
	}

	void Rasterizer::Clear(uint32_t _bits) {
		
		if (_bits & COLOR_BUFFER_BIT) {
			for (uint32_t i = 0; i < _frame_size; i++)
			{
				_frames[_frame_index][i] = _clearColor;
			}
		}

	}

	void Rasterizer::ClearColor(uint32_t clearColor) {
		_clearColor = clearColor;
	}



	bool Rasterizer::CreateSurface(uint32_t _screenWidth, uint32_t _screenHeight)
	{
		_frame_width = _screenWidth;
		_frame_height = _screenHeight;

		
		if (!InitializeSurface("Raw Engine", _screenWidth, _screenHeight)) {
			return false;
		}

	
		return true;
	}


	void  Rasterizer::DrawLine(Vector2 pointA, Vector2 pointB, uint32_t color) {

	}




}
