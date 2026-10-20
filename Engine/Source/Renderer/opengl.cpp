#include "Renderer/OpenGL.h"
#include "Debug/Logger.h"
#include "glad/gl.h"

bool openGLRenderer::init(SDL_Window* WindowHandle) {

	openGLRenderer::windowHandle = WindowHandle;
	openGLRenderer::GLContext = SDL_GL_CreateContext(openGLRenderer::windowHandle);

	if (!openGLRenderer::GLContext) goto Error;
	if(!SDL_GL_MakeCurrent(windowHandle, GLContext)) goto Error;
	gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

	DEBUG_OUT("OpenGL initialization success\n", outputOptions::None);

	return true;

Error:
	SDL_Quit();
	DEBUG_OUT("OpenGL init failed, %s\n", outputOptions::Error, SDL_GetError());
	return false;

}