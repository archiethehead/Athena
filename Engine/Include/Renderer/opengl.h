#pragma once

#include "Renderer/renderer.h"
#include "SDL3/SDL.h"

extern SDL_GLContext* g_PSDLGLContext_t;

class COpenGLRenderer : public CBaseRenderer {

public:
	COpenGLRenderer() = default;
	~COpenGLRenderer() = default;

	bool Init() override;

private:

};