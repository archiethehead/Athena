#pragma once

struct SDL_Window;

class baseRenderer {

public:
	
	virtual bool init(SDL_Window* windowHandle) { return false; }

	virtual void clearColour() {};
	virtual void beginFrame() {};
	virtual void endFrame() {};

	enum graphicsAPI: char {

		OpenGL

	};

	static graphicsAPI currentGraphicsAPI;
	static baseRenderer* createRenderer();

};