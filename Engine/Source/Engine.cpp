#include "Engine.h"
#include <cstdio>

CAthenaEngine* CAthenaEngine::s_PEngineSingleton = nullptr;

CAthenaEngine::~CAthenaEngine() {

	CAthenaEngine::s_PEngineSingleton = nullptr;

}

void CAthenaEngine::Update(float fDelta) {

	static float fTime = 0.0f;
	static int iSeconds = 0;
	fTime += fDelta;

	if (fTime >= 1.0f) {
	
		fTime = 0.0f;
		iSeconds++;
		printf("\r%d seconds have passed", iSeconds);

	}

}

CAthenaEngine* CAthenaEngine::GetEngine() {

	if (CAthenaEngine::s_PEngineSingleton == nullptr) {
	
		CAthenaEngine NewEngine = CAthenaEngine();
		CAthenaEngine::s_PEngineSingleton = &NewEngine;

	}

	return CAthenaEngine::s_PEngineSingleton;

}