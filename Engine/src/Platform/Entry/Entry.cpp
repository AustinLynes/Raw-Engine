// *****************************************
// Author: Austin Lynes 
// 
// 
// Last Modified: January 8th, 2022
// *****************************************
#include "Debug/Logger/Logger.h"

#include <Platform/Application/Application.h>

#include <Graphics/Rasterization/Surface.h>
#include <cstdlib>

#define WINDOW_TITLE "Raw Engine"
#define SURFACE_WIDTH	800
#define SURFACE_HEIGHT	600

#if defined(CreateApplication)
#undef CreateApplication
#endif

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define CHECK_MEMORY_LEAKS _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#define FIND_MEMORY_LEAK(leak_flag) _CrtSetBreakAlloc(leak_flag)
#define LEAK_FLAG -1
#else 
#define CHECK_MEMORY_LEAKS
#define FIND_MEMEORY_LEAKS
#define LEAK_FLAG

#endif

using namespace Debug;


extern void Engine::CreateApplication(Engine::Application*& _ptrApplication);
extern void Engine::RunApplication(Engine::Application*& _ptrApplication);
extern void Engine::ShutdownApplication(Engine::Application*& _ptrApplication);

int main()
{
	#ifdef _DEBUG
	CHECK_MEMORY_LEAKS;
	FIND_MEMORY_LEAK(LEAK_FLAG);
	#endif

	Engine::Application* app = nullptr;

	Engine::CreateApplication(app);

	if (app == nullptr) {
		return EXIT_FAILURE;
	}

	Engine::RunApplication(app);


	Engine::ShutdownApplication(app);

	return EXIT_SUCCESS;
}
