#ifdef _DEBUG

	#include "Debug.h"
	#include <cstdarg>
	#include <cstdio>
	#include <string>

	#ifdef _WIN32

		#include <windows.h>
		#include <intrin.h>

	#endif // ifdef _WIN32	

	constexpr int IBUFFER_SIZE = 512; // 0.5KB
	char g_SBuffer[IBUFFER_SIZE];
	std::string g_SOutputString(IBUFFER_SIZE, '\0');

	void Out(const char* format, OutputOptions Option, ...) {

		unsigned int buff;
		_mm_lfence();
		uint64_t StartCycles = __rdtscp(&buff);
		_mm_lfence();

		// TEST

		va_list args;
		va_start(args, Option);
		size_t Len = vsnprintf(g_SBuffer, sizeof(g_SBuffer), format, args);
		va_end(args);

		g_SOutputString.clear();
		g_SOutputString.append(g_SBuffer);

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

		//if (IsDebuggerPresent()) OutputDebugStringA(g_SOutputString.c_str());
		//else fputs(g_SOutputString.c_str(), stdout);

		// END TEST
		_mm_lfence();
		uint64_t EndCycles = __rdtscp(&buff);
		_mm_lfence();

		printf("\n\nCycles to complete function: %I64d\n\n", EndCycles - StartCycles);

	#else

		fputs(g_SOutputString.c_str(), stdout);

	#endif // ifdef _WIN32

	}

#endif // ifdef _DEBUG