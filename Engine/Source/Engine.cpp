#include "Engine.h"
#include "Debug/Logger.h"
#include "SDL3/SDL_messagebox.h"
#include <csignal>

#if ((defined _MSVC_LANG) && (_MSVC_LANG == 202302L) && (defined _DEBUG))

	#include <stacktrace>

#endif

#include <string>

athenaEngine::athenaEngine() :	viewport(viewport::getViewport()),
								renderer(baseRenderer::createRenderer()) {

#ifdef _WIN32

	SetUnhandledExceptionFilter(handleExceptionCrash);
	AddVectoredContinueHandler(1, handleExceptionCrash);

#endif

	std::signal(SIGFPE, handleSignalCrash);
	std::signal(SIGILL, handleSignalCrash);
	std::signal(SIGSEGV, handleSignalCrash);	

};

void athenaEngine::update(float fDelta) {
	
	return;

}

void athenaEngine::setCrashCallback(CrashCallbackFunction CrashCallback) {

	s_SandboxCrashCallback = CrashCallback;

}

bool athenaEngine::init(int x, int y) {

	DEBUG_OUT("ATHENA ENGINE\n", outputOptions::None);
	DEBUG_OUT("\nInitializing Engine\n", outputOptions::None);

	if (!viewport->init(x, y)) goto Error;
	if (!renderer->init(viewport->getWindowHandle())) goto Error;

	DEBUG_OUT("Engine initialization success\n", outputOptions::None);
	return true;

Error:
	DEBUG_OUT("Engine initialization failure\n", outputOptions::Error);
	return false;

}

athenaEngine& athenaEngine::GetEngine() {

	static athenaEngine s_PEngineSingleton;
	return s_PEngineSingleton;

}

#ifdef _WIN32

LONG WINAPI athenaEngine::handleExceptionCrash(struct _EXCEPTION_POINTERS* ExceptionInformation) {

	crashProcedure();

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
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Crash Report", CrashMessage.c_str(), viewport::getViewport()->getWindowHandle());

#else

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Crash Report", CrashDescription, CViewport::GetViewport()->GetWindowHandle());

#endif // _MSVC_LANG == 202302L

	killProgram();

	return EXCEPTION_EXECUTE_HANDLER;

}

#endif // ifdef _WIN32


void athenaEngine::handleSignalCrash(int Signal) {

	crashProcedure();

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
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Crash Report", CrashMessage.c_str(), viewport::getViewport()->getWindowHandle());

#else

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Crash Report", CrashDescription, CViewport::GetViewport()->GetWindowHandle());

#endif

	killProgram();

}

void athenaEngine::crashProcedure() {

	FLUSH_LOGGER();

}

void athenaEngine::killProgram() {

	if (s_SandboxCrashCallback != nullptr)
		s_SandboxCrashCallback();

};