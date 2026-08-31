#pragma once


class CBaseRenderer {

public:

	virtual ~CBaseRenderer() = default;
	
	virtual bool Init(void* WindowHandle) { return false; }

	virtual void ClearColour() {};
	virtual void BeginFrame() {};
	virtual void EndFrame() {};

	enum class s_EGraphicsAPI: char {

		OpenGL

	};
	static s_EGraphicsAPI s_ICurrentGraphicsAPI;

	static CBaseRenderer* CreateRenderer();

};