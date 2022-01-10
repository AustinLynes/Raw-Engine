#include "Rasterizer.h"
#include "Debug/Logger/Logger.h"

#include "Defines.h"


namespace Graphics {
	Rasterizer::Rasterizer(RasterizerDesc* _ptrRasterDesc)
	{
		raster_desc = *_ptrRasterDesc;
	}
	bool Rasterizer::Initilize()
	{
		raster_desc.frames = new uint32_t * [raster_desc.frame_count];

		for (uint32_t i = 0; i < raster_desc.frame_count; i++)
		{
			raster_desc.frames[i] = new uint32_t[raster_desc.frame_size];
		}

		if (!InitializeSurface("Raw Engine", raster_desc.frame_width, raster_desc.frame_height)) {
			return false;
		}

		return true;

	}

	bool Rasterizer::Shutdown()
	{

		for (uint32_t i = 0; i < raster_desc.frame_count; i++)
		{
			delete raster_desc.frames[i];
		}

		delete raster_desc.frames;

		return true;
	}

	// there needs to be a vertex buffer bound
	// 00F0 00F0 0000 0000 0000 0000 0000 0000
	//   X	  Y	  R		G	B	  A
	// 
	void Rasterizer::ProcessVertices(uint32_t _count)
	{
		int j = 0;

		raster_desc.vertexBufferSize = sizeof(Vertex) * _count;
		


		if ((raster_desc.drawMode & POINT) == POINT) {

			for (Vertex* vertex = static_cast<Vertex*>(raster_desc.vertexBuffer); vertex != (static_cast<Vertex*>(raster_desc.vertexBuffer) + _count); ) // X Y
			{
				float* positions = vertex->xyzw;
				int* ndc_xy = nullptr;

				RMath::GetPixelSpace(positions[0], positions[1], raster_desc.frame_width, raster_desc.frame_height, ndc_xy);

				int x = static_cast<int>(ndc_xy[0]);
				int y = static_cast<int>(ndc_xy[1]);

				uint a = vertex->color[0] << 0x18u;
				uint r = vertex->color[1] << 0x10u;
				uint g = vertex->color[2] << 0x08u;
				uint b = vertex->color[3];

				uint color = a | r | g | b;

				DrawPoint(x, y, color);

				vertex++;

				delete ndc_xy;

			}
		}
		else if ((raster_desc.drawMode & WIREFRAME) == WIREFRAME) {
			for (Vertex* vertex_A = raster_desc.vertexBuffer; vertex_A < (static_cast<Vertex*>(raster_desc.vertexBuffer) + _count); )
			{

				Vertex* vertex_B = vertex_A + 1;

				int* ps_x0_y0 = nullptr;
				int* ps_x1_y1 = nullptr;

				RMath::GetPixelSpace(vertex_A->xyzw[0], vertex_A->xyzw[1], raster_desc.frame_width, raster_desc.frame_height, ps_x0_y0);
				int x0 = ps_x0_y0[0];
				int y0 = ps_x0_y0[1];

				RMath::GetPixelSpace(vertex_B->xyzw[0], vertex_B->xyzw[1], raster_desc.frame_width, raster_desc.frame_height, ps_x1_y1);
				int x1 = ps_x1_y1[0];
				int y1 = ps_x1_y1[1];
				
				std::stringstream msg;
				msg <<
					"vertex_A.x: " << vertex_A->xyzw[0] << "\t" <<
					"vertex_A.y: " << vertex_A->xyzw[1] << "\t" <<
					"vertex_B.x: " << vertex_B->xyzw[0] << "\t" <<
					"vertex_B.y: " << vertex_B->xyzw[1] << "\t" <<
					"x0: " << x0 << "\t" <<
					"y0: " << y0 << "\t" <<
					"x1: " << x1 << "\t" <<
					"y1: " << y1 << "\t";

				Debug::Debugger::Log(msg.str());

				Debug::Debugger::Flush();


				// LEFT
				if (x0 > x1 && y0 == y1) {
					for (int _x = x1; _x < x0; _x++)
					{
						// PERFORM SHADING
						uint a = vertex_A->color[0] << 0x18u;
						uint r = vertex_A->color[1] << 0x10u;
						uint g = vertex_A->color[2] << 0x08u;
						uint b = vertex_A->color[3];

						uint color = a | r | g | b;

						DrawPoint(_x, floor(y0 + 0.5f), color);
					}

				} 
				// RIGHT
				else if (x0 < x1 && y0 == y1) {
					for (int _x = x0; _x < x1; _x++)
					{
						// PERFORM SHADING
						uint a = vertex_A->color[0] << 0x18u;
						uint r = vertex_A->color[1] << 0x10u;
						uint g = vertex_A->color[2] << 0x08u;
						uint b = vertex_A->color[3];

						uint color = a | r | g | b;

						DrawPoint(_x, floor(y0 + 0.5f), color);
					}

				}
				// UP
				else if (y0 < y1 && x0 == x1) {

					for (int _y = y0; _y < y1; _y++)
					{
						//float deltaX = x0 - x1;
						//float R = (_x - x1) / deltaX;
						//float _y = RMath::Lerp(y0, y1, R);


						// PERFORM SHADING
						uint a = vertex_A->color[0] << 0x18u;
						uint r = vertex_A->color[1] << 0x10u;
						uint g = vertex_A->color[2] << 0x08u;
						uint b = vertex_A->color[3];

						uint color = a | r | g | b;

						DrawPoint(x0, floor(_y + 0.5f), color);
					}

				}
				// DOWN
				else if (y0 > y1 && x0 == x1) {
					for (int _y = y1; _y < y0; _y++)
					{
						/*float deltaX = x0 - x1;
						float R = (_x - x1) / deltaX;
						
						float _y = RMath::Lerp(y0, y1, R);*/


						// PERFORM SHADING
						uint a = vertex_A->color[0] << 0x18u;
						uint r = vertex_A->color[1] << 0x10u;
						uint g = vertex_A->color[2] << 0x08u;
						uint b = vertex_A->color[3];

						uint color = a | r | g | b;

						DrawPoint(x0, floor(_y + 0.5f), color);
					}

				}
				// RIGHT_UP
				else if (x0 < x1 && y0 > y1)
				{
 					for (int _x = x0; _x < x1; _x++)
					{
						float deltaX = x0 - x1;
						float R = (_x - x1) / deltaX;
						float _y = RMath::Lerp(y1, y0, R);


						// PERFORM SHADING
						uint a = vertex_A->color[0] << 0x18u;
						uint r = vertex_A->color[1] << 0x10u;
						uint g = vertex_A->color[2] << 0x08u;
						uint b = vertex_A->color[3];

						uint color = a | r | g | b;

						DrawPoint(_x, floor(_y + 0.5f), color);
					}

				}
				// RIGHT_DOWN
				else if (x0 < x1 && y0 < y1) {
					for (int _x = x0; _x< x1; _x++)
					{
						float deltaX = x1 - x0;
						float R = (_x - x0) / deltaX;
						float _y = RMath::Lerp(y0, y1, R);
					
						// PERFORM SHADING
						uint a = vertex_A->color[0] << 0x18u;
						uint r = vertex_A->color[1] << 0x10u;
						uint g = vertex_A->color[2] << 0x08u;
						uint b = vertex_A->color[3];

						uint color = a | r | g | b;

						DrawPoint(_x, floor(_y - 0.5f), color);
					}

				}
				// LEFT_UP
				else if (x0 > x1 && y0 > y1)
				{
					for (int _x = x1; _x < x0; _x++)
					{
						float deltaX = x0 - x1;
						float R = (_x - x1) / deltaX;
						float _y = RMath::Lerp(y1, y0, R);
					
						// PERFORM SHADING
						uint a = vertex_A->color[0] << 0x18u;
						uint r = vertex_A->color[1] << 0x10u;
						uint g = vertex_A->color[2] << 0x08u;
						uint b = vertex_A->color[3];

						uint color = a | r | g | b;

						DrawPoint(_x, floor(_y - 0.5f), color);

					}

				}
				// LEFT_DOWN
				else if (x0 > x1 && y0 < y1) {

					for (int _x = x0 - 1; _x >= x1; _x--)
					{
						float deltaX = x1 - x0;
						float R = (_x - x0) / deltaX;
						float _y = RMath::Lerp(y0, y1, R);

						// PERFORM SHADING
						uint a = vertex_A->color[0] << 0x18u;
						uint r = vertex_A->color[1] << 0x10u;
						uint g = vertex_A->color[2] << 0x08u;
						uint b = vertex_A->color[3];

						uint color = a | r | g | b;


						DrawPoint(_x, floor(_y + 0.5f), color);
					}

				}

				vertex_A += 2;
				
				delete ps_x0_y0;
				delete ps_x1_y1;
			}
		}

	}

	void Rasterizer::SetDrawMode(uint drawMode)
	{
		raster_desc.drawMode |= drawMode;
	}

	bool  Rasterizer::SwapBuffers()
	{
		bool _success = UpdateSurface(raster_desc.frames[raster_desc.frame_index], raster_desc.frame_size);
		
		if (!_success) {
			return false;
		}

		raster_desc.frame_index++;
		raster_desc.frame_index %= raster_desc.frame_count;

		return true;
	}

	void  Rasterizer::Clear(uint bits)
	{
		if (bits & COLOR_BUFFER_BIT) {
			for (uint32_t i = 0; i < raster_desc.frame_size; i++)
			{
				raster_desc.frames[raster_desc.frame_index][i] = raster_desc.clearColor;
			}
		}
	}


	void  Rasterizer::SetClearColor(uint color)
	{
		raster_desc.clearColor = color;
	}

	void  Rasterizer::DrawPoint(int x, int y, uint color)
	{
		if (!(x >= 0 && x < raster_desc.frame_width && y >= 0 && y < raster_desc.frame_height))
			return;

		raster_desc.frames[raster_desc.frame_index][RMath::To1D(x, y, raster_desc.frame_width)] = color;
	}

	void Rasterizer::CreateBuffer(uint _count)
	{
		raster_desc.vertexBuffer = new Vertex[_count];
	}

	void Rasterizer::BindBuffer(Vertex* _buffer, uint _stride, uint _count, uint _buffer_size)
	{
		for (size_t i = 0; i < _count; i++)
		{
			raster_desc.vertexBuffer[i] = _buffer[i];
		}

		raster_desc.vertexBufferSize = _buffer_size;
		raster_desc.stride = _stride;

	}

	void Rasterizer::DestroyBuffer()
	{
		delete raster_desc.vertexBuffer;
	}

}
