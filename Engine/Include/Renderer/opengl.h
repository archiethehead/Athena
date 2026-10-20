#pragma once
#include "SDL3/SDL.h"

#include "Renderer/renderer.h"


class openGLRenderer : public baseRenderer {

public:
	openGLRenderer() = default;
	~openGLRenderer() = default;
	bool init(SDL_Window* WindowHandle) override;
	void clearColour() {};

private:
	SDL_GLContext GLContext = nullptr;
	SDL_Window* windowHandle = nullptr;

};