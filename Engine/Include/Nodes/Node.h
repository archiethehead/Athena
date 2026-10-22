#pragma once

#include <cstdint>

class node {

public:

	char* name = nullptr;
	uint64_t uid = NULL;

	node(const char* newNodeName);

	node() = default;
	~node();

};