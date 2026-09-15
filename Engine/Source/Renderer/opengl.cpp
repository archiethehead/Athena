#include "Renderer/OpenGL.h"
#include "Debug/Logger.h"
#include "glad/gl.h"

bool COpenGLRenderer::Init(SDL_Window* WindowHandle) {

	COpenGLRenderer::m_PWindowHandle = WindowHandle;
	COpenGLRenderer::m_OGLContext = SDL_GL_CreateContext(COpenGLRenderer::m_PWindowHandle);

	if (!COpenGLRenderer::m_OGLContext) goto Error;
	if(!SDL_GL_MakeCurrent(m_PWindowHandle, m_OGLContext)) goto Error;
	gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

	DEBUG_OUT("OpenGL initialization success", OutputOptions::None);

	return true;

Error:
	SDL_Quit();
	DEBUG_OUT("OpenGL init failed, %s", OutputOptions::Error, SDL_GetError());
	return false;

}