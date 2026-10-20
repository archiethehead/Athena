#pragma once

#ifdef _WIN32

#include <windows.h>

	#ifdef COMPILING_ENGINE
		
		#define DLL_LINK __declspec(dllexport)

	#else

		#define DLL_LINK __declspec(dllimport) 

	#endif // ifdef COMPILING_ENGINE

#else

	#define DLL_LINK

#endif // ifdef _WIN32s

#include "Viewport/viewport.h"
#include "Renderer/renderer.h"

typedef void (*CrashCallbackFunction)();
static CrashCallbackFunction s_SandboxCrashCallback = nullptr;

class DLL_LINK athenaEngine {

public:
	~athenaEngine() = default;
	void update(float fDelta);
	void setCrashCallback(CrashCallbackFunction FPCrashCallback);
	bool init(int x, int y);
	static athenaEngine& GetEngine();

private:

	viewport* viewport;
	baseRenderer* renderer;

	athenaEngine();

#ifdef _WIN32

	static LONG WINAPI handleExceptionCrash(struct _EXCEPTION_POINTERS* ExceptionInformation);

#endif // ifdef _WIN32

	static void handleSignalCrash(int Signal);
	static void crashProcedure();
	static void killProgram();

};