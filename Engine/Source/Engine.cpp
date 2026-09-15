#include "Engine.h"
#include "Debug/Logger.h"

CAthenaEngine::CAthenaEngine() :	m_PViewport(CViewport::GetViewport()),
									m_PRenderer(CBaseRenderer::CreateRenderer()) {};

void CAthenaEngine::Update(float fDelta) {
	
	return;

}

void CAthenaEngine::SetCrashCallback(CrashCallbackFunction CrashCallback) {

	s_SandboxCrashCallback = CrashCallback;

}

bool CAthenaEngine::Init(int x, int y) {

	HandleCrash(2);

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

void CAthenaEngine::HandleCrash(int Signal) {

	if (s_SandboxCrashCallback != nullptr)
		s_SandboxCrashCallback("Crash :(");

}