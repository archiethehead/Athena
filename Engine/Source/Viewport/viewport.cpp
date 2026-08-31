#include "Viewport/viewport.h"
#include "Renderer/openGL.h"
#include "SDL3/SDL.h"
#include <cstdio>

SDL_Window* m_PViewportWindow = nullptr;

bool CViewport::Init(int x, int y) {

	SDL_Window* Window_t = nullptr;
	SDL_GLContext NewGLContext_t = nullptr;

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

CViewport& CViewport::GetViewport() {

	static CViewport s_PViewportSingleton;
	return s_PViewportSingleton;

}