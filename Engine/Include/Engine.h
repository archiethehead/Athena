#pragma once

#ifdef COMPILING_ENGINE
#define DLL_LINK __declspec(dllexport)
#else
#define DLL_LINK __declspec(dllimport) 
#endif

class DLL_LINK CAthenaEngine {

public:
	~CAthenaEngine();

	void Update(float fDelta);

	static CAthenaEngine* GetEngine();

private:
	CAthenaEngine() = default;
	static CAthenaEngine* s_PEngineSingleton;

};