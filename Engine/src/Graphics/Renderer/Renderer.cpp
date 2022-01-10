#include "Renderer.h"

namespace Graphics {

	Renderer::Renderer()
	{

	}

	Renderer::~Renderer()
	{

	}

	bool Renderer::Init(uint _width, uint _height, uint _buffer_count)
	{
		RasterizerDesc desc{0};
		
		desc.frame_count = _buffer_count;
		desc.frame_height = _width;
		desc.frame_width = _height;
		desc.frame_size = _width * _height;

		_rasterizer = new Rasterizer(&desc);

		_rasterizer->Initilize();


		return false;
	}

	bool Renderer::Shutdown()
	{		
		_rasterizer->Shutdown();
		
		delete _rasterizer;

		if (!ShutdownSurface()) {
			return false;
		}

		return true;

	}

	bool Renderer::SwapBuffers()
	{
		return _rasterizer->SwapBuffers();
	}

	void Renderer::Clear(uint _bits) {
		_rasterizer->Clear(_bits);
	}

	void Renderer::ClearColor(uint _clearColor) {
		_rasterizer->SetClearColor(_clearColor);
	}
	
	void Renderer::Draw(uint _count) {
		_rasterizer->ProcessVertices(_count);
	}

	void Renderer::BindBuffer(Vertex* _buffer, uint _stride, uint _count, uint _buffer_size) {
		_rasterizer->BindBuffer(_buffer, _stride,_count, _buffer_size);
	}

	void Renderer::FreeBuffer()
	{
		_rasterizer->DestroyBuffer();
	}

	void Renderer::CreateBuffer(uint _count) {
		_rasterizer->CreateBuffer(_count);
	}

	void Renderer::SetDrawMode(uint _drawMode) {
		_rasterizer->SetDrawMode(_drawMode);
	}

}
