#include "RawEngine.h"

#include "Debug/Logger/Logger.h"
#include <iterator>
#include <iostream>
#include <array>


RawEngine::RawEngine() : _renderer{nullptr}
{

}

RawEngine::~RawEngine()
{
}

bool RawEngine::Init()
{
	_renderer = new Renderer();
	_renderer->Init(800, 800);

	return true;
}

bool RawEngine::Shutdown()
{

	_renderer->Shutdown();
	
	
	delete _renderer;


	return true;
}




void RawEngine::Update()
{

	

	do {
		// Clear
		_renderer->ClearColor(0xFF242424); // xRGB
		_renderer->Clear(COLOR_BUFFER_BIT);

		_renderer->SetDrawMode(WIREFRAME);

		// Draw
		// Create a Vertex Buffer
		// Draw those points

		Vertex line_test[16]{

			// To Top Right
			Vertex
			{
				{ 0.0f,  0.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x16u, 0x16u, 0x16u }
			},
			Vertex
			{
				{ 1.0f,  1.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x16u, 0x16u, 0x16u }
			},

			// To Bottom Right
			Vertex
			{
				{ 0.0f,  0.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x16u, 0x16u, 0x16u }
			},
			Vertex
			{
				{ 1.0f,  -1.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x16u, 0x16u, 0x16u }
			},

			// To Bottom Left
			Vertex
			{
				{ 0.0f,  0.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x16u, 0x16u, 0x16u }
			},
			Vertex
			{
				{ -1.0f,  -1.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x16u, 0x16u, 0x16u }
			},
			
			// To Top Left
			Vertex
			{
				{ 0.0f,  0.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x16u, 0x16u, 0x16u }
			},
			Vertex
			{
				{ -1.0f,  1.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x16u, 0x16u, 0x16u }
			},
			// To Left
			Vertex
			{
				{ 0.0f,  0.0f, 0.0f, 0.0f },
				{ 0xFFu, 0xFFu, 0x00u, 0x00u }
			},
			Vertex
			{
				{ 1.0f,  0.0f, 0.0f, 0.0f },
				{ 0xFFu, 0xFFu, 0x00u, 0x00u }
			},

			// To Right
			Vertex
			{
				{ 0.0f,  0.0f, 0.0f, 0.0f },
				{ 0xFFu, 0xFFu, 0x00u, 0x00u }
			},
			Vertex
			{
				{-1.0f,  0.0f, 0.0f, 0.0f },
				{ 0xFFu, 0xFFu, 0x00u, 0x00u }
			},

			// To Top
			Vertex
			{
				{ 0.0f,  0.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x00u, 0xFFu, 0x00u }
			},
			Vertex
			{
				{ 0.0f,  1.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x00u, 0xFFu, 0x00u }
			},

			// To Bottom
			Vertex
			{
				{ 0.0f,  0.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x00u, 0xFFu, 0x00u }
			},
			Vertex
			{
				{ 0.0f,  -1.0f, 0.0f, 0.0f },
				{ 0xFFu, 0x00u, 0xFFu, 0x00u }
			},


		};

		//Vertex line_2[2]{
		//	Vertex
		//	{
		//		{ 0.25f, 0.25f, 0.0f, 0.0f },
		//		{ 0xFFu, 0xFFu, 0xFFu, 0xFFu }
		//	},
		//	Vertex
		//	{
		//		{ 0.25f, -0.25f, 0.0f, 0.0f },
		//		{ 0xFFu, 0xFFu, 0xFFu, 0xFFu }
		//	},
		//};

		int vertex_count = std::ssize(line_test);

		_renderer->CreateBuffer(vertex_count);
		_renderer->BindBuffer(line_test, sizeof(Vertex), vertex_count, sizeof(Vertex) * vertex_count);
		_renderer->Draw(std::ssize(line_test));
		_renderer->FreeBuffer();

		/*vertex_count = std::ssize(line_2);

		_renderer->CreateBuffer(vertex_count);
		_renderer->BindBuffer(line_2, sizeof(Vertex), vertex_count, sizeof(Vertex) * vertex_count);
		_renderer->Draw(vertex_count);
		_renderer->FreeBuffer();*/


		
		// Present
		//Debug::Debugger::Flush();

	} while (_renderer->SwapBuffers());
}

