#pragma once

#include <Platform/Application/Application.h>

#include "Utillities/Util.h"

#include <Graphics/Renderer/Renderer.h>
#include "Defines.h"

#include "RMath.h"

#include <cstdint>

using namespace Graphics;
class RawEngine : public Engine::Application {
public:
	RawEngine();
	virtual ~RawEngine();

	virtual bool Init() override;
	virtual bool Shutdown() override;
	virtual void Update() override;

	
private:
	Renderer* _renderer;


};


void Engine::CreateApplication(Engine::Application*& _ptrApplication) {
	delete _ptrApplication;
	_ptrApplication = new RawEngine();
	_ptrApplication->Init();
}

void Engine::RunApplication(Engine::Application*& _ptrApplication) {
	if (_ptrApplication != nullptr) {
		_ptrApplication->Update();
	}
}

void Engine::ShutdownApplication(Engine::Application*& _ptrApplication) {
	if (_ptrApplication != nullptr) {
		_ptrApplication->Shutdown();
		delete _ptrApplication;
	}
}

