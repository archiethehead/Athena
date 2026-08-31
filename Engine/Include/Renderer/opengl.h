#pragma once

#include "Renderer/renderer.h"
#include <SDL3/SDL_video.h>

class COpenGLRenderer : public CBaseRenderer {

public:
	COpenGLRenderer() = default;
	~COpenGLRenderer() = default;
	bool Init(void* WindowHandle) override;

private:
	SDL_GLContext m_OGLContext = nullptr;
	SDL_Window* m_PWindowHandle = nullptr;

};