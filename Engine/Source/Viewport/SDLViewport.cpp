#include "Viewport/SDLViewport.h"
#include "SDL3/SDL.h"
#include "debug.h"

bool CSDLViewport::Init(int x, int y) {

	if (!SDL_Init(SDL_INIT_VIDEO)) goto Error;

	m_WindowHandle_t = SDL_CreateWindow("Athena Engine", x, y, SDL_WINDOW_OPENGL);

	if (!m_WindowHandle_t) goto Error;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	return true;

Error:
	SDL_Quit();
	Out("ERROR: Viewport init failed, %s\n", SDL_GetError());
	return false;

}

void* CSDLViewport::GetWindowHandle() {

	void* PWindowHandle_t = static_cast<void*>(m_WindowHandle_t);
	return PWindowHandle_t;

}