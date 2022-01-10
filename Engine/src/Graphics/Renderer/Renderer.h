#pragma once
#include "pch.h"
#include "Rasterizer/Rasterizer.h"

#include "RMath.h"
#include <cassert>

namespace Graphics {

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		bool Init(uint _width, uint _height, uint _buffer_count = 2);
		bool Shutdown();
		
		bool SwapBuffers();
	
		void BindBuffer(Vertex* _buffer, uint _stride, uint _count, uint buffer_size);

		void CreateBuffer(uint _count);

		void FreeBuffer();

		void Clear(uint _bits);

		void ClearColor(uint clearColor);

		void Draw(uint _count);

		void SetDrawMode(uint _drawMode);

		

	private:
		Rasterizer* _rasterizer;
	

		bool _should_close;
	};

}

