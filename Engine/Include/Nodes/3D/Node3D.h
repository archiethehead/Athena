#pragma once

#include "Nodes/Node.h"
#include "glm.hpp"

class node3D : public node {

public:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	node3D(const char* newNodeName, glm::vec3 newPosition, glm::vec3 newRotation);
	node3D() = default;
	~node3D() = default;

};