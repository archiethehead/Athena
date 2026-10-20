#include "Viewport/viewport.h"
#include "SDL3/SDL.h"
#include "Debug/Logger.h"

bool viewport::init(int x, int y) {

	if (!SDL_Init(SDL_INIT_VIDEO)) goto Error;

	windowHandle = SDL_CreateWindow("Athena Engine", x, y, SDL_WINDOW_OPENGL);

	if (!windowHandle) goto Error;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	DEBUG_OUT("Viewport initialization success\n", outputOptions::None);

	return true;

Error:
	SDL_Quit();
	DEBUG_OUT("Viewport init failed, %s\n", outputOptions::Error, SDL_GetError());
	return false;

}

SDL_Window* viewport::getWindowHandle() {

	return windowHandle;

}

viewport* viewport::getViewport() {

	static viewport viewportSingleton = viewport();
	return &viewportSingleton;

}