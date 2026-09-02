#ifdef _DEBUG

	#include "Debug.h"
	#include <cstdarg>
	#include <cstdio>
	#include <string>

	#ifdef _WIN32

		#include <windows.h>

	#endif // ifdef _WIN32	

	constexpr int IBUFFER_SIZE = 512; // 0.5KB
	char g_SBuffer[IBUFFER_SIZE];
	std::string g_SOutputString(IBUFFER_SIZE, '\0');

	void Out(const char* format, OutputOptions Option, ...) {

		va_list args;
		va_start(args, Option);
		vsnprintf(g_SBuffer, sizeof(g_SBuffer), format, args);
		va_end(args);

		g_SOutputString = g_SBuffer;
		int Len = (int)g_SOutputString.length();

		switch (Option) {
		
		case OutputOptions::Underline:
			g_SOutputString.append(Len, '-');
			g_SOutputString.insert(Len, 1, '\n');
			break;

		case OutputOptions::Header:
			g_SOutputString.insert(0, Len, '#');
			g_SOutputString.insert(Len, 1, '\n');
			g_SOutputString.append(Len, '#');
			g_SOutputString.insert((Len * 2) + 1, 1, '\n');
			break;

		case OutputOptions::Warning:
			g_SOutputString.insert(0, "WARNING: ");
			break;

		case OutputOptions::Error:
			g_SOutputString.insert(0, "ERROR: ");
			break;
		
		}

		g_SOutputString.append(1, '\n');

	#ifdef _WIN32

		if (IsDebuggerPresent()) OutputDebugStringA(g_SOutputString.c_str());
		else fputs(g_SOutputString.c_str(), stdout);

	#else

		fputs(g_SOutputString.c_str(), stdout);

	#endif // ifdef _WIN32

	}

#endif // ifdef _DEBUG