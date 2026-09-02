#pragma once

#include <cstdint>

enum OutputOptions : uint32_t {

	None,
	Underline,
	Header,
	Warning,
	Error

};

#ifdef _DEBUG

	#define DEBUG_OUT(x, y, ...) Out(x, y, ##__VA_ARGS__)
	void Out(const char* format, OutputOptions Option, ...);

#else

	#define DEBUG_OUT(x, OutputOptions EOptions, ...)

#endif