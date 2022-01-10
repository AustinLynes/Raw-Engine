#pragma once
#include "pch.h"

#include "Graphics/Renderer/Surface/Surface.h"
#include "RMath.h"

namespace Graphics {

	typedef unsigned int uint;

	struct Vertex {
		float xyzw[4]{ 0.0f };				// 16 bytes
		uint color[4]{ 0x00u };				// 16 bytes 
	};

	struct VertexArrayObject {
		float* buffer;
		uint32_t stride;
		uint32_t size;
	};

	struct RasterizerDesc {

		uint frame_count = 0;
		uint frame_height = 0;
		uint frame_width = 0;
		uint frame_size = 0;

		uint bufferBits = 0;
		uint clearColor = 0;

		uint drawMode;

		Vertex* vertexBuffer = nullptr; // to be Bound at runtime

		uint vertexBufferSize = 0;
		uint stride = 0;

		uint** frames = nullptr;
		uint* frame_ptr = nullptr;
		uint frame_index = 0;



	};

	class Rasterizer {

		// 1. Describe Rasterizer
		//		the rasterizer will fail silently if you do not describe the 
		//		what the rasterizer should look like, and do.
		// 2. Initilize
		// -------------------- Primitive Drawing
		// 0. Create a Buffer
		// 1. Bind Buffer
		// 2. Draw(vertex count)


	public:
		Rasterizer() {}
		Rasterizer(RasterizerDesc* _ptrRasterDesc);

		bool Initilize();
		bool Shutdown();

		void ProcessVertices(uint32_t _count);

		bool SwapBuffers();

		void Clear(uint bits);
		void SetClearColor(uint color);

		void DrawPoint(int x, int y, uint color);

		void SetDrawMode(uint drawMode);


		void CreateBuffer(uint size); // only creates vertex buffers

		void BindBuffer(Vertex* _buffer, uint _stride, uint _count, uint buffer_size);

		void DestroyBuffer();




		RasterizerDesc raster_desc;


	};





}