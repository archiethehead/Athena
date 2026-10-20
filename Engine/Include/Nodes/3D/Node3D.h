#pragma once

#include "Nodes/Node.h"
#include "glm.hpp"

class DLL_LINK node3D : public node {

public:
	glm::vec3 position;
	glm::vec3 rotation;

	node3D(const char* newNodeName, glm::vec3 newPosition, glm::vec3 newRotation);
	node3D() = default;
	~node3D() = default;

};