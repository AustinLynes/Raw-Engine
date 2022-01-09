#include "RawEngine.h"


RawEngine::RawEngine() : _rasterizer{nullptr}
{

}

RawEngine::~RawEngine()
{
}

bool RawEngine::Init()
{
	_rasterizer = new Rasterizer();
	_rasterizer->Init(800, 800);


	return true;
}

bool RawEngine::Shutdown()
{

	_rasterizer->Shutdown();

	return true;
}


void RawEngine::Update()
{
	while (_rasterizer->SwapBuffers()) {}
}

