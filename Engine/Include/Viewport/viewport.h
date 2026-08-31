#pragma once

class CBaseViewport {

public:
	virtual ~CBaseViewport() = default;
	virtual bool Init(int x, int y) { return false;  };
	virtual void* GetWindowHandle() { return nullptr; }
	static CBaseViewport* GetViewport();

	enum class m_EViewportAPI : char {
	
		SDL3
	
	};
	static m_EViewportAPI s_ICurrentViewportAPI;
	static CBaseViewport* CreateViewport();

};