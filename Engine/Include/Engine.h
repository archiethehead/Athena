#pragma once

#ifdef COMPILING_ENGINE

	#define DLL_LINK __declspec(dllexport)

#else

	#define DLL_LINK __declspec(dllimport) 

#endif // ifdef COMPILING_ENGINE

#include "Viewport/viewport.h"
#include "Renderer/renderer.h"

class DLL_LINK CAthenaEngine {

public:
	~CAthenaEngine() = default;
	void Update(float fDelta);
	bool Init(int x, int y);
	static CAthenaEngine& GetEngine();

private:
	CAthenaEngine() :	m_PViewport(CViewport::GetViewport()),
						m_PRenderer(CBaseRenderer::CreateRenderer())
	{};

	CViewport* m_PViewport;
	CBaseRenderer* m_PRenderer;

};