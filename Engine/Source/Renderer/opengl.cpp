#include "Renderer/OpenGL.h"
#include "debug.h"
#include "glad/gl.h"

bool COpenGLRenderer::Init(void* WindowHandle) {

	COpenGLRenderer::m_PWindowHandle = static_cast<SDL_Window*>(WindowHandle);
	COpenGLRenderer::m_OGLContext = SDL_GL_CreateContext(COpenGLRenderer::m_PWindowHandle);

	if (!COpenGLRenderer::m_OGLContext) goto Error;
	if(!SDL_GL_MakeCurrent(m_PWindowHandle, m_OGLContext)) goto Error;
	gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

	DebugOut("OpenGL initialization success\n");

	return true;

Error:
	SDL_Quit();
	DebugOut("ERROR: OpenGL init failed, %s\n", SDL_GetError());
	return false;

}