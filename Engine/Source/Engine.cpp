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

#ifdef _WIN32

	SetUnhandledExceptionFilter(HandleExceptionCrash);
	AddVectoredContinueHandler(1, HandleExceptionCrash);

#endif

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

	int a = 0;
	a /= 0;

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

#ifdef _WIN32

LONG WINAPI CAthenaEngine::HandleExceptionCrash(struct _EXCEPTION_POINTERS* ExceptionInformation) {

	CrashProcedure();

	const char* CrashDescription = "An unkown exception has occured, terminating program.";
	DWORD Exception = ExceptionInformation->ExceptionRecord->ExceptionCode;

	switch (Exception) {

	case EXCEPTION_IN_PAGE_ERROR:
		CrashDescription = "The application attempted to access a memory-page that doesn't exist. This can occur as a result of the storage medium the software exists on being removed during execution.\n";
		break;

	case EXCEPTION_INT_OVERFLOW:
	case EXCEPTION_FLT_OVERFLOW:
		CrashDescription = "A floating-point/integer overflow ocurred.\n";
		break;
	
	case EXCEPTION_FLT_INVALID_OPERATION:
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		CrashDescription = "An illegal floating point operation (e.g., divide by 0) occured.\n";
		break;

	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		CrashDescription = "A integer divide by zero exception occured.\n";
		break;

	case EXCEPTION_ILLEGAL_INSTRUCTION:
		CrashDescription = "An illegal instruction was encountered. This many be the result of installing the incorrect binaries for your machine's architecture.\n";
		break;

	case EXCEPTION_ACCESS_VIOLATION:
		CrashDescription = "An illegal memory operation occured.\n";
		break;

	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		CrashDescription = "The bounds of an array were exceeded.\n";

	case EXCEPTION_STACK_OVERFLOW:
		CrashDescription = "A stack memory overflow occured.\n";
		break;

	}

#if _MSVC_LANG == 202302L

	std::stacktrace CStackTrace = std::stacktrace::current();
	std::string CrashMessage = std::to_string(CStackTrace).insert(0, "\nStack Trace:\n").insert(0, CrashDescription);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Crash Report", CrashMessage.c_str(), CViewport::GetViewport()->GetWindowHandle());

#else

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Crash Report", CrashDescription, CViewport::GetViewport()->GetWindowHandle());

#endif // _MSVC_LANG == 202302L

	KillProgram();

	return EXCEPTION_EXECUTE_HANDLER;

}

#endif // ifdef _WIN32


void CAthenaEngine::HandleSignalCrash(int Signal) {

	CrashProcedure();

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

	KillProgram();

}

void CAthenaEngine::CrashProcedure() {

	FLUSH_LOGGER();

}

void CAthenaEngine::KillProgram() {

	if (s_SandboxCrashCallback != nullptr)
		s_SandboxCrashCallback();

};