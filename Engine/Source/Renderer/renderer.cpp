#include "Renderer/renderer.h"
#include "Renderer/openGL.h"
#include "SDL3/SDL.h"

baseRenderer::graphicsAPI baseRenderer::currentGraphicsAPI = baseRenderer::graphicsAPI::OpenGL;

baseRenderer* baseRenderer::createRenderer() {

	static baseRenderer* rendererSingleton = nullptr;

	if (rendererSingleton == nullptr) {

		switch (baseRenderer::currentGraphicsAPI) {

		case baseRenderer::graphicsAPI::OpenGL:

			rendererSingleton = new openGLRenderer();


		}

	}

	return rendererSingleton;

}