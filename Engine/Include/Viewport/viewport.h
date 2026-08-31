#pragma once

struct SDL_Window;

extern SDL_Window* m_PViewportWindow;

class CViewport {

public:
	~CViewport() = default;

	bool Init(int x, int y);

	static CViewport& GetViewport();

private:
	CViewport() = default;

};