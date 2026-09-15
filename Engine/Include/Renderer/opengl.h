#pragma once
#include "SDL3/SDL.h"

#include "Renderer/renderer.h"


class COpenGLRenderer : public CBaseRenderer {

public:
	COpenGLRenderer() = default;
	~COpenGLRenderer() = default;
	bool Init(SDL_Window* WindowHandle) override;
	void ClearColour() {};

private:
	SDL_GLContext m_OGLContext = nullptr;
	SDL_Window* m_PWindowHandle = nullptr;

};