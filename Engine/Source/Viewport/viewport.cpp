#include "Viewport/viewport.h"
#include "SDL3/SDL.h"
#include <cstdio>

CViewport* CViewport::s_PViewportSingleton = nullptr;

CViewport::~CViewport() {

	CViewport::s_PViewportSingleton = nullptr;

}

bool CViewport::Init(int x, int y) {

	SDL_Window* Window_t;

	if (!SDL_Init(SDL_INIT_VIDEO)) goto Error;
	
	Window_t = SDL_CreateWindow("Athena Engine", x, y, SDL_WINDOW_OPENGL);

	if (!Window_t) goto Error;

	return true;

Error:
	printf("ERROR: Viewport init failed, %s\n", SDL_GetError());
	return false;

}

CViewport* CViewport::GetViewport() {

	if (CViewport::s_PViewportSingleton == nullptr) {
	
		CViewport NewViewport = CViewport();
		s_PViewportSingleton = &NewViewport;
	
	}

	return s_PViewportSingleton;

}