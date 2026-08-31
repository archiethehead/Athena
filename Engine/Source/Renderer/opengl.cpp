#include "Renderer/OpenGL.h"

SDL_GLContext* g_PSDLGLContext_t =  nullptr;

bool COpenGLRenderer::Init(void* WindowHandle) {

	COpenGLRenderer::m_PWindowHandle = static_cast<SDL_Window*>(WindowHandle);
	COpenGLRenderer::m_OGLContext = SDL_GL_CreateContext(COpenGLRenderer::m_PWindowHandle);

	if (!COpenGLRenderer::m_OGLContext) {
	
		return false;
	
	}

	return true;

}