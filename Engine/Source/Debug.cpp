#ifdef _DEBUG

#include "Debug.h"
#include <cstdarg>
#include <cstdio>

#ifdef _WIN32

#include <windows.h>

#endif // ifdef _WIN32

void Out(const char* format, ...) {

	char buffer[1024];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

#ifdef _WIN32

	OutputDebugStringA(buffer);

#else

	puts(buffer);

#endif // ifdef _WIN32

}

#endif // ifdef _DEBUG