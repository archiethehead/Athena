#pragma once

struct SDL_Window;

class CViewport {

public:
	~CViewport();

	bool Init(int x, int y);

	static CViewport* GetViewport();

private:
	CViewport() = default;
	static CViewport* s_PViewportSingleton;

};