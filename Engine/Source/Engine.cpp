#include "Engine.h"
#include "Debug/Logger.h"
#include <csignal>

CAthenaEngine::CAthenaEngine() :	m_PViewport(CViewport::GetViewport()),
									m_PRenderer(CBaseRenderer::CreateRenderer()) {

	std::signal(SIGFPE, HandleCrash);
	std::signal(SIGILL, HandleCrash);
	std::signal(SIGSEGV, HandleCrash);	

};

void CAthenaEngine::Update(float fDelta) {
	
	return;

}

void CAthenaEngine::SetCrashCallback(CrashCallbackFunction CrashCallback) {

	s_SandboxCrashCallback = CrashCallback;

}

bool CAthenaEngine::Init(int x, int y) {

	HandleCrash(SIGILL);

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

	const char* CrashMessage;

	switch (Signal) {
	
	case (SIGFPE):
		CrashMessage = "A floating point exception was triggered.";
		break;

	case (SIGILL):
		CrashMessage = "An illegal instruction was encountered. This many be the result of installing the incorrect binaries for your machine architecture.";
		break;

	case (SIGSEGV):
		CrashMessage = "An illegal memory operation occured.";
		break;

	default:
		CrashMessage = "?";
		break;
	
	}

	if (s_SandboxCrashCallback != nullptr)
		s_SandboxCrashCallback(CrashMessage);

}