#include "Engine.h"
#include "Debug.h"

void CAthenaEngine::Update(float fDelta) {
	
	return;

}

bool CAthenaEngine::Init(int x, int y) {

	DEBUG_OUT("ATHENA ENGINE", OutputOptions::Header);
	DEBUG_OUT("\nInitializing Engine", OutputOptions::Underline);

	if (!m_PViewport->Init(x, y)) goto Error;
	if (!m_PRenderer->Init(m_PViewport->GetWindowHandle())) goto Error;

	DEBUG_OUT("Engine initialization success", OutputOptions::None);
	return true;

Error:
	DEBUG_OUT("Engine initialization failure", OutputOptions::Error);
	return false;

}

CAthenaEngine& CAthenaEngine::GetEngine() {

	static CAthenaEngine s_PEngineSingleton;
	return s_PEngineSingleton;

}