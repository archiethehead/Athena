#pragma once

struct SDL_Window;

class CViewport {

public:

	~CViewport() = default;
	static CViewport* GetViewport();

	bool Init(int x, int y);
	void* GetWindowHandle();

private:
	CViewport() = default;
	SDL_Window* m_WindowHandle_t;

};