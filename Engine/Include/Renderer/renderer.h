#pragma once

struct SDL_Window;

class CBaseRenderer {

public:

	virtual ~CBaseRenderer() = default;
	
	virtual bool Init(void* WindowHandle) { return false; }

	virtual void ClearColour() {};
	virtual void BeginFrame() {};
	virtual void EndFrame() {};

	enum class m_EGraphicsAPI: char {

		OpenGL

	};
	static m_EGraphicsAPI s_ICurrentGraphicsAPI;
	static CBaseRenderer* CreateRenderer();

};