#include "Engine.h"
#include <cstdio>

void CAthenaEngine::Update(float fDelta) {

	static float fTime = 0.0f;
	static int iSeconds = 0;
	fTime += fDelta;
	bool IsZero = fTime >= 1.0f;


	if (IsZero) {
	
		fTime = 0.0f;
		iSeconds++;
		printf("%d seconds have passed", iSeconds);

	}

}