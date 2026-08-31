#pragma once

#include "Viewport/viewport.h"
#include <SDL3/SDL.h>

class CSDLViewport : public CBaseViewport {

public:

	CSDLViewport() = default;
	~CSDLViewport() = default;

	bool Init(int x, int y) override;
	void* GetWindowHandle() override;

private:
	SDL_Window* m_WindowHandle_t = nullptr;

};