#pragma once

#ifdef COMPILING_ENGINE

	#define DLL_LINK __declspec(dllexport)

#else

	#define DLL_LINK __declspec(dllimport) 

#endif // ifdef COMPILING_ENGINE

#include "Viewport/viewport.h"
#include "Renderer/renderer.h"

typedef void (*CrashCallbackFunction)(const char*);
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
	static void HandleCrash(int Signal);

};