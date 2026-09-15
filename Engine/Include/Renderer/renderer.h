#pragma once

struct SDL_Window;

class CBaseRenderer {

public:
	
	virtual bool Init(SDL_Window* WindowHandle) { return false; }

	virtual void ClearColour() {};
	virtual void BeginFrame() {};
	virtual void EndFrame() {};

	enum m_EGraphicsAPI: char {

		OpenGL

	};
	static m_EGraphicsAPI s_ICurrentGraphicsAPI;
	static CBaseRenderer* CreateRenderer();

};