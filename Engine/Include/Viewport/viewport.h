#pragma once

struct SDL_Window;

class viewport {

public:

	~viewport() = default;
	static viewport* getViewport();

	bool init(int x, int y);
	SDL_Window* getWindowHandle();

private:
	viewport() = default;
	SDL_Window* windowHandle;

};