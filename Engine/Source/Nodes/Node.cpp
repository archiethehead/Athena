#include "Nodes/Node.h"
#include <cstdlib>
#include <cstring>

node::node(const char* newNodeName) {

	uid = (uint64_t)this;

	char* newNodeMemory = (char*)malloc(strlen(newNodeName) + 1);

	if (newNodeMemory == nullptr)
		return;

	name = newNodeMemory;
	strcpy_s(name, strlen(newNodeName) + 1, newNodeName);

}

node::~node() {

	if (name != nullptr)
		free(name);

}