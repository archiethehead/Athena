#include "Viewport/viewport.h"
#include "Viewport/SDLViewport.h"


CBaseViewport::m_EViewportAPI CBaseViewport::s_ICurrentViewportAPI = CBaseViewport::m_EViewportAPI::SDL3;

CBaseViewport* CBaseViewport::CreateViewport() {

	static CBaseViewport* s_PViewportSingleton = nullptr;

	if (s_PViewportSingleton == nullptr) {
	
		switch (CBaseViewport::s_ICurrentViewportAPI) {
		
		case CBaseViewport::m_EViewportAPI::SDL3:
			s_PViewportSingleton = new CSDLViewport();
		
		}
	
	}

	return s_PViewportSingleton;

}