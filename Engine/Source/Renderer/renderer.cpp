#include "Renderer/renderer.h"
#include "Renderer/opengl.h"

CBaseRenderer::s_EGraphicsAPI CBaseRenderer::s_ICurrentGraphicsAPI = CBaseRenderer::s_EGraphicsAPI::OpenGL;

CBaseRenderer* CBaseRenderer::CreateRenderer() {

	switch (CBaseRenderer::s_ICurrentGraphicsAPI) {
	
		case CBaseRenderer::s_EGraphicsAPI::OpenGL:
			return new COpenGLRenderer();
	
	}

}