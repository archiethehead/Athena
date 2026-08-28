#pragma once

#ifdef COMPILING_ENGINE
#define DLL_LINK __declspec(dllexport)
#else
#define DLL_LINK __declspec(dllimport) 
#endif

class DLL_LINK CAthenaEngine {

public:
	CAthenaEngine() = default;
	~CAthenaEngine() = default;

	void Update(float fDelta);

};