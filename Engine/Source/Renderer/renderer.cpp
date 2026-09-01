#include "Renderer/renderer.h"
#include "Renderer/openGL.h"
#include "SDL3/SDL.h"

CBaseRenderer::m_EGraphicsAPI CBaseRenderer::s_ICurrentGraphicsAPI = CBaseRenderer::m_EGraphicsAPI::OpenGL;

CBaseRenderer* CBaseRenderer::CreateRenderer() {

	static CBaseRenderer* s_PRendererSingleton = nullptr;

	if (s_PRendererSingleton == nullptr) {

		switch (CBaseRenderer::s_ICurrentGraphicsAPI) {

		case CBaseRenderer::m_EGraphicsAPI::OpenGL:

			s_PRendererSingleton = new COpenGLRenderer();


		}

	}

	return s_PRendererSingleton;

}