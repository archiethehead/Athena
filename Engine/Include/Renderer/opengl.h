#pragma once

#include "Renderer/renderer.h"
#include <SDL3/SDL.h>

class COpenGLRenderer : public CBaseRenderer {

public:
	COpenGLRenderer() = default;
	~COpenGLRenderer() = default;
	bool Init(void* WindowHandle) override;
	void ClearColour() override;

private:
	SDL_GLContext m_OGLContext = nullptr;
	SDL_Window* m_PWindowHandle = nullptr;

};