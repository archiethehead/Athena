#pragma once


class IRenderer {

public:

	virtual ~IRenderer() = default;
	
	virtual bool Init();

	virtual void ClearColour();
	virtual void BeginFrame();
	virtual void EndFrame();

	enum class s_EGraphicsAPI: char {

		OpenGL

	};
	static s_EGraphicsAPI s_ICurrentGraphicsAPI;

	static IRenderer* CreateRenderer();

};