#include "Engine.h"
#include "Debug.h"

void CAthenaEngine::Update(float fDelta) {

	static float fTime = 0.0f;
	static unsigned int iSeconds = 0;
	fTime += fDelta;

	if (fTime >= 1.0f) {
	
		fTime = 0.0f;
		iSeconds++;
		Out("\r%u seconds have passed", iSeconds);

	}

}

bool CAthenaEngine::Init(int x, int y) {

	if (!m_PViewport->Init(x, y)) goto Error;
	if (!m_PRenderer->Init(m_PViewport->GetWindowHandle())) goto Error;

	Out("Engine initialization success!");
	return true;

Error:
	return false;

}

CAthenaEngine& CAthenaEngine::GetEngine() {

	static CAthenaEngine s_PEngineSingleton;
	return s_PEngineSingleton;

}