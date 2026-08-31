#pragma once

#include "Renderer/renderer.h"
#include "SDL3/SDL.h"

extern SDL_GLContext* g_PSDLGLContext_t;

class COpenGLRenderer : public CBaseRenderer {

public:
	COpenGLRenderer() = default;
	~COpenGLRenderer() = default;

	bool Init(void* WindowHandle) override;

private:
	SDL_GLContext m_OGLContext = nullptr;
	SDL_Window* m_PWindowHandle = nullptr;

};