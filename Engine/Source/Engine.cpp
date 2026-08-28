#include "Engine.h"
#include <cstdio>

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