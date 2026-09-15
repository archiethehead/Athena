#include "Engine.h"
#include "Debug/Logger.h"
#include "SDL3/SDL_messagebox.h"
#include <csignal>

#if ((defined _MSVC_LANG) && (_MSVC_LANG == 202302L) && (defined _DEBUG))

	#include <stacktrace>

#endif

#include <string>

CAthenaEngine::CAthenaEngine() :	m_PViewport(CViewport::GetViewport()),
									m_PRenderer(CBaseRenderer::CreateRenderer()) {

	std::signal(SIGFPE, HandleSignalCrash);
	std::signal(SIGILL, HandleSignalCrash);
	std::signal(SIGSEGV, HandleSignalCrash);	

};

void CAthenaEngine::Update(float fDelta) {
	
	return;

}

void CAthenaEngine::SetCrashCallback(CrashCallbackFunction CrashCallback) {

	s_SandboxCrashCallback = CrashCallback;

}

bool CAthenaEngine::Init(int x, int y) {

	raise(SIGILL);

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

void CAthenaEngine::HandleSignalCrash(int Signal) {

	const char* CrashDescription;

	switch (Signal) {
	
	case (SIGFPE):
		CrashDescription = "A floating point exception was triggered.\n";
		break;

	case (SIGILL):
		CrashDescription = "An illegal instruction was encountered. This many be the result of installing the incorrect binaries for your machine's architecture.\n";
		break;

	case (SIGSEGV):
		CrashDescription = "An illegal memory operation occured.\n";
		break;

	default:
		CrashDescription = "?";
		break;
	
	}

#if ((((defined __linux__) && (defined __cplusplus) && (__cplusplus == 202302L)) || ((defined _WIN32) && (defined _MSVC_LANG) && (_MSVC_LANG == 202302L))) && (defined _DEBUG))

	std::stacktrace CStackTrace = std::stacktrace::current();
	std::string CrashMessage = std::to_string(CStackTrace).insert(0, "\nStack Trace:\n").insert(0, CrashDescription);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Crash Report", CrashMessage.c_str(), CViewport::GetViewport()->GetWindowHandle());

#else

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Crash Report", CrashDescription, CViewport::GetViewport()->GetWindowHandle());

#endif

	if (s_SandboxCrashCallback != nullptr)
		s_SandboxCrashCallback();

}