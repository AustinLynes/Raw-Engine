#pragma once

namespace Engine {

	class Application
	{
	public:
		Application(){};
		virtual ~Application() {};

		virtual bool Init() = 0;
		virtual bool Shutdown() = 0;

		virtual void Update() = 0;
	};

	void CreateApplication(Application*& _ptrApplication);
	void RunApplication(Application*& _ptrApplication);
	void ShutdownApplication(Application*& _ptrApplication);

}

