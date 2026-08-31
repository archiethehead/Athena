#include "Viewport/viewport.h"
#include "Renderer/openGL.h"
#include "SDL3/SDL.h"
#include <cstdio>

CViewport* CViewport::s_PViewportSingleton = nullptr;
SDL_Window* m_PViewportWindow = nullptr;

CViewport::~CViewport() {

	CViewport::s_PViewportSingleton = nullptr;

}

bool CViewport::Init(int x, int y) {

	SDL_Window* Window_t = NULL;
	SDL_GLContext NewGLContext_t = NULL;

	if (!SDL_Init(SDL_INIT_VIDEO)) goto Error;
	
	Window_t = SDL_CreateWindow("Athena Engine", x, y, SDL_WINDOW_OPENGL);

	if (!Window_t) goto Error;

	m_PViewportWindow = Window_t;
	NewGLContext_t = SDL_GL_CreateContext(Window_t);

	if (!NewGLContext_t) goto Error;

	g_PSDLGLContext_t = &NewGLContext_t;

	return true;

Error:
	if (Window_t) SDL_DestroyWindow(Window_t);
	SDL_Quit();
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