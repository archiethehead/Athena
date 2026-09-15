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

class DLL_LINK CAthenaEngine {

public:
	~CAthenaEngine() = default;
	void Update(float fDelta);
	void SetCrashCallback(CrashCallbackFunction FPCrashCallback);
	bool Init(int x, int y);
	static CAthenaEngine& GetEngine();

private:

	CViewport* m_PViewport;
	CBaseRenderer* m_PRenderer;

	CAthenaEngine();

#ifdef _WIN32

	static LONG WINAPI HandleExceptionCrash(struct _EXCEPTION_POINTERS* ExceptionInformation);

#endif // ifdef _WIN32

	static void HandleSignalCrash(int Signal);
	static void CrashProcedure();
	static void KillProgram();

};