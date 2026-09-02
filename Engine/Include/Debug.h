#pragma once


#ifdef _DEBUG

	#define DebugOut(x, ...) Out(x, ##__VA_ARGS__)
	void Out(const char* format, ...);

#else

	#define DebugOut(x, ...)

#endif

