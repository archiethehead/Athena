#pragma once

#ifdef _WIN32

#include <windows.h>

	#ifdef COMPILING_ENGINE

		#define DLL_LINK __declspec(dllexport)

	#else

		#define DLL_LINK __declspec(dllimport) 

	#endif // ifdef COMPILING_ENGINE

#else

	#define DLL_LINK

#endif // ifdef _WIN32s

#include <cstdint>

class DLL_LINK node {

public:

	char* name = nullptr;
	uint64_t uid = NULL;

	node(const char* newNodeName);

	node() = default;
	~node();

};